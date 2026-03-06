//---------------------------------------------------------------------------------------
//
//  Module: mainwindow.cpp
//
//  Main module the handles the GUI of the application
//
//---------------------------------------------------------------------------------------
#include "AutoCost.h"
#include "appsettings.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QString>

#include <QDebug>

//---------------------------------------------------------------------------------------
//
//  MainWindow constructor
//
//---------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //-----------------------------------------------------------------------------------
    //
    //  Load the Program configuration
    //
    //-----------------------------------------------------------------------------------
    if (ProgramConfigurationLoad() != 0)
    {
        exit(0);
    }

    //-----------------------------------------------------------------------------------
    //
    //  Activate the GUI of the application
    //
    //-----------------------------------------------------------------------------------
    ui->setupUi(this);
}

//---------------------------------------------------------------------------------------
//
//  MainWindow destructor
//
//---------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//---------------------------------------------------------------------------------------
//
//  MainWindow methodes
//
//---------------------------------------------------------------------------------------
//
//  ProgramConfigurationLoad
//
//  Creates an applicattionSetting instance
//
//---------------------------------------------------------------------------------------
int MainWindow::ProgramConfigurationLoad()
{

    //-----------------------------------------------------------------------------------
    //
    //  Create instance of AppSettings and configure the instance
    //
    //-----------------------------------------------------------------------------------
    ApplicationConfig = new AppSettings;
    ApplicationConfig->SetApplicationDomain(strApplicationDomain);
    ApplicationConfig->SetApplicationOrganization(strApplicationOrganization);
    ApplicationConfig->SetApplicationName(strApplicationName);


    //----------------------------------------------------------------------------
    //
    // Build and Test values !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    QString strTestSectionName = "General";
    QString strTestKeyName = "TestKey01";
    QString strTestKeyValue = "TestValue01";

    if (ApplicationConfig->SetAppSettings(strTestSectionName, strTestKeyName, strTestKeyValue) != 0)
    {
        return 0;
    }
    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    strTestKeyValue = "";
    if (ApplicationConfig->GetAppSettings(strTestSectionName, strTestKeyName, strTestKeyValue) != 0)
    {
        return 0;
    }

    return 0;
}

//---------------------------------------------------------------------------------------
//
//  Main menu slots
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  Menu -> File -> Options
//
//---------------------------------------------------------------------------------------
void MainWindow::on_actionOptions_triggered()
{
    ApplicationSettings = new AppSettingsDialog;

}

