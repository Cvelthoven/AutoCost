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

#include <QCoreApplication>
#include <QSettings>
#include <QString>

//---------------------------------------------------------------------------------------
//
//  AppSettings default constructor
//
//---------------------------------------------------------------------------------------
AppSettings::AppSettings() {}

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
                                QString &strKeyValue)
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
        strKeyValue = temp.toString();
    }
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
                                QString &strKeyValue)
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
    programConfig.setValue(strFullKeyPath, strKeyValue);
    programConfig.sync();

    return 0;
}
