//---------------------------------------------------------------------------------------
//
//  Module: appsettings.cpp
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "appsettings.h"
#include "qstringcrypto.h"

#include <QByteArray>
#include <QCoreApplication>
#include <QSettings>
#include <QString>
#include <QVariant>

//---------------------------------------------------------------------------------------
//
//  Helpers for encryption/decryption
//  These need to be at the beginning of the code (calls are not in header file)
//
//---------------------------------------------------------------------------------------
static QString cryptoKeySettingsPath()
{
    // Where the Base64URL key is stored in QSettings
    return "Crypto/Key32";
}

static QByteArray ensureCryptoKey32(QSettings& settings)
{
    // Try load
    const QString keyB64Url = settings.value(cryptoKeySettingsPath()).toString();
    QByteArray key32 = QByteArray::fromBase64(keyB64Url.toLatin1(), QByteArray::Base64UrlEncoding);

    if (key32.size() == 32)
        return key32;

    // Generate + persist
    const auto gen = QStringCrypto::generateKey32Base64Url();
    if (!gen.ok || gen.value.isEmpty())
        return QByteArray(); // encryption disabled if generation fails

    settings.setValue(cryptoKeySettingsPath(), gen.value);
    settings.sync();

    key32 = QByteArray::fromBase64(gen.value.toLatin1(), QByteArray::Base64UrlEncoding);
    if (key32.size() != 32)
        return QByteArray();

    return key32;
}

static bool isProbablyEncryptedPayloadV2(const QString& s)
{
    // Decode and look for "v2" prefix described in QStringCrypto header
    const QByteArray raw = QByteArray::fromBase64(s.toLatin1(), QByteArray::Base64UrlEncoding);
    return raw.size() >= 2 && raw[0] == 'v' && raw[1] == '2';
}

//---------------------------------------------------------------------------------------
//
//  AppSettings default constructor
//
//---------------------------------------------------------------------------------------
AppSettings::AppSettings() {}

//---------------------------------------------------------------------------------------
//
//  Constructor that loads the configuration into memory
//
//---------------------------------------------------------------------------------------
AppSettings::AppSettings(const QString &strApplicationDomain,
                         const QString &strApplicationName,
                         const QString &strApplicationOrganization)
{
    QString strSectionName = "General",
        strKeyName = "",
        strKeyValue = "";

    //-----------------------------------------------------------------------------------
    //
    //  Set application enviroment definitions
    //
    //-----------------------------------------------------------------------------------
    QCoreApplication::setOrganizationDomain(strApplicationDomain);
    QCoreApplication::setApplicationName(strApplicationName);
    QCoreApplication::setOrganizationName(strApplicationOrganization);


}

//---------------------------------------------------------------------------------------
//
//  Class methods
//
//---------------------------------------------------------------------------------------
//
//  GetAppSettings
//
//---------------------------------------------------------------------------------------
int AppSettings::GetAppSettings(const QString &strKeySection,
                                const QString &strKeyName,
                                QString &strKeyValue,
                                bool bEncrypt)
{
    //-----------------------------------------------------------------------------------
    //
    //  Ensure keyname is defined
    //
    //-----------------------------------------------------------------------------------
    if (strKeyName.size() == 0)
    {
        return 1;
    }

    //-----------------------------------------------------------------------------------
    //
    //  Build full path to application key
    //
    //-----------------------------------------------------------------------------------
    if (strKeySection.size() !=0)
    {
        strFullKeyPath = strKeySection + "/" + strKeyName;
    }
    else
    {
        strFullKeyPath = strKeyName;
    }

    //-----------------------------------------------------------------------------------
    //
    //  Retrieve the value of the application key
    //
    //-----------------------------------------------------------------------------------
    QSettings programConfig;
    QVariant temp = programConfig.value(strFullKeyPath);
     if (temp.isValid())
    {
        //-------------------------------------------------------------------------------
        //
        //  Check if the value is encrypted
        if (bEncrypt)
        {
            const QString stored = temp.toString();

    //        QSettings programConfig; // or reuse the one you already created above if you prefer
            const QByteArray key32 = ensureCryptoKey32(programConfig);

            if (!key32.isEmpty() && isProbablyEncryptedPayloadV2(stored))
            {
                const auto dec = QStringCrypto::decryptFromBase64Url(stored, key32);
                if (dec.ok)
                    strKeyValue = dec.value;
                else
                    strKeyValue = stored; // fallback
            }
            else
            {
                strKeyValue = stored; // plaintext legacy value
            }
        }
        //-------------------------------------------------------------------------------
        //
        //  Value is not encrypted
        else
        {
            strKeyValue = temp.toString();
        }
    }
    //-----------------------------------------------------------------------------------
    //
    //  Key not found return empty string
    //
    else
    {
        strKeyValue = "";
    }

    return 0;
}

//---------------------------------------------------------------------------------------
//
//  SetApplicationDomain
//
//---------------------------------------------------------------------------------------
int AppSettings::SetApplicationDomain(const QString &strApplicationDomain)
{
    if (strApplicationDomain.length() != 0)
    {
        QCoreApplication::setOrganizationDomain(strApplicationDomain);
        return 0;
    }
    else
    {
        return 1;
    }

}

//---------------------------------------------------------------------------------------
//
//  SetApplicationName
//
//---------------------------------------------------------------------------------------
int AppSettings::SetApplicationName(const QString &strApplicationName)
{
    if (strApplicationName.length() != 0)
    {
        QCoreApplication::setApplicationName(strApplicationName);
        return 0;
    }
    else
    {
        return 1;
    }
 }

//---------------------------------------------------------------------------------------
//
//  SetApplicationOrganization
//
//---------------------------------------------------------------------------------------
int AppSettings::SetApplicationOrganization(const QString &strApplicationOrganization)
{
    if (strApplicationOrganization.length() != 0)
    {
        QCoreApplication::setOrganizationName(strApplicationOrganization);
        return 0;
    }
    else
    {
        return 1;
    }
}

//---------------------------------------------------------------------------------------
//
//  SetAppSettings
//
//---------------------------------------------------------------------------------------
int AppSettings::SetAppSettings(const QString &strKeySection,
                                const QString &strKeyName,
                                QString &strKeyValue,
                                bool bEncrypt)
{
    //-----------------------------------------------------------------------------------
    //
    //  Ensure keyname is defined
    //
    //-----------------------------------------------------------------------------------
    if (strKeyName.size() == 0)
    {
        return 1;
    }

    //-----------------------------------------------------------------------------------
    //
    //  Build full path to application key
    //
    //-----------------------------------------------------------------------------------
    if (strKeySection.size() !=0)
    {
        strFullKeyPath = strKeySection + "/" + strKeyName;
    }
    else
    {
        strFullKeyPath = strKeyName;
    }

    //-----------------------------------------------------------------------------------
    //
    //  Set and force write of the application key
    //
    //-----------------------------------------------------------------------------------
    QSettings programConfig;

    if (bEncrypt)
    {
        const QByteArray key32 = ensureCryptoKey32(programConfig);

        if (!key32.isEmpty() && !strKeyValue.isEmpty())
        {
            const auto enc = QStringCrypto::encryptToBase64Url(strKeyValue, key32);
            if (enc.ok)
            {
                programConfig.setValue(strFullKeyPath, enc.value);
            }
            else
            {
                // Fallback to plaintext if encryption fails
                programConfig.setValue(strFullKeyPath, strKeyValue);
            }
        }
        else
        {
            // If key missing/empty -> store plaintext
            programConfig.setValue(strFullKeyPath, strKeyValue);
        }
    }
    else
    {
        programConfig.setValue(strFullKeyPath, strKeyValue);
    }
    programConfig.sync();
    return 0;
}

