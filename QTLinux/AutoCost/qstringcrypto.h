#pragma once

#include <QString>
#include <QByteArray>

/**
 * QStringCrypto
 *
 * Encrypts/decrypts QString using OpenSSL with AES-256-GCM (AEAD).
 * Accepts a RAW 32-byte key (binary), no password KDF performed here.
 *
 * Output is Base64URL (no padding) of a binary payload:
 *     [ 'v''2' | iv(12) | tag(16) | ciphertext(N) ]
 */
class QStringCrypto
{
public:
    struct Result
    {
        bool ok = false;
        QString value;     // ciphertext payload (encrypt) or plaintext (decrypt) or base64 key (helpers)
        QString error;     // error details if ok == false
    };

    // --- Key helpers ---
    // Generates a cryptographically secure 32-byte key (binary).
    // If ok==false, returned QByteArray is empty.
    static QByteArray generateKey32(bool* ok = nullptr);

    // Generates key and returns Base64URL (no padding) representation in Result.value
    static Result generateKey32Base64Url();

    // Decode Base64URL key back into raw 32-byte key
    static Result key32FromBase64Url(const QString& keyBase64Url);

    // --- Encryption / Decryption ---
    static Result encryptToBase64Url(const QString& plaintext, const QByteArray& key32);
    static Result decryptFromBase64Url(const QString& payloadBase64Url, const QByteArray& key32);

private:
    static bool validateKey32(const QByteArray& key32, QString& err);
};
