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
#include "appsettings.h"
#include "appsettingsdialog.h"
//#include "detailcostsqlmodel.h"
#include "detailcosttablemodel.h"
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

private slots:
    void on_actionOptions_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;

    //-----------------------------------------------------------------------------------
    //
    //  Private methods
    //
    //-----------------------------------------------------------------------------------
    int ProgramConfigurationLoad();
    int OpenAutoCostDetails();

    //-----------------------------------------------------------------------------------
    //
    //  Private variables
    //
    //-----------------------------------------------------------------------------------
    AppSettings *ApplicationConfig;
    DetailCostTableModel *AutoCostDetails;
    PostGreSQLDB *AppDatabase;


};
#endif // MAINWINDOW_H
