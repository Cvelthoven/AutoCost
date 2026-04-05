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
#include <QTableView>

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
    //  Load detailed auto cost records from the database
    //
    //-----------------------------------------------------------------------------------
    if (OpenAutoCostDetails() != 0)
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
    delete AutoCostDetails;
    delete ApplicationConfig;
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

    return 0;
}

//---------------------------------------------------------------------------------------
//
//  OpenAutoCostDetails
//
//  Creates an AppDatabase instance
//
//---------------------------------------------------------------------------------------
int MainWindow::OpenAutoCostDetails()
{
    //-----------------------------------------------------------------------------------
    //
    //  Create an instance of details autocost overview
    //
    //-----------------------------------------------------------------------------------
    AutoCostDetails = new DetailCostTableModel();

    //-----------------------------------------------------------------------------------
    //
    //  Create the view of the detail cost
    //
    //-----------------------------------------------------------------------------------
    DetailCostView.setModel(AutoCostDetails);
    DetailCostView.show();

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

