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
    , ui(new Ui::MainWindow),
    DetailCostDataModelTable(new DetailCostDataModel(this))
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

    //-----------------------------------------------------------------------------------
    //
    //  Create the view
    //


    //-----------------------------------------------------------------------------------
    //
    //  Set the model for the view (this connects them)
    //
    //
    ui->tblDetailOverview->setModel(DetailCostDataModelTable);

    //-----------------------------------------------------------------------------------
    //
    //  Set the view to tblDetailOverview
    //
    // setCentralWidget(DetailCostDataViewTable);


    //-----------------------------------------------------------------------------------
    //
    //  Load initial data
    // if (!DetailCostDataViewTable->loadData())
    // {
    //     qWarning() << "Error loading detail cost data";
    // }

    // Connect signals if needed
    // connect(ui->actionRefresh, &QAction::triggered, DetailCostDataViewTable, [this]() {
    //     DetailCostDataViewTable->loadData();
    // });
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
 //   delete DetailCostDataViewTable;
    delete DetailCostDataModelTable;
 //   delete AutoCostDetails;
 //   delete AppDatabase;
 //   delete ApplicationConfig;

}

//---------------------------------------------------------------------------------------
//
//  MainWindow methodes
//
//---------------------------------------------------------------------------------------
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
//
//  OpenAutoCostDetails
//
//  Creates an table overview of the auto cost details
//
//---------------------------------------------------------------------------------------
int MainWindow::OpenAutoCostDetails()
{

    //-----------------------------------------------------------------------------------
    //
    //  Create an instance of details autocost overview
    //
 //   AutoCostDetails = new DetailCostTableModel();
    qDebug() << "Constructor DetailCostDataView called in MainWindow->OpenAutoCostDetails";

//    DetailCostDataViewTable = new DetailCostDataView();

    //-----------------------------------------------------------------------------------
    //
    //  Create the view of the detail cost
    //
    //-----------------------------------------------------------------------------------
    // ui->tblDetailOverview->setModel(AutoCostDetails);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewRecID, 20);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewRecType, 20);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewDate, 90);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewDescription, 300);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewPeriodic, 75);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewElectricity, 75);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewOther, 75);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewAccessory, 75);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewMillage, 60);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewMillageTrip, 60);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewKWhTrip, 60);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewKWhLoaded, 80);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewKWhperKM, 60);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewAvgEuroPerKWh, 90);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewKWhPerPercentage, 60);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewKMPerPercentage, 60);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewAccuStartPercentage, 75);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewAccuEndPercentage, 75);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewAccuUsagePercentage, 80);
    // ui->tblDetailOverview->setColumnWidth(CostOverViewAccuLoadDeltaPercentage, 75);

    return 0;
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

