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

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;

    int ProgramConfigurationLoad();
    AppSettings *ApplicationConfig;
};
#endif // MAINWINDOW_H
