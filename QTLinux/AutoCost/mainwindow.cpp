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
    ApplicationConfig = new AppSettings(strApplicationDomain,
                                        strApplicationName,
                                        strApplicationOrganization);


    //-----------------------------------------------------------------------------------
    //
    // Build and Test values !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // QString strTestSectionName = "General";
    // QString strTestKeyName = "SSHKey";
    // QString strTestKeyValue = "SSHKeyValue01";

    // if (ApplicationConfig->SetAppSettings(strTestSectionName, strTestKeyName, strTestKeyValue) != 0)
    // {
    //     return 0;
    // }
    // strTestKeyName = "SSHIV";
    // strTestKeyValue = "SSHIV01";
    // if (ApplicationConfig->SetAppSettings(strTestSectionName, strTestKeyName, strTestKeyValue) != 0)
    // {
    //     return 0;
    // }
    // strTestSectionName = "Application database";
    // strTestKeyName = "Server";
    // strTestKeyValue = "Server01";
    // if (ApplicationConfig->SetAppSettings(strTestSectionName, strTestKeyName, strTestKeyValue) != 0)
    // {
    //     return 0;
    // }


    //------------- End test part !!!!!!!!!!!!!!!!!!!!!    ------------------------------
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


void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

