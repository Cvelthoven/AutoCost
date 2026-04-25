#ifndef DATAINPUTDIALOG_H
#define DATAINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class DataInputDialog;
}

class DataInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataInputDialog(QWidget *parent = nullptr);
    ~DataInputDialog();

private:
    Ui::DataInputDialog *ui;
};

#endif // DATAINPUTDIALOG_H
