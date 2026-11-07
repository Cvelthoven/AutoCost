//---------------------------------------------------------------------------------------
//
//  Module: appsettingDatamodel.h
//
//  Class AppSettingDataModel contains the methodes to keep, maintain the application
//  configuration in memory during the execution of the application.
//
//---------------------------------------------------------------------------------------
#ifndef APPSETTINGDATAMODEL_H
#define APPSETTINGDATAMODEL_H
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "appsettings.h"

#include <QString>
#include <QVector>

//---------------------------------------------------------------------------------------
//
//  Class AppSettingDataModel definitions
//
//---------------------------------------------------------------------------------------
class AppSettingDataModel
{
public:
    AppSettingDataModel();

    QVector<QString> getStvAppDBConf() const;
    void setStvAppDBConf(const QVector<QString> &newStvAppDBConf);

    double getDKWhDef() const;
    void setDKWhDef(double newDKWhDef);

    int getIAccuDefEndPercentage() const;
    void setIAccuDefEndPercentage(int newIAccuDefEndPercentage);

    int getIMillageYear() const;
    void setIMillageYear(int newIMillageYear);

private:
    //-----------------------------------------------------------------------------------
    //
    //  Methodes
    //
    void ReadAutoCostConf();
    void ReadAutoCostConfAppDB();
    void ReadAutoCostConfLoadSessionDefaults();
    void ReadAutoCostConfMiscellaneous();

    //-----------------------------------------------------------------------------------
    //
    //  Values
    //
    double
        dKWhDef;

    int
        iAccuDefEndPercentage,
        iMillageYear;

     const QString
        //-------------------------------------------------------------------------------
        //
        //  Configuration for AppSettings
        //
        strApplicationName = "AutoCost",
        strApplicationDomain = "CVelthoven.com",
        strApplicationOrganization = "CVelthoven",

        //-------------------------------------------------------------------------------
        //
        //  Configuraton Application Database section key names
        //
        strSectionNameAppDB = "ApplicationDatabase",
        strAppDBServerIPKey = "ServerIP",
        strAppDBServerPortKey = "ServerPort",
        strAppDBNameKey = "AppDBName",
        strAppDBUserIDKey = "AppDBUserID",
        strAppDBUserPasswordKey = "AppDBUserPassword",
        //-------------------------------------------------------------------------------
        //
        //  Configuraton Application Load Session section key names
        //
        strSectionNameLoadSession = "LoadSessionDefaults",
        strLoadSessionKWh = "DefaultKWh",
        strLoadSessionAcceEndPercentage = "DefaultAccuEnd",
        //-------------------------------------------------------------------------------
        //
        //  Configuraton Application Miscellaneous section key names
        //
        strSectionNameMiscellaneous = "Miscellaneous",
        strMiscellaneousMillageYear = "MillageYear";

    QVector<QString>
        stvAppDBConf;

     AppSettings* ApplicationConfiguration = nullptr;
};

#endif // APPSETTINGDATAMODEL_H
