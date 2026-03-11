//---------------------------------------------------------------------------------------
//
//  Module: postgresqldb.cpp
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "AutoCost.h"
#include "appsettings.h"
#include "postgresqldb.h"

#include <QSqlDatabase>

#include <QDebug>

//---------------------------------------------------------------------------------------
//
//  AppSettings default constructor
//
//---------------------------------------------------------------------------------------
PostGreSQLDB::PostGreSQLDB()
{
    //-----------------------------------------------------------------------------------
    //
    //  Retrieve application database configuration
    //
    //-----------------------------------------------------------------------------------
    ApplicationConfig = new AppSettings(strApplicationDomain,
                                        strApplicationName,
                                        strApplicationOrganization);
    strKeyName = strAppDBServerIPKey;
    if (ApplicationConfig->GetAppSettings(strSectionName,strKeyName,strDBServerIP, bEncrypted) != 0)
    {
        strDBServerIP = "";
    }
    strKeyName = strAppDBServerPortKey;
    if (ApplicationConfig->GetAppSettings(strSectionName,strKeyName,strDBServerPort, bEncrypted) != 0)
    {
        strDBServerPort = "";
    }
    strKeyName = strAppDBNameKey;
    if (ApplicationConfig->GetAppSettings(strSectionName,strKeyName,strDBName, bEncrypted) != 0)
    {
        strDBName = "";
    }
    strKeyName = strAppDBUserIDKey;
    if (ApplicationConfig->GetAppSettings(strSectionName,strKeyName,strDBUserID, bEncrypted) != 0)
    {
        strDBUserID = "";
    }
    strKeyName = strAppDBUserPasswordKey;
    bEncrypted = true;
    if (ApplicationConfig->GetAppSettings(strSectionName,strKeyName,strDBPassword, bEncrypted) != 0)
    {
        strDBPassword = "";
    }

    qDebug() << "database configuration loaded";
}
