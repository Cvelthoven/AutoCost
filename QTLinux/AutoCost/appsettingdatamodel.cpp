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
    for (int iCnt1 = 0; iCnt1 < AppOptionAppDBPassword; iCnt1++)
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
