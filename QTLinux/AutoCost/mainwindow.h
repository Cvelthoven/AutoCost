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
#include "datainput.h"
#include "datainputdialog.h"
#include "detailcostdataview.h"
#include "detailcosttablemodel.h"// needs to be removed
#include "postgresqldb.h"

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
    int ConnectApplicationDataDB();
    int OpenAutoCostDetails();
    int ProgramConfigurationLoad();

    //-----------------------------------------------------------------------------------
    //
    //  Private variables
    //
    //-----------------------------------------------------------------------------------
    AppConfiguration* ApplicationConfiguration = nullptr;
    DataInput* ManualData = nullptr;
    DetailCostDataView* DetailCostDataViewTable = nullptr;
    DetailCostTableModel *AutoCostDetails = nullptr;// needs to be removed
    PostGreSQLDB* AppDataDB = nullptr;


};
#endif // MAINWINDOW_H
