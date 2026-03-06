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
    //  Fill the dialog with the found values
    //
    //-----------------------------------------------------------------------------------

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
