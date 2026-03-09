#include "qstringcrypto.h"

#include <QByteArray>

// OpenSSL
#include <openssl/evp.h>
#include <openssl/rand.h>

static QByteArray secureRandomBytes(int n, bool* okOut = nullptr)
{
    if (okOut) *okOut = false;

    QByteArray out(n, Qt::Uninitialized);
    if (RAND_bytes(reinterpret_cast<unsigned char*>(out.data()), n) != 1) {
        out.clear();
        return out;
    }

    if (okOut) *okOut = true;
    return out;
}

bool QStringCrypto::validateKey32(const QByteArray& key32, QString& err)
{
    if (key32.size() != 32) {
        err = QString("Invalid key length (%1). AES-256-GCM requires a 32-byte key.").arg(key32.size());
        return false;
    }
    return true;
}

// --- Key helpers ---

QByteArray QStringCrypto::generateKey32(bool* ok)
{
    return secureRandomBytes(32, ok);
}

QStringCrypto::Result QStringCrypto::generateKey32Base64Url()
{
    Result r;
    bool ok = false;
    const QByteArray key = generateKey32(&ok);
    if (!ok || key.size() != 32) {
        r.error = "Failed to generate secure 32-byte key (OpenSSL RAND_bytes failed)";
        return r;
    }

    r.ok = true;
    r.value = QString::fromLatin1(key.toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals));
    return r;
}

QStringCrypto::Result QStringCrypto::key32FromBase64Url(const QString& keyBase64Url)
{
    Result r;

    const QByteArray key = QByteArray::fromBase64(keyBase64Url.toLatin1(), QByteArray::Base64UrlEncoding);
    if (key.size() != 32) {
        r.error = QString("Decoded key length is %1 bytes; expected 32.").arg(key.size());
        return r;
    }

    r.ok = true;
    // For this helper, put the raw bytes into value is awkward (QString may corrupt binary).
    // So return the same Base64Url if you want a Result, and the caller should use the QByteArray version.
    // To make this actually useful, we’ll return the key as HEX in value:
    r.value = QString::fromLatin1(key.toHex());
    return r;
}

//---------------------------------------------------------------------------------------
//
//  Encrypt methode: encryptToBase64Url
//
//---------------------------------------------------------------------------------------
QStringCrypto::Result QStringCrypto::encryptToBase64Url(const QString& plaintext, const QByteArray& key32)
{
    Result r;
    if (!validateKey32(key32, r.error))
        return r;

    const QByteArray plain = plaintext.toUtf8();

    bool rndOk = false;
    const QByteArray iv = secureRandomBytes(12, &rndOk); // recommended nonce length for GCM
    if (!rndOk || iv.size() != 12) {
        r.error = "Failed to generate IV (OpenSSL RAND_bytes failed)";
        return r;
    }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        r.error = "EVP_CIPHER_CTX_new failed";
        return r;
    }

    QByteArray ciphertext(plain.size(), 0);
    QByteArray tag(16, 0);

    bool ok = true;
    int len = 0;
    int outLen = 0;

    do {
        if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr) != 1) { ok = false; r.error = "EVP_EncryptInit_ex (cipher) failed"; break; }
        if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv.size(), nullptr) != 1) { ok = false; r.error = "EVP_CTRL_GCM_SET_IVLEN failed"; break; }

        if (EVP_EncryptInit_ex(ctx, nullptr, nullptr,
                               reinterpret_cast<const unsigned char*>(key32.constData()),
                               reinterpret_cast<const unsigned char*>(iv.constData())) != 1) { ok = false; r.error = "EVP_EncryptInit_ex (key/iv) failed"; break; }

        if (EVP_EncryptUpdate(ctx,
                              reinterpret_cast<unsigned char*>(ciphertext.data()), &len,
                              reinterpret_cast<const unsigned char*>(plain.constData()), plain.size()) != 1) { ok = false; r.error = "EVP_EncryptUpdate failed"; break; }
        outLen = len;

        if (EVP_EncryptFinal_ex(ctx,
                                reinterpret_cast<unsigned char*>(ciphertext.data()) + outLen, &len) != 1) { ok = false; r.error = "EVP_EncryptFinal_ex failed"; break; }
        outLen += len;
        ciphertext.truncate(outLen);

        if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, tag.size(), tag.data()) != 1) { ok = false; r.error = "EVP_CTRL_GCM_GET_TAG failed"; break; }
    } while (false);

    EVP_CIPHER_CTX_free(ctx);

    if (!ok)
        return r;

    // payload format: v2 + iv + tag + ciphertext
    QByteArray payload;
    payload.reserve(2 + iv.size() + tag.size() + ciphertext.size());
    payload.append("v2", 2);
    payload.append(iv);
    payload.append(tag);
    payload.append(ciphertext);

    r.ok = true;
    r.value = QString::fromLatin1(payload.toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals));
    return r;
}

//---------------------------------------------------------------------------------------
//
//  Decrypt methode: decryptFromBase64Url
//
//---------------------------------------------------------------------------------------
QStringCrypto::Result QStringCrypto::decryptFromBase64Url(const QString& payloadBase64Url, const QByteArray& key32)
{
    Result r;
    if (!validateKey32(key32, r.error))
        return r;

    const QByteArray payload = QByteArray::fromBase64(payloadBase64Url.toLatin1(), QByteArray::Base64UrlEncoding);
    if (payload.size() < 2 + 12 + 16) {
        r.error = "Payload too short";
        return r;
    }

    if (!(payload[0] == 'v' && payload[1] == '2')) {
        r.error = "Unsupported payload version";
        return r;
    }

    int offset = 2;
    const QByteArray iv  = payload.mid(offset, 12); offset += 12;
    const QByteArray tag = payload.mid(offset, 16); offset += 16;
    const QByteArray ciphertext = payload.mid(offset);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        r.error = "EVP_CIPHER_CTX_new failed";
        return r;
    }

    QByteArray plain(ciphertext.size(), 0);

    bool ok = true;
    int len = 0;
    int outLen = 0;

    do {
        if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr) != 1) { ok = false; r.error = "EVP_DecryptInit_ex (cipher) failed"; break; }
        if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv.size(), nullptr) != 1) { ok = false; r.error = "EVP_CTRL_GCM_SET_IVLEN failed"; break; }

        if (EVP_DecryptInit_ex(ctx, nullptr, nullptr,
                               reinterpret_cast<const unsigned char*>(key32.constData()),
                               reinterpret_cast<const unsigned char*>(iv.constData())) != 1) { ok = false; r.error = "EVP_DecryptInit_ex (key/iv) failed"; break; }

        if (EVP_DecryptUpdate(ctx,
                              reinterpret_cast<unsigned char*>(plain.data()), &len,
                              reinterpret_cast<const unsigned char*>(ciphertext.constData()), ciphertext.size()) != 1) { ok = false; r.error = "EVP_DecryptUpdate failed"; break; }
        outLen = len;

        if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, tag.size(), const_cast<char*>(tag.constData())) != 1) { ok = false; r.error = "EVP_CTRL_GCM_SET_TAG failed"; break; }

        // returns 0 if authentication fails (wrong key or tampered payload)
        if (EVP_DecryptFinal_ex(ctx,
                                reinterpret_cast<unsigned char*>(plain.data()) + outLen, &len) != 1) { ok = false; r.error = "Authentication failed (wrong key or corrupted data)"; break; }
        outLen += len;
        plain.truncate(outLen);
    } while (false);

    EVP_CIPHER_CTX_free(ctx);

    if (!ok)
        return r;

    r.ok = true;
    r.value = QString::fromUtf8(plain);
    return r;
}
