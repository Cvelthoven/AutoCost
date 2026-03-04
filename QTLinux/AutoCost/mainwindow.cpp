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
    if (!ProgramConfigurationLoad())
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
    return 0;

    //----------------------------------------------------------------------------
    //
    // Build and Test values !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    QString strTestSectionName = "[General]";
    QString strTestKeyName = "TestKey01";
    QString strTestKeyValue = "TestValue01";
    //  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
