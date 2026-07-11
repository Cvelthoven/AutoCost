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
    ui->lblKWhTime2->setText("");
    ui->lblKWhTime3->setText("");
    ui->lblKWhTime4->setText("");
    ui->lblKWhTime5->setText("");
    ui->lblKWhTime6->setText("");
    ui->lblKWhTime7->setText("");
    ui->lblKWhTime8->setText("");
    ui->lblKWhTime9->setText("");
    ui->lblKWhTime10->setText("");


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

    //-----------------------------------------------------------------------------------
    //
    //  Retrieve data
    //
    //-----------------------------------------------------------------------------------
    daRecordDate = ui->deRecordDate->date();
//    strDate = ui->deRecordDate->date().toString(strDateFormat);
    strDescription = ui->lnDescription->text();
    dAmount = ui->lnAmount->text().toFloat();

}

//---------------------------------------------------------------------------------------
//
//  Handle radiobuttons cost type
//
//---------------------------------------------------------------------------------------
//
//  Handle periodic type
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

//---------------------------------------------------------------------------------------
//
//  Handle electricity type
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_rbElectricity_toggled(bool checked)
{
    if (checked)
    {
        iCostType = CostRecElectricity;
        setElectricityDefaultNonPublic();
    }
    else
    {
        iCostType = 0;
        clearElectricityInput();
    }
}

//---------------------------------------------------------------------------------------
//
//  Handle other type
//
//---------------------------------------------------------------------------------------
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

//---------------------------------------------------------------------------------------
//
//  Handle accessoires type
//
//---------------------------------------------------------------------------------------
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
//  Getter and Setter Methods
//
//---------------------------------------------------------------------------------------
//
//  Table: acAutoCost
//
//---------------------------------------------------------------------------------------
int DataInputDialog::getICostType() const
{
    return iCostType;
}

QDate DataInputDialog::getDaRecordDate() const
{
    return daRecordDate;
}

QString DataInputDialog::getStrDescription() const
{
    return strDescription;
}

double DataInputDialog::getDAmount() const
{
    return dAmount;
}

//---------------------------------------------------------------------------------------
//
//  Table: acElectricity
//
//---------------------------------------------------------------------------------------
bool DataInputDialog::getBPublicLoadSession() const
{
    return bPublicLoadSession;
}

int DataInputDialog::getIMillage() const
{
    return iMillage;
}

double DataInputDialog::getDTotalKWh() const
{
    return dTotalKWh;
}

int DataInputDialog::getIAccuEndPercentage() const
{
    return iAccuEndPercentage;
}

int DataInputDialog::getIAccuStartPercentage() const
{
    return iAccuStartPercentage;
}

QTime DataInputDialog::getTiStartTime() const
{
    return tiStartTime;
}

//---------------------------------------------------------------------------------------
//
//  Slots that handle input from dialog fields
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  on_lnAccuPercentageStart_editingFinished
//  Slot to handle the start percentage af the accu of the loading session
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_lnAccuPercentageStart_editingFinished()
{
    iAccuStartPercentage = ui->lnAccuPercentageStart->text().toInt();
}

//---------------------------------------------------------------------------------------
//
//  on_lnAccuPercentageEnd_editingFinished
//  Slot to handle the end percentage af the accu of the loading session
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_lnAccuPercentageEnd_editingFinished()
{
    iAccuEndPercentage = ui->lnAccuPercentageEnd->text().toInt();
}

//---------------------------------------------------------------------------------------
//
//  on_lnMillage_editingFinished
//  Slot to handle the millage at the start of a load session
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_lnMillage_editingFinished()
{
    iMillage = ui->lnMillage->text().toInt();
}

//---------------------------------------------------------------------------------------
//
//  Handle the switch between a non-public and public load session
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_rbPublicLoadSession_toggled(bool checked)
{
    if (checked)
    {
        bPublicLoadSession = true;
        setElectricityDefaultNonPublic();
    }
    else
    {
        bPublicLoadSession = false;
    }

}

//---------------------------------------------------------------------------------------
//
//  Slots to retrieve the KWH amount per hour
//  And set, if needed, the next hour ready
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_lnKWh1_editingFinished()
{
    dKWhPeriod[0] = ui->lnKWh1->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcNonPublicLoadPerSession(0);
        calcCostNonPublicElectricity();
        showNonPublicLoadSession();
    }
}

void DataInputDialog::on_lnKWh2_editingFinished()
{
    dKWhPeriod[1] = ui->lnKWh2->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcNonPublicLoadPerSession(1);
        calcCostNonPublicElectricity();
        showNonPublicLoadSession();
    }
}

void DataInputDialog::on_lnKWh3_editingFinished()
{
    dKWhPeriod[2] = ui->lnKWh3->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcNonPublicLoadPerSession(2);
        calcCostNonPublicElectricity();
        showNonPublicLoadSession();
    }
}

void DataInputDialog::on_lnKWh4_editingFinished()
{
    dKWhPeriod[3] = ui->lnKWh4->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcNonPublicLoadPerSession(3);
        calcCostNonPublicElectricity();
        showNonPublicLoadSession();
    }
}

void DataInputDialog::on_lnKWh5_editingFinished()
{
    dKWhPeriod[4] = ui->lnKWh5->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcNonPublicLoadPerSession(4);
        calcCostNonPublicElectricity();
        showNonPublicLoadSession();
    }
}

void DataInputDialog::on_lnKWh6_editingFinished()
{
    dKWhPeriod[5] = ui->lnKWh6->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcNonPublicLoadPerSession(5);
        calcCostNonPublicElectricity();
        showNonPublicLoadSession();
    }
}

void DataInputDialog::on_lnKWh7_editingFinished()
{
    dKWhPeriod[6] = ui->lnKWh7->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcNonPublicLoadPerSession(6);
        calcCostNonPublicElectricity();
        showNonPublicLoadSession();
    }
}

void DataInputDialog::on_lnKWh8_editingFinished()
{
    dKWhPeriod[7] = ui->lnKWh8->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcNonPublicLoadPerSession(7);
        calcCostNonPublicElectricity();
        showNonPublicLoadSession();
    }
}

void DataInputDialog::on_lnKWh9_editingFinished()
{
    dKWhPeriod[8] = ui->lnKWh9->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcNonPublicLoadPerSession(8);
        calcCostNonPublicElectricity();
        showNonPublicLoadSession();
    }
}

void DataInputDialog::on_lnKWh10_editingFinished()
{
    dKWhPeriod[9] = ui->lnKWh10->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcNonPublicLoadPerSession(9);
        calcCostNonPublicElectricity();
        showNonPublicLoadSession();
    }
}

//---------------------------------------------------------------------------------------
//
//  Slots to retrieve the price KWh
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_lnPriceKWh1_editingFinished()
{
    dKWhPrice[0] = ui->lnPriceKWh1->text().toDouble();
    bFirstLoadPeriodChanged = true;
    if (!bPublicLoadSession)
    {
        calcCostNonPublicElectricity();
    }
}

void DataInputDialog::on_lnPriceKWh2_editingFinished()
{
    dKWhPrice[1] = ui->lnPriceKWh2->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcCostNonPublicElectricity();
    }
}

void DataInputDialog::on_lnPriceKWh3_editingFinished()
{
    dKWhPrice[2] = ui->lnPriceKWh3->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcCostNonPublicElectricity();
    }
}

void DataInputDialog::on_lnPriceKWh4_editingFinished()
{
    dKWhPrice[3] = ui->lnPriceKWh4->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcCostNonPublicElectricity();
    }
}

void DataInputDialog::on_lnPriceKWh5_editingFinished()
{
    dKWhPrice[4] = ui->lnPriceKWh5->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcCostNonPublicElectricity();
    }
}

void DataInputDialog::on_lnPriceKWh6_editingFinished()
{
    dKWhPrice[5] = ui->lnPriceKWh6->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcCostNonPublicElectricity();
    }
}

void DataInputDialog::on_lnPriceKWh7_editingFinished()
{
    dKWhPrice[6] = ui->lnPriceKWh7->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcCostNonPublicElectricity();
    }
}

void DataInputDialog::on_lnPriceKWh8_editingFinished()
{
    dKWhPrice[7] = ui->lnPriceKWh8->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcCostNonPublicElectricity();
    }
}

void DataInputDialog::on_lnPriceKWh9_editingFinished()
{
    dKWhPrice[8] = ui->lnPriceKWh9->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcCostNonPublicElectricity();
    }
}

void DataInputDialog::on_lnPriceKWh10_editingFinished()
{
    dKWhPrice[9] = ui->lnPriceKWh10->text().toDouble();
    if (!bPublicLoadSession)
    {
        calcCostNonPublicElectricity();
    }
}

//---------------------------------------------------------------------------------------
//
//  Default/Max KWh load session changed
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_lnKWhMax_editingFinished()
{
    dDefaultKWh = ui->lnKWhMax->text().toDouble();
    calcNonPublicLoadPerSession(0);
    showNonPublicLoadSession();
    calcCostNonPublicElectricity();

}

//---------------------------------------------------------------------------------------
//
//  Loads total amount loaded and the start time set at that moment to ensure that also
//  the default time is loaded in case this is the correct time.
//
//---------------------------------------------------------------------------------------
void DataInputDialog::on_lnTotalKWh_editingFinished()
{
    getStartTime();
    dTotalKWh = ui->lnTotalKWh->text().toDouble();
    //-----------------------------------------------------------------------------------
    //
    //  Load the defaults for a non-public load session
    //
    //-----------------------------------------------------------------------------------
    if (!bPublicLoadSession)
    {
        calcNonPublicLoadPerSession(0);
        showNonPublicLoadSession();
        calcCostNonPublicElectricity();
    }

    //-----------------------------------------------------------------------------------
    //
    //  Load the defaults for a public load session
    //
    //-----------------------------------------------------------------------------------
    else
    {

    }
}

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
        bFirstLoadPeriodChanged = true;
        getStartTime();
        calcNonPublicLoadPerSession(0);
        showNonPublicLoadSession();
        calcCostNonPublicElectricity();

    }
}

//---------------------------------------------------------------------------------------
//
//  Other methods
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  Calculate non-pulbic electricity load session cost and show it in dialog
//
//---------------------------------------------------------------------------------------
void DataInputDialog::calcCostNonPublicElectricity()
{
    dAmount = 0.0;
    for (int iCnt1 = 0; iCnt1 < iMaxNbElectricityPeriods; iCnt1++)
    {
        dAmount = dAmount + (dKWhPeriod[iCnt1] * dKWhPrice[iCnt1]);
    }
    ui->lnAmount->setText(QString::number(dAmount,'f', 2));

}

//---------------------------------------------------------------------------------------
//
//  (Re)colculate non-public electricity load session load per period
//
//  Input:
//      - iColNbChanged: number of the period that is changed, next periods will
//        be recalculated
//
//---------------------------------------------------------------------------------------
void DataInputDialog::calcNonPublicLoadPerSession(int iColNbChanged)
{
    //-----------------------------------------------------------------------------------
    //
    //  local variables
    //
    //-----------------------------------------------------------------------------------
    double dSubTotalKWh = 0.0,
        dRestKWh = 0.0;

    int iCnt1 = 0;

    //-----------------------------------------------------------------------------------
    //
    //  (Re)calc amount from start untill and including period that is changed
    //
    //-----------------------------------------------------------------------------------
    iCnt1 = 0;
    while (iCnt1 <= iColNbChanged)
    {
        dSubTotalKWh += dKWhPeriod[iCnt1];
        iCnt1++;
    }

    //-----------------------------------------------------------------------------------
    //
    //  Calc the amount of the first period
    //  If the first period is set manually then no action
    //
    //-----------------------------------------------------------------------------------
    if (iColNbChanged == 0)
    {
        if ((bFirstLoadPeriodChanged)||(bStartLoadTimeChanged))
        {
            dKWhPeriod[0] = dDefaultKWh * (static_cast<double>(60 - iStartMinute)/60);
            dKWhPeriod[0] = std::round(dKWhPeriod[0] * 1000) / 1000;
            bFirstLoadPeriodChanged = false;
            bStartLoadTimeChanged = false;
        }
        dSubTotalKWh = dKWhPeriod[0];
        iCnt1 = 1;
    }
    dRestKWh = dTotalKWh - dSubTotalKWh;

    //-----------------------------------------------------------------------------------
    //
    //  (Re)calc the remaining periods, overwrite value with default
    //
    //-----------------------------------------------------------------------------------
    while ((dRestKWh >= dDefaultKWh) && (iCnt1 < (iMaxNbElectricityPeriods -1)))
    {
        dKWhPeriod[iCnt1] = dDefaultKWh;
        dRestKWh -= dKWhPeriod[iCnt1];
        iCnt1++;
    }

    //-----------------------------------------------------------------------------------
    //
    //  (Re)calc the last period, and if needed add an extra period
    //
    //-----------------------------------------------------------------------------------
        dKWhPeriod[iCnt1] = dRestKWh;

}

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
    ui->lblKWhTime2->setText("");
    ui->lblKWhTime3->setText("");
    ui->lblKWhTime4->setText("");
    ui->lblKWhTime5->setText("");
    ui->lblKWhTime6->setText("");
    ui->lblKWhTime7->setText("");
    ui->lblKWhTime8->setText("");
    ui->lblKWhTime9->setText("");
    ui->lblKWhTime10->setText("");
    for (int iCnt1 = 0; iCnt1 < iMaxNbElectricityPeriods; iCnt1++)
    {
        dKWhPeriod[iCnt1] = 0;
        dKWhPrice[iCnt1] = 0;
    }

}

//---------------------------------------------------------------------------------------
//
//  Load start time from the dialog box and set the first hour label
//
//---------------------------------------------------------------------------------------
void DataInputDialog::getStartTime()
{
    tiStartTime = ui->teStartTime->time();
    iStartHour = tiStartTime.hour();
    iStartMinute = tiStartTime.minute();
    strStartTime = tiStartTime.toString("hh:mm");

}

//---------------------------------------------------------------------------------------
//
//  resetDialog
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

//---------------------------------------------------------------------------------------
//
//  setElectricityDefaultNonPublic
//  Set default electricity input in dialog for non-public load session
//
//---------------------------------------------------------------------------------------
void DataInputDialog::setElectricityDefaultNonPublic()
{
    ui->lnDescription->setText("Laden");
    ui->teStartTime->setDisplayFormat(strStartTimeFormat);
    ui->teStartTime->setTime(QTime::fromString("00:00"));
    ui->lnKWhMax->setText(QString::number(dDefaultKWh,'f', 1));
    ui->lnAccuPercentageEnd->setText(QString::number(iAccuEndPercentage));

}

//---------------------------------------------------------------------------------------
//
//  Display loadsession period data of non public load session
//
//---------------------------------------------------------------------------------------
void DataInputDialog::showNonPublicLoadSession()
{
    int iCnt1 = 0;
    QString strHour;
    while ((dKWhPeriod[iCnt1] > 0)&&(iCnt1 < iMaxNbElectricityPeriods))
    {
        switch (iCnt1) {
        case 0:
            ui->lnKWh1->setText(QString::number(dKWhPeriod[iCnt1],'f', 3));
            ui->lnPriceKWh1->setText(QString::number(dKWhPrice[iCnt1], 'f',2));
            break;
        case 1:
            ui->lnKWh2->setText(QString::number(dKWhPeriod[iCnt1],'f', 3));
            ui->lnPriceKWh2->setText(QString::number(dKWhPrice[iCnt1], 'f',2));
            strHour = QTime((iStartHour + iCnt1), 0).toString("hh:mm");
            ui->lblKWhTime2->setText(strHour);
            break;
        case 2:
            ui->lnKWh3->setText(QString::number(dKWhPeriod[iCnt1],'f', 3));
            ui->lnPriceKWh3->setText(QString::number(dKWhPrice[iCnt1], 'f',2));
            strHour = QTime((iStartHour + iCnt1), 0).toString("hh:mm");
            ui->lblKWhTime3->setText(strHour);
            break;
        case 3:
            ui->lnKWh4->setText(QString::number(dKWhPeriod[iCnt1],'f', 3));
            ui->lnPriceKWh4->setText(QString::number(dKWhPrice[iCnt1], 'f',2));
            strHour = QTime((iStartHour + iCnt1), 0).toString("hh:mm");
            ui->lblKWhTime4->setText(strHour);
            break;
        case 4:
            ui->lnKWh5->setText(QString::number(dKWhPeriod[iCnt1],'f', 3));
            ui->lnPriceKWh5->setText(QString::number(dKWhPrice[iCnt1], 'f',2));
            strHour = QTime((iStartHour + iCnt1), 0).toString("hh:mm");
            ui->lblKWhTime5->setText(strHour);
            break;
        case 5:
            ui->lnKWh6->setText(QString::number(dKWhPeriod[iCnt1],'f', 3));
            ui->lnPriceKWh6->setText(QString::number(dKWhPrice[iCnt1], 'f',2));
            strHour = QTime((iStartHour + iCnt1), 0).toString("hh:mm");
            ui->lblKWhTime6->setText(strHour);
            break;
        case 6:
            ui->lnKWh7->setText(QString::number(dKWhPeriod[iCnt1],'f', 3));
            ui->lnPriceKWh7->setText(QString::number(dKWhPrice[iCnt1], 'f',2));
            strHour = QTime((iStartHour + iCnt1), 0).toString("hh:mm");
            ui->lblKWhTime7->setText(strHour);
            break;
        case 7:
            ui->lnKWh8->setText(QString::number(dKWhPeriod[iCnt1],'f', 3));
            ui->lnPriceKWh8->setText(QString::number(dKWhPrice[iCnt1], 'f',2));
            strHour = QTime((iStartHour + iCnt1), 0).toString("hh:mm");
            ui->lblKWhTime8->setText(strHour);
            break;
        case 8:
            ui->lnKWh9->setText(QString::number(dKWhPeriod[iCnt1],'f', 3));
            ui->lnPriceKWh9->setText(QString::number(dKWhPrice[iCnt1], 'f',2));
            strHour = QTime((iStartHour + iCnt1), 0).toString("hh:mm");
            ui->lblKWhTime9->setText(strHour);
            break;
        case 9:
            ui->lnKWh10->setText(QString::number(dKWhPeriod[iCnt1],'f', 3));
            ui->lnPriceKWh10->setText(QString::number(dKWhPrice[iCnt1], 'f',2));
            strHour = QTime((iStartHour + iCnt1), 0).toString("hh:mm");
            ui->lblKWhTime10->setText(strHour);
            break;
        default:
            break;
        }
        iCnt1++;
    }
}





