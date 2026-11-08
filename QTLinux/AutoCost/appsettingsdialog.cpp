//---------------------------------------------------------------------------------------
//
//  Module: appsettings.cpp
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "appsettingdatamodel.h"
#include "appsettingsdialog.h"
#include "ui_appsettingsdialog.h"
#include "AutoCost.h"

#include <QString>

//---------------------------------------------------------------------------------------
//
//  AppSettings default constructor
//
//---------------------------------------------------------------------------------------
AppSettingsDialog::AppSettingsDialog(QWidget *parent,
                                     AppSettingDataModel *AppnConf)
    : QDialog(parent)
    , ui(new Ui::AppSettingsDialog)
{
    //-----------------------------------------------------------------------------------
    //
    //  Local variables
    //
    int iCnt;

    QString
        strTempSectionName ="",
        strTempKeyName = "",
        strTempKeyValue = "";

    ui->setupUi(this);

    ApplicationConfiguration = AppnConf;
    //-----------------------------------------------------------------------------------
    //
    //  Application database options
    //
    stvDBOptions = ApplicationConfiguration->getStvAppDBConf();
    for (int iCnt1 = AppOptionServerIP; iCnt1 <= AppOptionAppDBPassword; iCnt1++)
    {
        switch (iCnt1)
        {
        case AppOptionServerIP:
            ui->lneAppServerIP->setText(stvDBOptions[iCnt1]);
            break;
        case AppOptionServerPort:
            ui->lneAppServerPort->setText(stvDBOptions[iCnt1]);
            break;
        case AppOptionAppDBName:
            ui->lneAppDBName->setText(stvDBOptions[iCnt1]);
            break;
        case AppOptionAppDBUserID:
            ui->lneAppDBUserID->setText(stvDBOptions[iCnt1]);
            break;
        case AppOptionAppDBPassword:
            ui->lneAppDBPassword->setText(stvDBOptions[iCnt1]);
            break;
        default:
            break;
        }
    }
    //-----------------------------------------------------------------------------------
    //
    //  Load session defaults
    //
    dKWhDef = ApplicationConfiguration->getDKWhDef();
    ui->lnLoadSesDefKWh->setText(QString::number(dKWhDef, 'f', 1));
    iLoadSessionEndPercentage = ApplicationConfiguration->getIAccuDefEndPercentage();
    ui->lnLoadSesDefAccuEnd->setText(QString::number(iLoadSessionEndPercentage));

    //-----------------------------------------------------------------------------------
    //
    //  Miscellaneous options
    //
    iMillageYear = ApplicationConfiguration->getIMillageYear();
    ui->lnMiscMillageYear->setText(QString::number(iMillageYear));


    //-----------------------------------------------------------------------------------
    //
    //  Execute dialog
    //
    AppSettingsDialog::exec();

}

//---------------------------------------------------------------------------------------
//
//  AppSettings default destructor
//
//---------------------------------------------------------------------------------------
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

    //-----------------------------------------------------------------------------------
    //
    //  Local variables
    //
    //----------------------------------------------------------------------------------
    int iCnt1;

    QString
        strTempKeyValue = "";

    //-----------------------------------------------------------------------------------
    //
    //  Application database options
    //
    for (iCnt1 = AppOptionServerIP; iCnt1 <= AppOptionAppDBPassword; iCnt1++)
    {
        switch (iCnt1)
        {
        case AppOptionServerIP:
            strTempKeyValue = ui->lneAppServerIP->text();
            break;
        case AppOptionServerPort:
            strTempKeyValue = ui->lneAppServerPort->text();
            break;
        case AppOptionAppDBName:
            strTempKeyValue = ui->lneAppDBName->text();
            break;
        case AppOptionAppDBUserID:
            strTempKeyValue = ui->lneAppDBUserID->text();
            break;
        case AppOptionAppDBPassword:
            strTempKeyValue = ui->lneAppDBPassword->text();
            break;
        default:
            break;
        }
        //-------------------------------------------------------------------------------
        //
        //  Compare value with value in memory
        //  Update is changed in memory and file
        //
        if (stvDBOptions[iCnt1] != strTempKeyValue)
        {
            stvDBOptions[iCnt1] = strTempKeyValue;
            bOptionChanged = true;
        }
    }

    //-----------------------------------------------------------------------------------
    //
    //  Update Application database options if changed
    //
    if (bOptionChanged)
    {
        ApplicationConfiguration->setStvAppDBConf(stvDBOptions);
    }

    //-----------------------------------------------------------------------------------
    //
    //  Load session defaults
    //
    dKWhDef = ui->lnLoadSesDefKWh->text().toDouble();
    if (dKWhDef != ApplicationConfiguration->getDKWhDef())
    {
        ApplicationConfiguration->setDKWhDef(dKWhDef);
    }
    iLoadSessionEndPercentage = ui->lnLoadSesDefAccuEnd->text().toInt();
    if (iLoadSessionEndPercentage != ApplicationConfiguration->getIAccuDefEndPercentage())
    {
        ApplicationConfiguration->setIAccuDefEndPercentage(iLoadSessionEndPercentage);
    }

    //-----------------------------------------------------------------------------------
    //
    //  Miscellaneous options
    //
    iMillageYear = ui->lnLoadSesDefAccuEnd->text().toInt();
    if (iMillageYear != ApplicationConfiguration->getIMillageYear())
    {
        ApplicationConfiguration->setIMillageYear(iMillageYear);
    }

}

