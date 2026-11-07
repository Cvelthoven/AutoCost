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
    // must be removed used in millageoverviewdatamodel and datainput dialog
    iAccuEndPercentageDefault = 90, // -> App settings
    iMaxMillageYear = 10000,        // -> App settings, and per year adjustable
    iMaxNbElectricityPeriods = 10;  // -> App settings or dynamic

const double
    // must be removed used in millageoverviewdatamodel and datainput dialog
    dKWhMaxDefault = 7.7000;//  -> App settings,

const QString
    // still use in appconfiguration must be removed
    strApplicationName = "AutoCost",
    strApplicationDomain = "CVelthoven.com",
    strApplicationOrganization = "CVelthoven",

    //-----------------------------------------------------------------------------------
    //
    //  Other QString values
    //
    strApplicationDatabaseConnectionName = "AppDataDBConnection";

//---------------------------------------------------------------------------------------
//
//  Enums for the application settings in configuration file
//
//---------------------------------------------------------------------------------------
//
//  Descriptive names for the Application database configuration values
//
//  Use in MainWindow and AppSettingsDataModel
//
enum AppAppDBOptions
{
    AppOptionServerIP = 0,
    AppOptionServerPort,
    AppOptionAppDBName,
    AppOptionAppDBUserID,
    AppOptionAppDBPassword
};

//---------------------------------------------------------------------------------------
//
//  Descriptove names for the record types
//
//  Used in detailcosdatamodel and datainputdialog needs to be removed
enum CostRecordTypes
{
    CostRecPeriodic = 1,
    CostRecElectricity,
    CostRecOther,
    CostRecAccessory
};

#endif // AUTOCOST_H
