#ifndef APPLICATIONSETTINGSDIALOG_H
#define APPLICATIONSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class ApplicationSettingsDialog;
}

class ApplicationSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ApplicationSettingsDialog(QWidget *parent = nullptr);
    ~ApplicationSettingsDialog();

private slots:
    void on_buttonBox_rejected();

private:
    Ui::ApplicationSettingsDialog *ui;
};

#endif // APPLICATIONSETTINGSDIALOG_H
