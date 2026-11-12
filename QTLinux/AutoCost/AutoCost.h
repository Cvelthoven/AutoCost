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
const QString
    strApplicationDatabaseConnectionName = "AppDataDBConnection";

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
//  Used in detailcosdatamodel and datainputdialog
//
enum CostRecordTypes
{
    CostRecPeriodic = 1,
    CostRecElectricity,
    CostRecOther,
    CostRecAccessory
};

#endif // AUTOCOST_H
