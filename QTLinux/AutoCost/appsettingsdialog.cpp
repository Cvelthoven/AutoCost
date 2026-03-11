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

//#include <QDebug>

//---------------------------------------------------------------------------------------
//
//  AppSettings default constructor and destructor
//
//---------------------------------------------------------------------------------------
AppSettingsDialog::AppSettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AppSettingsDialog)
{
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
    strTempSectionName = strSectionNameGeneral;
    for (int iCnt1 = AppOptionSSHKey; iCnt1 <= AppOptionSSHIV; iCnt1++)
    {
        switch (iCnt1)
        {
        case AppOptionSSHKey:
            strTempKeyName = strGeneralSSHKeyKey;
            bEncrypted = false;
            break;
        case AppOptionSSHIV:
            strTempKeyName = strGeneralSSHIVKey;
            bEncrypted = false;
            break;
        default:
            break;
        }
        if (AppConfiguration->GetAppSettings(strTempSectionName,strTempKeyName,strTempKeyValue, bEncrypted) == 0)
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
    strTempSectionName = strSectionNameAppDB;
    for (int iCnt1 = AppOptionServerIP; iCnt1 <= AppOptionAppDBPassword; iCnt1++)
    {
        switch (iCnt1)
        {
        case AppOptionServerIP:
            strTempKeyName = strAppDBServerIPKey;
            bEncrypted = false;
            break;
        case AppOptionServerPort:
            strTempKeyName = strAppDBServerPortKey;
            bEncrypted = false;
            break;
        case AppOptionAppDBName:
            strTempKeyName = strAppDBNameKey;
            bEncrypted = false;
            break;
        case AppOptionAppDBUserID:
            strTempKeyName = strAppDBUserIDKey;
            bEncrypted = false;
            break;
        case AppOptionAppDBPassword:
            strTempKeyName = strAppDBUserPasswordKey;
            bEncrypted = true;
            break;
        default:
            break;
        }
        if (AppConfiguration->GetAppSettings(strTempSectionName,strTempKeyName,strTempKeyValue, bEncrypted) == 0)
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

//---------------------------------------------------------------------------------------
//
//  Slots methodes
//
//---------------------------------------------------------------------------------------
//
//  Method on_buttonBox_accepted
//  Handles the activation of the accept button in the options dialog.
//  Checks if values have been changes and when changes store the in memory and write to
//  file
//
//---------------------------------------------------------------------------------------
void AppSettingsDialog::on_buttonBox_accepted()
{
    qDebug() << "appsettingdialog -> accept button triggered";

    //-----------------------------------------------------------------------------------
    //
    //  Local variables
    //
    //----------------------------------------------------------------------------------
    int iCnt1;

    QString
        strTempKeyValue = "",
        strKeyName = "",
        strSectionName = "";

    //-----------------------------------------------------------------------------------
    //
    //  Check if values are changed
    //
    //-----------------------------------------------------------------------------------
    //
    //  General options
    //
    //-----------------------------------------------------------------------------------
    strSectionName = strSectionNameGeneral;
    for (iCnt1 = AppOptionSSHKey; iCnt1 <= AppOptionSSHIV; iCnt1++)
    {
        switch (iCnt1)
        {
        case AppOptionSSHKey:
            strTempKeyValue = ui->lneSSHKey->text();
            strKeyName = strGeneralSSHKeyKey;
            bEncrypted = false;
            break;
        case AppOptionSSHIV:
            strTempKeyValue = ui->lneSSHIV->text();
            strKeyName = strGeneralSSHIVKey;
            bEncrypted = false;
            break;
        default:
            break;
        }
        //-------------------------------------------------------------------------------
        //
        //  Compare value with value in memory
        //  Update is changed in memory and file
        //
        //-------------------------------------------------------------------------------
        if (lsGeneralOptions[iCnt1] != strTempKeyValue)
        {
            lsGeneralOptions[iCnt1] = strTempKeyValue;
            AppConfiguration->SetAppSettings(strSectionName,strKeyName,lsGeneralOptions[iCnt1], bEncrypted);
        }
    }

    //-----------------------------------------------------------------------------------
    //
    //  Application database options
    //
    //-----------------------------------------------------------------------------------
    strSectionName = strSectionNameAppDB;
    for (iCnt1 = AppOptionServerIP; iCnt1 <= AppOptionAppDBPassword; iCnt1++)
    {
        switch (iCnt1)
        {
        case AppOptionServerIP:
            strTempKeyValue = ui->lneAppServerIP->text();
            strKeyName = strAppDBServerIPKey;
            bEncrypted = false;
            break;
        case AppOptionServerPort:
            strTempKeyValue = ui->lneAppServerPort->text();
            strKeyName = strAppDBServerPortKey;
            bEncrypted = false;
            break;
        case AppOptionAppDBName:
            strTempKeyValue = ui->lneAppDBName->text();
            strKeyName = strAppDBNameKey;
            bEncrypted = false;
            break;
        case AppOptionAppDBUserID:
            strTempKeyValue = ui->lneAppDBUserID->text();
            strKeyName = strAppDBUserIDKey;
            bEncrypted = false;
            break;
        case AppOptionAppDBPassword:
            strTempKeyValue = ui->lneAppDBPassword->text();
            strKeyName = strAppDBUserPasswordKey;
            bEncrypted = true;
            break;
        default:
            break;
        }
        //-------------------------------------------------------------------------------
        //
        //  Compare value with value in memory
        //  Update is changed in memory and file
        //
        //-------------------------------------------------------------------------------
        if (lsAppDBOptions[iCnt1] != strTempKeyValue)
        {
            lsAppDBOptions[iCnt1] = strTempKeyValue;
            AppConfiguration->SetAppSettings(strSectionName,strKeyName,lsAppDBOptions[iCnt1], bEncrypted);
        }
    }

}

