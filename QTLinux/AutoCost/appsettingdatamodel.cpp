//---------------------------------------------------------------------------------------
//
//  Module: appsettingDatamodel.cpp
//
//  Class AppSettingDataModel contains the methodes to keep, maintain the application
//  configuration in memory during the execution of the application.
//
//---------------------------------------------------------------------------------------
#include "appsettingdatamodel.h"
#include "appsettings.h"
#include "AutoCost.h"

#include <QString>
#include <QVector>

//---------------------------------------------------------------------------------------
//
//  AppSettingDataModel default constructor
//
//---------------------------------------------------------------------------------------
AppSettingDataModel::AppSettingDataModel()
{
    //-----------------------------------------------------------------------------------
    //
    //  Initialize values
    //
    for (int iCnt1 = 0; iCnt1 <= AppOptionAppDBPassword; iCnt1++)
    {
        stvAppDBConf.append("");
    }
    dKWhDef = -1.00;
    iAccuDefEndPercentage = -1;
    iMillageYear = -1;

    //-----------------------------------------------------------------------------------
    //
    //  Create and init application settings
    //
    ApplicationConfiguration = new AppSettings(strApplicationDomain,
                                               strApplicationName,
                                               strApplicationOrganization);

    //-----------------------------------------------------------------------------------
    //
    //  Retrieve data from autocost.conf
    //
    ReadAutoCostConf();
}

//---------------------------------------------------------------------------------------
//
//  Class AppSettingDataModel methodes
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  getDKWhDef
//
//---------------------------------------------------------------------------------------
double AppSettingDataModel::getDKWhDef() const
{
    return dKWhDef;
}

//---------------------------------------------------------------------------------------
//
//  getIAccuDefEndPercentage
//
//---------------------------------------------------------------------------------------
int AppSettingDataModel::getIAccuDefEndPercentage() const
{
    return iAccuDefEndPercentage;
}

//---------------------------------------------------------------------------------------
//
//  getIMillageYear
//
//---------------------------------------------------------------------------------------
int AppSettingDataModel::getIMillageYear() const
{
    return iMillageYear;
}

//---------------------------------------------------------------------------------------
//
//  getStvAppDBConf
//
//---------------------------------------------------------------------------------------
QVector<QString> AppSettingDataModel::getStvAppDBConf() const
{
    return stvAppDBConf;
}

//---------------------------------------------------------------------------------------
//
//  ReadAutoCostConf
//
//---------------------------------------------------------------------------------------
void AppSettingDataModel::ReadAutoCostConf()
{

    ReadAutoCostConfAppDB();
    ReadAutoCostConfLoadSessionDefaults();
    ReadAutoCostConfMiscellaneous();
}

//---------------------------------------------------------------------------------------
//
//  ReadAutoCostConfAppDB
//
//---------------------------------------------------------------------------------------
void AppSettingDataModel::ReadAutoCostConfAppDB()
{
    ApplicationConfiguration->GetAppSettings(strSectionNameAppDB,
                                             strAppDBServerIPKey,
                                             stvAppDBConf[AppOptionServerIP],
                                             false);
    ApplicationConfiguration->GetAppSettings(strSectionNameAppDB,
                                             strAppDBServerPortKey,
                                             stvAppDBConf[AppOptionServerPort],
                                             false);
    ApplicationConfiguration->GetAppSettings(strSectionNameAppDB,
                                             strAppDBNameKey,
                                             stvAppDBConf[AppOptionAppDBName],
                                             false);
    ApplicationConfiguration->GetAppSettings(strSectionNameAppDB,
                                             strAppDBUserIDKey,
                                             stvAppDBConf[AppOptionAppDBUserID],
                                             false);
    ApplicationConfiguration->GetAppSettings(strSectionNameAppDB,
                                             strAppDBUserPasswordKey,
                                             stvAppDBConf[AppOptionAppDBPassword],
                                             true);

}

//---------------------------------------------------------------------------------------
//
//  ReadAutoCostConfLoadSessionDefaults
//
//---------------------------------------------------------------------------------------
void AppSettingDataModel::ReadAutoCostConfLoadSessionDefaults()
{
    QString strKeyValueTemp;

    ApplicationConfiguration->GetAppSettings(strSectionNameLoadSession,
                                             strLoadSessionKWh,
                                             strKeyValueTemp,
                                             false);
    dKWhDef = strKeyValueTemp.toDouble();

    ApplicationConfiguration->GetAppSettings(strSectionNameLoadSession,
                                             strLoadSessionAcceEndPercentage,
                                             strKeyValueTemp,
                                             false);
    iAccuDefEndPercentage = strKeyValueTemp.toInt();

}

//---------------------------------------------------------------------------------------
//
//  ReadAutoCostConfMiscellaneous
//
//---------------------------------------------------------------------------------------
void AppSettingDataModel::ReadAutoCostConfMiscellaneous()
{
    QString strKeyValueTemp;

    ApplicationConfiguration->GetAppSettings(strSectionNameMiscellaneous,
                                             strMiscellaneousMillageYear,
                                             strKeyValueTemp,
                                             false);
    iMillageYear = strKeyValueTemp.toInt();

}

//---------------------------------------------------------------------------------------
//
//  setDKWhDef
//
//---------------------------------------------------------------------------------------
void AppSettingDataModel::setDKWhDef(double newDKWhDef)
{
    dKWhDef = newDKWhDef;
}

//---------------------------------------------------------------------------------------
//
//  setIAccuDefEndPercentage
//
//---------------------------------------------------------------------------------------
void AppSettingDataModel::setIAccuDefEndPercentage(int newIAccuDefEndPercentage)
{
    iAccuDefEndPercentage = newIAccuDefEndPercentage;
}

//---------------------------------------------------------------------------------------
//
//  setIMillageYear
//
//---------------------------------------------------------------------------------------
void AppSettingDataModel::setIMillageYear(int newIMillageYear)
{
    iMillageYear = newIMillageYear;
}

//---------------------------------------------------------------------------------------
//
//  setStvAppDBConf
//
//---------------------------------------------------------------------------------------
void AppSettingDataModel::setStvAppDBConf(const QVector<QString> &newStvAppDBConf)
{
    stvAppDBConf = newStvAppDBConf;
}
