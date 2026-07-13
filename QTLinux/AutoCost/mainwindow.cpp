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
    //  Activate the GUI of the application
    //  This creates the elements of the MainWindow
    //
    //-----------------------------------------------------------------------------------
    ui->setupUi(this);

    //-----------------------------------------------------------------------------------
    //
    //  Load detailed auto cost records from the database
    //
    //-----------------------------------------------------------------------------------
    if (OpenAutoCostDetails() != 0)
    {
        exit(0);
    }

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
    ui->tblDetailOverview->setModel(AutoCostDetails);
    ui->tblDetailOverview->setColumnWidth(CostOverViewRecID, 20);
    ui->tblDetailOverview->setColumnWidth(CostOverViewRecType, 20);
    ui->tblDetailOverview->setColumnWidth(CostOverViewDate, 90);
    ui->tblDetailOverview->setColumnWidth(CostOverViewDescription, 300);
    ui->tblDetailOverview->setColumnWidth(CostOverViewPeriodic, 75);
    ui->tblDetailOverview->setColumnWidth(CostOverViewElectricity, 75);
    ui->tblDetailOverview->setColumnWidth(CostOverViewOther, 75);
    ui->tblDetailOverview->setColumnWidth(CostOverViewAccessory, 75);
    ui->tblDetailOverview->setColumnWidth(CostOverViewMillage, 60);
    ui->tblDetailOverview->setColumnWidth(CostOverViewMillageTrip, 60);
    ui->tblDetailOverview->setColumnWidth(CostOverViewKWhTrip, 60);
    ui->tblDetailOverview->setColumnWidth(CostOverViewKWhLoaded, 80);
    ui->tblDetailOverview->setColumnWidth(CostOverViewKWhperKM, 60);
    ui->tblDetailOverview->setColumnWidth(CostOverViewAvgEuroPerKWh, 90);
    ui->tblDetailOverview->setColumnWidth(CostOverViewKWhPerPercentage, 60);
    ui->tblDetailOverview->setColumnWidth(CostOverViewKMPerPercentage, 60);
    ui->tblDetailOverview->setColumnWidth(CostOverViewAccuStartPercentage, 75);
    ui->tblDetailOverview->setColumnWidth(CostOverViewAccuEndPercentage, 75);
    ui->tblDetailOverview->setColumnWidth(CostOverViewAccuUsagePercentage, 80);
    ui->tblDetailOverview->setColumnWidth(CostOverViewAccuLoadDeltaPercentage, 75);

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

//---------------------------------------------------------------------------------------
//
//  Menu -> Data input -> Manual input
//
//---------------------------------------------------------------------------------------
void MainWindow::on_actionManual_Data_input_triggered()
{
    ManualDataInput = new DataInputDialog;
    //-----------------------------------------------------------------------------------
    //
    //  Loop to handle multiple record input
    //
    //-----------------------------------------------------------------------------------
    while (true)
    {
        int rc = ManualDataInput->exec();
        if ((rc != QDialog::Accepted)||(ManualDataInput->getBClosePressed()))
            break;
        ManualDataInput->resetDialog();
    }


}

