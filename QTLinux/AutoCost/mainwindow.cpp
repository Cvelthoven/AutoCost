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
#include "./ui_mainwindow.h"
#include "postgresqldb.h"

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
    //  Create the detail cost data model and load data
    //
    DetailCostDataModelTable = new DetailCostDataModel(this);
    if (!DetailCostDataModelTable->loadDetailCostData())
    {
        exit(0);
    }


    //-----------------------------------------------------------------------------------
    //
    //  Set the model for the view (this connects them)
    //
    //
    ui->tblDetailOverview->setModel(DetailCostDataModelTable);
    ConfigureAutoCostDetails();

    //-----------------------------------------------------------------------------------
    //
    //  Set the view to tblDetailOverview
    //
    // setCentralWidget(DetailCostDataViewTable);

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
    delete ManualDataInput;
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
    //  Create the view of the detail cost
    //
    //-----------------------------------------------------------------------------------
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

