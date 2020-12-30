#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//---------------------------------------------------------------------------------------
//
//  AutoCost: mainwindow
//
//---------------------------------------------------------------------------------------
//
//  General QT header files
#include <QMainWindow>

//---------------------------------------------------------------------------------------
//
// AutoCost specific header files
#include "applicationsettingsdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_FileExit_triggered();

    void on_action_ToolsOptions_triggered();

private:
    Ui::MainWindow *ui;
    ApplicationSettingsDialog *AppSettingDialog;
};
#endif // MAINWINDOW_H
