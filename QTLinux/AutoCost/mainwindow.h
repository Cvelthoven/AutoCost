//---------------------------------------------------------------------------------------
//
//  Module: mainwindow.h
//
//---------------------------------------------------------------------------------------
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "appconfiguration.h"
#include "appsettingsdialog.h"
#include "averagecostdatamodel.h"
#include "datainput.h"
#include "datainputdialog.h"
#include "detailcostdatamodel.h"
#include "electricityoverviewdatamodel.h"
#include "millageoverviewdatamodel.h"
#include "postgresqldb.h"
#include "totalcostdatamodel.h"

#include <QMainWindow>
#include <QTableView>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    AppSettingsDialog *ApplicationSettings;
    DataInputDialog *ManualDataInput;
    QTableView DetailCostView;

private slots:
    void on_actionOptions_triggered();

    void on_actionExit_triggered();

    void on_actionManual_Data_input_triggered();

private:
    Ui::MainWindow *ui;

    //-----------------------------------------------------------------------------------
    //
    //  Private methods
    //
    //-----------------------------------------------------------------------------------
    void AverageCostOverviewTable();
    void ConfigureAutoCostDetails();
    void ConfigureAutoTotalCost();
    void ElectricityOverviewTable();
    void MillageOverviewTable();
    int ConnectApplicationDataDB();
    int ProgramConfigurationLoad();

    //-----------------------------------------------------------------------------------
    //
    //  Private variables
    //
    //-----------------------------------------------------------------------------------
    AppConfiguration* ApplicationConfiguration = nullptr;
    AverageCostDataModel* AverageCostDataModelTable = nullptr;
    DataInput* ManualData = nullptr;
    DetailCostDataModel* DetailCostDataModelTable = nullptr;
    ElectricityOverviewDataModel* ElectricityDataModelTable = nullptr;
    MillageOverviewDataModel* MillageDataModelTable = nullptr;
    PostGreSQLDB* AppDataDB = nullptr;
    TotalCostDataModel* TotallCostDataModelTable = nullptr;

};
#endif // MAINWINDOW_H
