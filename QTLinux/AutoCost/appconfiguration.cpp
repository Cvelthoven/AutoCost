//---------------------------------------------------------------------------------------
//
//  Module: appconfiguration.cpp
//
//  This class contains the application settings during the run of the application.
//  It uses the class AppSettings for retrieval and maintenance on file
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "AutoCost.h"
#include "appsettings.h"
#include "appconfiguration.h"

#include <QString>

//---------------------------------------------------------------------------------------
//
//  AppSettings default constructor
//
//---------------------------------------------------------------------------------------
AppConfiguration::AppConfiguration()
{
    //-----------------------------------------------------------------------------------
    //
    //  Set application configuration to retrieve the conf file
    //
    asApplicationSettings = new AppSettings(strApplicationDomain,
                                            strApplicationName,
                                            strApplicationOrganization);

    //-----------------------------------------------------------------------------------
    //
    //  Retrieve the application database configuration values
    //
    RetriveDBConfiguration();
}

//---------------------------------------------------------------------------------------
//
//  AppSettings destructor
//
//---------------------------------------------------------------------------------------
AppConfiguration::~AppConfiguration()
{
    delete asApplicationSettings;
}

//---------------------------------------------------------------------------------------
//
//  Class methods
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  RetriveDBConfiguration
//
//  Retrieves the available application database configuration values
//  and stores them in a QList<QString> ApplicationDBConfig
//
//---------------------------------------------------------------------------------------
void AppConfiguration::RetriveDBConfiguration()
{
    QString
        strTempKeyName = "",
        strTempKeyValue = "";

    //-----------------------------------------------------------------------------------
    //
    //  Application database Options
    //
    //-----------------------------------------------------------------------------------
    strTempSectionName = strSectionNameAppDB;
    for (int iCnt1 = DBServerIP; iCnt1 <= DBAppPassword; iCnt1++)
    {
        switch (iCnt1)
        {
        case DBServerIP:
            strTempKeyName = strAppDBServerIPKey;
            bEncrypted = false;
            break;
        case DBServerPort:
            strTempKeyName = strAppDBServerPortKey;
            bEncrypted = false;
            break;
        case DBName:
            strTempKeyName = strAppDBNameKey;
            bEncrypted = false;
            break;
        case DBAppUserId:
            strTempKeyName = strAppDBUserIDKey;
            bEncrypted = false;
            break;
        case DBAppPassword:
            strTempKeyName = strAppDBUserPasswordKey;
            bEncrypted = true;
            break;
        default:
            break;
        }
        if (asApplicationSettings->GetAppSettings(strTempSectionName,strTempKeyName,strTempKeyValue, bEncrypted) == 0)
        {
            ApplicationDBConfig.append(strTempKeyValue);
            strTempKeyValue = "";
        }
        else
        {
            ApplicationDBConfig.append("");
        }
    }
}