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
    strApplicationName = "AutoCost",
    strApplicationDomain = "CVelthoven.com",
    strApplicationOrganization = "CVelthoven",
    //-----------------------------------------------------------------------------------
    //
    //  Configuration General section key names
    //
    strSectionNameGeneral = "General",
    strGeneralSSHKeyKey = "SSHKey",
    strGeneralSSHIVKey = "SSHIV",
    //-----------------------------------------------------------------------------------
    //
    //  Configuraton Application Database section key names
    //
    strSectionNameAppDB = "Application database",
    strAppDBServerIPKey = "ServerIP",
    strAppDBServerPortKey = "ServerPort",
    strAppDBNameKey = "AppDBName",
    strAppDBUserIDKey = "AppDBUserID",
    strAppDBUserPasswordKey = "AppDBUserPassword";

//-----------------------------------------------------------------------------------
//
//  Enums for Cost overview dialog columns with descriptive names
//
enum CostOverViewCol
{
    CostOverViewRecID = 0,
    CostOverViewRecType,
    CostOverViewDate,
    CostOverViewDescription,
    CostOverViewPeriodic,
    CostOverViewElectricity,
    CostOverViewOther,
    CostOverViewAccessory,
    CostOverViewMillage,
    CostOverViewMillageTrip,
    CostOverViewKWhTrip,
    CostOverViewKWhLoaded,
    CostOverViewCostKWhperKM,
    CostOverViewAvgEuroPerKWh,
    CostOverViewKWhPerPercentage,
    CostOverViewKMPerPercentage,
    CostOverViewAccuStartPercentage,
    CostOverViewAccuEndPercentage,
    CostOverViewAccuUsagePercentage,
    CostOverViewAccuLoadDeltaPercentage,
    CostOverViewPeriod

};


#endif // AUTOCOST_H
