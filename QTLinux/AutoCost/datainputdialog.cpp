#include "datainputdialog.h"
#include "ui_datainputdialog.h"

DataInputDialog::DataInputDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DataInputDialog)
{
    ui->setupUi(this);
}

DataInputDialog::~DataInputDialog()
{
    delete ui;
}
