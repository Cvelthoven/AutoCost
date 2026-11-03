//---------------------------------------------------------------------------------------
//  Module: AutoCost.h
//
//  This module defines all program wide values
//
//---------------------------------------------------------------------------------------
#ifndef AUTOCOST_H
#define AUTOCOST_H

//---------------------------------------------------------------------------------------
//
//  Include headers
//
//---------------------------------------------------------------------------------------
#include <QString>

//---------------------------------------------------------------------------------------
//
//  Application configuration definitions
//
//---------------------------------------------------------------------------------------
const int
    iAccuEndPercentageDefault = 90, // -> App settings
    iMaxMillageYear = 10000,        // -> App settings, and per year adjustable
    iMaxNbElectricityPeriods = 10;  // -> App settings or dynamic

const double
    dKWhMaxDefault = 7.7000;//  -> App settings,

const QString
    strApplicationName = "AutoCost",
    strApplicationDomain = "CVelthoven.com",
    strApplicationOrganization = "CVelthoven",
    //-----------------------------------------------------------------------------------
    //
    //  Configuration General section key names
    //
    strSectionNameGeneral = "General",//!!!!1!!!! No longer used
    strGeneralSSHKeyKey = "SSHKey",//!!!!!!!!!!!! No longer used
    strGeneralSSHIVKey = "SSHIV",//!!!!!!!!!!!!!! No longer used
    //-----------------------------------------------------------------------------------
    //
    //  Configuraton Application Database section key names
    //
    strSectionNameAppDB = "Application database",
    strAppDBServerIPKey = "ServerIP",
    strAppDBServerPortKey = "ServerPort",
    strAppDBNameKey = "AppDBName",
    strAppDBUserIDKey = "AppDBUserID",
    strAppDBUserPasswordKey = "AppDBUserPassword",
    //-----------------------------------------------------------------------------------
    //
    //  Other QString values
    //
    strApplicationDatabaseConnectionName = "AppDataDBConnection";


//---------------------------------------------------------------------------------------
//
//  Enums for the application settings in configuration file
//
enum AppConfDatabase
{
    DBServerIP = 0,
    DBServerPort,
    DBName,
    DBAppUserId,
    DBAppPassword
};

//---------------------------------------------------------------------------------------
//
//  Descriptove names for the record types
//
enum CostRecordTypes
{
    CostRecPeriodic = 1,
    CostRecElectricity,
    CostRecOther,
    CostRecAccessory
};

//---------------------------------------------------------------------------------------
//
//  Descriptive column names of DetailCostDataModel query
//
enum DataColumnFields
{
    DataColAutoCostRecID = 0,
    DataColAutoCostRecType,
    DataColAutoCostDate,
    DataColAutoCostDescription,
    DataColAutoCostTotalCost,
    DataColAutoCostFrequency,
    DataColElectricityRecID,
    DataColElectricityKmTotal,
    DataColElectricityKWhLoaded,
    DataColElectricityCapBattteryStart,
    DataColElectricityCapBatteryEnd,
    DataColElectricityStartTime
};

#endif // AUTOCOST_H
