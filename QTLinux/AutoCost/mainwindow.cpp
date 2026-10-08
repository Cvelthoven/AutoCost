//---------------------------------------------------------------------------------------
//
//  Module: mainwindow.cpp
//
//  Main module the handles the GUI of the application
//
//---------------------------------------------------------------------------------------
#include "AutoCost.h"
#include "detailcostdatamodel.h"
#include "mainwindow.h"
#include "millageoverviewdatamodel.h"
#include "./ui_mainwindow.h"
#include "postgresqldb.h"
#include "totalcostdatamodel.h"

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
    if (ProgramConfigurationLoad() != 0)
    {
        exit(0);
    }


    //-----------------------------------------------------------------------------------
    //
    //  Activate the GUI of the application
    //  This creates the elements of the MainWindow
    //
    ui->setupUi(this);

    //-----------------------------------------------------------------------------------
    //
    //  Create connection to database
    //
    if (ConnectApplicationDataDB() != 0)
    {
        exit(0);
    }

    //-----------------------------------------------------------------------------------
    //
    //  DetailCostDataModelTable:
    //  - Create
    //  - Load data
    //  - set data model
    //  - configure view
    //
    //  Detail cost must be before total cost
    //
    //-----------------------------------------------------------------------------------
    //
    //  Create and load data
    //
    DetailCostDataModelTable = new DetailCostDataModel(this);
    if (!DetailCostDataModelTable->loadDetailCostData())
    {
        exit(0);
    }

    //-----------------------------------------------------------------------------------
    //
    //  Set the model for the detailed cost view (this connects them)
    //  and configure the view
    //
    ui->tblDetailOverview->setModel(DetailCostDataModelTable);
    ConfigureAutoCostDetails();

    //-----------------------------------------------------------------------------------
    //
    //  TotallCostDataModelTable:
    //  - Create
    //  - Load data
    //  - set data model
    //  - configure view
    //
    //  Must be after detail cost due to data used from detail cost
    //
    //-----------------------------------------------------------------------------------
    //
    //  Create and load data
    //
    TotallCostDataModelTable = new TotalCostDataModel(this);
    TotallCostDataModelTable->loadTotals(*DetailCostDataModelTable);

    //-----------------------------------------------------------------------------------
    //
    //  Set the model for the total cost view (this connects them)
    //  and configure the view
    //
    ui->tblYearTotalOverview->setModel(TotallCostDataModelTable);
    ConfigureAutoTotalCost();

    //-----------------------------------------------------------------------------------
    //
    //  MillageDataModelTable:
    //  - Create
    //  - Load data
    //  - set data model
    //  - configure view
    //
    //  Must be after detail cost due to data used from detail cost
    //
    //-----------------------------------------------------------------------------------
    //
    //  Create and load data
    //
    MillageDataModelTable = new MillageOverviewDataModel(this);
    if (!MillageDataModelTable->loadMillageData(*DetailCostDataModelTable))
    {
        exit(0);
    }

    //-----------------------------------------------------------------------------------
    //
    //  Set the model for the total cost view (this connects them)
    //  and configure the view
    //
     ui->tblMillageOverview->setModel(MillageDataModelTable);
    MillageOverviewTable();

}

//---------------------------------------------------------------------------------------
//
//  MainWindow destructor
//
//---------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    AppDataDB->close();
    delete ui;
//    delete ManualDataInput; // cause crash needs further investigation
    delete TotallCostDataModelTable;
    delete MillageDataModelTable;
    // Must be last contains data used by other classes
    delete DetailCostDataModelTable;
}

//---------------------------------------------------------------------------------------
//
//  MainWindow methodes
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  ConfigureAutoCostDetails
//
//  Sets the column width of the detail cost table view
//
//---------------------------------------------------------------------------------------
void MainWindow::ConfigureAutoCostDetails()
{
    //-----------------------------------------------------------------------------------
    //
    //  Set row alternating colors
    //
    ui->tblDetailOverview->setAlternatingRowColors(true);

    //-----------------------------------------------------------------------------------
    //
    //  Set row alternating colors
    //
    ui->tblDetailOverview->setColumnWidth(CostOverViewDate, 90);
    ui->tblDetailOverview->setColumnWidth(CostOverViewDescription, 330);
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
    //  Following fields must be hidden in final release
    ui->tblDetailOverview->setColumnWidth(CostOverViewRecID, 20);
    ui->tblDetailOverview->setColumnWidth(CostOverViewElecRecId, 20);
    ui->tblDetailOverview->setColumnWidth(CostOverViewRecType, 20);
    ui->tblDetailOverview->setColumnWidth(CostOverViewPeriod, 20);
}

//---------------------------------------------------------------------------------------
//
//  ConfigureAutoTotalCost
//
//  Sets the column width of the total cost table view
//
//---------------------------------------------------------------------------------------
void MainWindow::MillageOverviewTable()
{
    //-----------------------------------------------------------------------------------
    //
    //  Set row alternating colors
    //
    ui->tblMillageOverview->setAlternatingRowColors(true);

    //-----------------------------------------------------------------------------------
    //
    //  Set column width
    //
    ui->tblMillageOverview->setColumnWidth(MillageOverviewYear, 60);
    ui->tblMillageOverview->setColumnWidth(MillageOverviewStart, 80);
    ui->tblMillageOverview->setColumnWidth(MillageOverviewCurrent, 80);
    ui->tblMillageOverview->setColumnWidth(MillageOverviewLimit, 80);
    ui->tblMillageOverview->setColumnWidth(MillageOverviewUsed, 80);
    ui->tblMillageOverview->setColumnWidth(MillageOverviewRemaining, 80);
}

//---------------------------------------------------------------------------------------
//
//  ConfigureAutoTotalCost
//
//  Sets the column width of the total cost table view
//
//---------------------------------------------------------------------------------------
void MainWindow::ConfigureAutoTotalCost()
{
    //-----------------------------------------------------------------------------------
    //
    //  Set row alternating colors
    //
     ui->tblYearTotalOverview->setAlternatingRowColors(true);

    //-----------------------------------------------------------------------------------
    //
    //  Set column width
    //
    ui->tblYearTotalOverview->setColumnWidth(TotalCostViewYear, 60);
    ui->tblYearTotalOverview->setColumnWidth(TotalCostViewTotal, 80);
    ui->tblYearTotalOverview->setColumnWidth(TotalCostViewPeriodic, 80);
    ui->tblYearTotalOverview->setColumnWidth(TotalCostViewElectricity, 80);
    ui->tblYearTotalOverview->setColumnWidth(TotalCostViewOther, 80);
    ui->tblYearTotalOverview->setColumnWidth(TotalCostViewAccessory, 80);
}

//---------------------------------------------------------------------------------------
//
//  ConnectApplicationDataDB
//
//---------------------------------------------------------------------------------------
int MainWindow::ConnectApplicationDataDB()
{
    int iRC = 0;

    //-----------------------------------------------------------------------------------
    //
    //  Create connection to application data database
    //
    AppDataDB = &PostGreSQLDB::instance();

    //-----------------------------------------------------------------------------------
    //
    //  Configure the database connection
    //
    AppDataDB->configure(
        ApplicationConfiguration->ApplicationDBConfig[DBServerIP],
        ApplicationConfiguration->ApplicationDBConfig[DBServerPort].toInt(),
        ApplicationConfiguration->ApplicationDBConfig[DBName],
        ApplicationConfiguration->ApplicationDBConfig[DBAppUserId],
        ApplicationConfiguration->ApplicationDBConfig[DBAppPassword],
        strApplicationDatabaseConnectionName);

    //-----------------------------------------------------------------------------------
    //
    //  Open database connection
    //
    if (!AppDataDB->open())
    {
        qDebug() << "Connection " << strApplicationDatabaseConnectionName << " failed";
        iRC = 1;
    }

    return iRC;
}

//---------------------------------------------------------------------------------------
//  ProgramConfigurationLoad
//
//  Creates an applicattionSetting instance
//
//---------------------------------------------------------------------------------------
int MainWindow::ProgramConfigurationLoad()
{

    //-----------------------------------------------------------------------------------
    //
    //  Retrieve the application configuration available at startup of application
    //
    //-----------------------------------------------------------------------------------
    ApplicationConfiguration = new AppConfiguration();
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
    qDebug() << "Constructor of DataInputDialog called from MainWindow on_actionManual_Data_input_triggered";
    ManualDataInput = new DataInputDialog;
//    ManualDataInput = new DataInputDialog(ApplicationConfiguration);

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
