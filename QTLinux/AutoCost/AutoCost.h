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
    strSectionNameAppDB = "Application Database",
    strAppDBServerIPKey = "ServerIP",
    strAppDBServerPortKey = "ServerPort",
    strAppDBNameKey = "AppDBName",
    strAppDBUserIDKey = "AppDBUersID",
    strAppDBUserPasswordKey= "AppDBUserPassword";

#endif // AUTOCOST_H
