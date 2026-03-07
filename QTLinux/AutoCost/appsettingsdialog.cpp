//---------------------------------------------------------------------------------------
//
//  Module: appsettings.cpp
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "appsettings.h"
#include "appsettingsdialog.h"
#include "ui_appsettingsdialog.h"
#include "AutoCost.h"

#include <QString>

#include <QDebug>

//---------------------------------------------------------------------------------------
//
//  AppSettings default constructor and destructor
//
//---------------------------------------------------------------------------------------
AppSettingsDialog::AppSettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AppSettingsDialog)
{
    qDebug() << "appsettingdialog -> constructor triggered";
    //-----------------------------------------------------------------------------------
    //
    //  Local variables
    //
    //----------------------------------------------------------------------------------
    int iCnt;

    QString
        strTempSectionName ="",
        strTempKeyName = "",
        strTempKeyValue = "";

    ui->setupUi(this);

    //-----------------------------------------------------------------------------------
    //
    //  Load available application configuration
    //
    //-----------------------------------------------------------------------------------
    AppConfiguration = new AppSettings(strApplicationDomain,
                                       strApplicationName,
                                       strApplicationOrganization);

    //-----------------------------------------------------------------------------------
    //
    //  Load the application configuration
    //
    //-----------------------------------------------------------------------------------
    //
    //  General Options
    //
    //-----------------------------------------------------------------------------------
    strTempSectionName = "General";
    for (int iCnt1 = AppOptionSSHKey; iCnt1 <= AppOptionSSHIV; iCnt1++)
    {
        switch (iCnt1)
        {
        case AppOptionSSHKey:
            strTempKeyName = "SSHKey";
            break;
        case AppOptionSSHIV:
            strTempKeyName = "SSHIV";
            break;
        default:
            break;
        }
        if (AppConfiguration->GetAppSettings(strTempSectionName,strTempKeyName,strTempKeyValue) == 0)
        {
            lsGeneralOptions.append(strTempKeyValue);
            strTempKeyValue = "";
        }
        else
        {
            lsGeneralOptions.append("");
        }
    }

    //-----------------------------------------------------------------------------------
    //
    //  Application database Options
    //
    //-----------------------------------------------------------------------------------
    strTempSectionName = "Application database";
    for (int iCnt1 = AppOptionServerIP; iCnt1 <= AppOptionAppDBPassword; iCnt1++)
    {
        switch (iCnt1)
        {
        case AppOptionServerIP:
            strTempKeyName = "ServerIP";
            break;
        case AppOptionServerPort:
            strTempKeyName = "ServerPort";
            break;
        case AppOptionAppDBName:
            strTempKeyName = "AppDBName";
            break;
        case AppOptionAppDBUserID:
            strTempKeyName = "AppDBUserID";
            break;
        case AppOptionAppDBPassword:
            strTempKeyName = "AppDBUserPassword";
            break;
        default:
            break;
        }
        if (AppConfiguration->GetAppSettings(strTempSectionName,strTempKeyName,strTempKeyValue) == 0)
        {
            lsAppDBOptions.append(strTempKeyValue);
            strTempKeyValue = "";
        }
        else
        {
            lsAppDBOptions.append("");
        }
    }

    //-----------------------------------------------------------------------------------
    //
    //  Preload found values into the dialog fields
    //
    //-----------------------------------------------------------------------------------
    //
    //  General Options
    //
    //-----------------------------------------------------------------------------------
    for (int iCnt1 = AppOptionSSHKey; iCnt1 <= AppOptionSSHIV; iCnt1++)
    {
        switch (iCnt1)
        {
        case AppOptionSSHKey:
            ui->lneSSHKey->setText(lsGeneralOptions[iCnt1]);
            break;
        case AppOptionSSHIV:
            ui->lneSSHIV->setText(lsGeneralOptions[iCnt1]);
            break;
        default:
            break;
        }
    }

    //-----------------------------------------------------------------------------------
    //
    //  Application database options
    //
    //-----------------------------------------------------------------------------------
    for (int iCnt1 = AppOptionServerIP; iCnt1 <= AppOptionAppDBPassword; iCnt1++)
    {
        switch (iCnt1)
        {
        case AppOptionServerIP:
            ui->lneAppServerIP->setText(lsAppDBOptions[iCnt1]);
            break;
        case AppOptionServerPort:
            ui->lneAppServerPort->setText(lsAppDBOptions[iCnt1]);
            break;
        case AppOptionAppDBName:
            ui->lneAppDBName->setText(lsAppDBOptions[iCnt1]);
            break;
        case AppOptionAppDBUserID:
            ui->lneAppDBUserID->setText(lsAppDBOptions[iCnt1]);
            break;
        case AppOptionAppDBPassword:
            ui->lneAppDBPassword->setText(lsAppDBOptions[iCnt1]);
            break;
        default:
            break;
        }
    }

    //-----------------------------------------------------------------------------------
    //
    //  Execute dialog
    //
    //-----------------------------------------------------------------------------------
    AppSettingsDialog::exec();

}

AppSettingsDialog::~AppSettingsDialog()
{
    delete ui;
}
