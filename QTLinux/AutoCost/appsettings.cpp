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
    return 0;
}

//---------------------------------------------------------------------------------------
//
//  LoadKeyValues
//
//---------------------------------------------------------------------------------------
int AppSettings::LoadKeyValues()
{
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
    return 0;
}

//---------------------------------------------------------------------------------------
//
//  WriteKeyValues
//
//---------------------------------------------------------------------------------------
int AppSettings::WriteKeyValues()
{
    return 0;
}
