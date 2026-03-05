//---------------------------------------------------------------------------------------
//
//  Module: appsettings.h
//
//---------------------------------------------------------------------------------------
#ifndef APPSETTINGS_H
#define APPSETTINGS_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include <QObject>
#include <QString>

//---------------------------------------------------------------------------------------
//
//  Clsass AppSettings definitions
//
//---------------------------------------------------------------------------------------
class AppSettings
{
public:
    AppSettings();

    //-----------------------------------------------------------------------------------
    //
    //  Public methods
    //
    //-----------------------------------------------------------------------------------
    int GetAppSettings(const QString &strKeySection,
                       const QString &strKeyName,
                       QString &strKeyValue);
    int SetApplicationDomain(const QString &strApplicationDomain);
    int SetApplicationName(const QString &strApplicationName);
    int SetApplicationOrganization(const QString &strApplicationOrganization);
    int SetAppSettings(const QString &strKeySection,
                       const QString &strKeyName,
                       QString &strKeyValue);

private:
    QString strFullKeyPath;

};

#endif // APPSETTINGS_H
