//---------------------------------------------------------------------------------------
//
//  Module: appconfiguration.h
//
//  This class contains the application settings during the run of the application.
//  It uses the class AppSettings for retrieval and maintenance on file
//
//---------------------------------------------------------------------------------------
#ifndef APPCONFIGURATION_H
#define APPCONFIGURATION_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "AutoCost.h"
#include "appsettings.h"
#include <QString>
//---------------------------------------------------------------------------------------
//
//  Clsass AppSettings definitions
//
//---------------------------------------------------------------------------------------
class AppConfiguration
{
public:
    AppConfiguration();
    ~AppConfiguration();

    //-----------------------------------------------------------------------------------
    //
    //  Stringlists containing the configuration settings per section
    //
    QList<QString>
        ApplicationDBConfig;

private:
    //-----------------------------------------------------------------------------------
    //
    //  Private methods
    //
    void RetriveDBConfiguration();

    //-----------------------------------------------------------------------------------
    //
    //  Private variables
    //
    AppSettings* asApplicationSettings = nullptr;

    bool
        bEncrypted = false;

    QString
        strTempSectionName = "";

};

#endif // APPCONFIGURATION_H
