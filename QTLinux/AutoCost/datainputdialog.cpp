//---------------------------------------------------------------------------------------
//
//  Module: datainputdialog.cpp
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "AutoCost.h"
#include "datainputdialog.h"
#include "ui_datainputdialog.h"

#include <QAbstractButton>
#include <QDialogButtonBox>
#include <QDate>
#include <QTime>

//---------------------------------------------------------------------------------------
//
//  DataInputDialog default constructor
//
//---------------------------------------------------------------------------------------
DataInputDialog::DataInputDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DataInputDialog)
{

    //-----------------------------------------------------------------------------------
    //
    //  Local variables
    //
    //-----------------------------------------------------------------------------------

    ui->setupUi(this);

    //-----------------------------------------------------------------------------------
    //
    //  Preload fields
    //
    //-----------------------------------------------------------------------------------
    //
    //  Date and time field and label
    //
    //-----------------------------------------------------------------------------------
    ui->deRecordDate->setDisplayFormat(strDateFormat);
    ui->teStartTime->setDisplayFormat(strStartTimeFormat);
    ui->lblKWhTime1->setText("");

    //-----------------------------------------------------------------------------------
    //
    //  Set the radiobutton id's
    //
    //-----------------------------------------------------------------------------------
    ui->CostButtonGroup->setId(ui->rbPeriodic, 1);
    ui->CostButtonGroup->setId(ui->rbElectricity, 2);
    ui->CostButtonGroup->setId(ui->rbOther, 3);
    ui->CostButtonGroup->setId(ui->rbAccessoires, 4);

    //-----------------------------------------------------------------------------------
    //
    //  Fill the dialog with the default values
    //
    //-----------------------------------------------------------------------------------
    resetDialog();
}

//---------------------------------------------------------------------------------------
//
//  DataInputDialog default destructor
//
//---------------------------------------------------------------------------------------
DataInputDialog::~DataInputDialog()
{
    delete ui;
}

//---------------------------------------------------------------------------------------
//
//  Handle different responses on DataInputDialog
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    //-----------------------------------------------------------------------------------
    //
    //  Select action based on which button is clicked
    //
    //-----------------------------------------------------------------------------------
    QDialogButtonBox::StandardButton which = ui->buttonBox->standardButton(button);
    switch (which)
    {
    //-----------------------------------------------------------------------------------
    //
    //  Retrieve the input data and store it in the database
    //  And reset the dialog to the default again
    //
    //-----------------------------------------------------------------------------------
    case QDialogButtonBox::Apply:
        onApplyPressed();
        accept();
        break;

    //-----------------------------------------------------------------------------------
    //
    //  Close the dialog without saving possible input
    //
    //-----------------------------------------------------------------------------------
    case QDialogButtonBox::Cancel:
        onCancelPressed();
        reject();
        break;

    //-----------------------------------------------------------------------------------
    //
    //  Retrieve the input data and store it in the database
    //  And close the dialog
    //
    //-----------------------------------------------------------------------------------
    case QDialogButtonBox::Close:
        onClosePressed();
        break;

    //-----------------------------------------------------------------------------------
    //
    //  Discard possible input data
    //  And reset the dialog to the default again
    //
    //-----------------------------------------------------------------------------------
    case QDialogButtonBox::Discard:
        onDiscardPressed();
        break;

    default:
        break;
    }

}

//---------------------------------------------------------------------------------------
//
//  Retrieve the input data and store it in the database
//  And reset the dialog to the default again
//
//---------------------------------------------------------------------------------------
void DataInputDialog::onApplyPressed()
{
    retrieveData();
    resetDialog();
}

//---------------------------------------------------------------------------------------
//
//  Close the dialog without saving possible input
//
//---------------------------------------------------------------------------------------
void DataInputDialog::onCancelPressed()
{

}

//---------------------------------------------------------------------------------------
//
//  Retrieve the input data and store it in the database
//  And close the dialog
//
//---------------------------------------------------------------------------------------
void DataInputDialog::onClosePressed()
{
    retrieveData();
}

//---------------------------------------------------------------------------------------
//
//  Discard possible input data
//  And reset the dialog to the default again
//
//---------------------------------------------------------------------------------------
void DataInputDialog::onDiscardPressed()
{
    resetDialog();
}


//---------------------------------------------------------------------------------------
//
//  Retrieve input data from dialog
//  Except the electricity data
//
//---------------------------------------------------------------------------------------
void DataInputDialog::retrieveData()
{
    QString strAmount = "";

    //-----------------------------------------------------------------------------------
    //
    //  Retrieve data
    //
    //-----------------------------------------------------------------------------------
    strDate = ui->deRecordDate->date().toString(strDateFormat);
    strDescription = ui->lnDescription->text();
    strAmount = ui->lnAmount->text();
    strStartTime = ui->teStartTime->time().toString(strStartTimeFormat);
    // int iCostTypeID = ui->CostButtonGroup->checkedId();
    // if (iCostTypeID != -1)
    // {

    // }
}

//---------------------------------------------------------------------------------------
//
//  Handle radiobuttons cost type
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_rbPeriodic_toggled(bool checked)
{
    if (checked)
    {
        iCostType = CostRecPeriodic;
     }
    else
    {
        iCostType = 0;
    }
}

void DataInputDialog::on_rbElectricity_toggled(bool checked)
{
    if (checked)
    {
        iCostType = CostRecElectricity;
        ui->lnDescription->setText("Laden");
        ui->teStartTime->setDisplayFormat(strStartTimeFormat);
        ui->teStartTime->setTime(QTime::fromString("00:00"));
        ui->lnKWh1->setText("0.00");
        ui->lnPriceKWh1->setText("0.00");
    }
    else
    {
        iCostType = 0;
        clearElectricityInput();
    }
}


void DataInputDialog::on_rbOther_toggled(bool checked)
{
    if (checked)
    {
        iCostType = CostRecOther;
    }
    else
    {
        iCostType = 0;
    }
}


void DataInputDialog::on_rbAccessoires_toggled(bool checked)
{
    if (checked)
    {
        iCostType = CostRecAccessory;
    }
    else
    {
        iCostType = 0;
    }
}

//---------------------------------------------------------------------------------------
//
//  Slots that handle input from dialog fields
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  Retrieve time set by user
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_teStartTime_userTimeChanged(const QTime &time)
{
    //-----------------------------------------------------------------------------------
    //
    //  Only retrieve time when cost type is electricity otherwise ignore or discard
    //
    //-----------------------------------------------------------------------------------
    if (iCostType == 2)
    {
        tiStartTime = ui->teStartTime->time();
        strStartTime = tiStartTime.toString("hh:mm");
        ui->lblKWhTime1->setText(strStartTime);
    }


}

//---------------------------------------------------------------------------------------
//
//  Other methods
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  Clear electricity input when switching cost type
//
//---------------------------------------------------------------------------------------
void DataInputDialog::clearElectricityInput()
{
    ui->lnKWh1->clear();
    ui->lnKWh2->clear();
    ui->lnKWh3->clear();
    ui->lnKWh4->clear();
    ui->lnKWh5->clear();
    ui->lnKWh6->clear();
    ui->lnKWh7->clear();
    ui->lnKWh8->clear();
    ui->lnKWh9->clear();
    ui->lnKWhMax->clear();
    ui->lnPriceKWh1->clear();
    ui->lnPriceKWh2->clear();
    ui->lnPriceKWh3->clear();
    ui->lnPriceKWh4->clear();
    ui->lnPriceKWh5->clear();
    ui->lnPriceKWh6->clear();
    ui->lnPriceKWh7->clear();
    ui->lnPriceKWh8->clear();
    ui->lnPriceKWh9->clear();
    ui->lnTotalKWh->clear();
    ui->lblKWhTime1->setText("");

}

//---------------------------------------------------------------------------------------
//
//  Reset the dialog to the default again
//
//---------------------------------------------------------------------------------------
void DataInputDialog::resetDialog()
{
    ui->deRecordDate->setDate(QDate::currentDate());
    ui->lnDescription->clear();
    ui->lnAmount->clear();
    ui->teStartTime->clear();
    clearElectricityInput();

}
