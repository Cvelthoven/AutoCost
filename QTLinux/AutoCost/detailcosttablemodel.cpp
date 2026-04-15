//---------------------------------------------------------------------------------------
//
//  Module: DetailCostTableModel.cpp
//
//  This class prepares the data from detailcostsqlmodel to be displayed.
//  All reformating and filling the calculated columns are part of this class
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "AutoCost.h"
#include "detailcosttablemodel.h"

#include <QAbstractTableModel>
#include <QDate>
#include <QTableView>
#include <QString>

#include <QDebug>
//---------------------------------------------------------------------------------------
//
//  DetailCostTableModel default constructor
//
//---------------------------------------------------------------------------------------
DetailCostTableModel::DetailCostTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    DetailedCostSqlTable = new DetailCostSqlModel();

    //-----------------------------------------------------------------------------------
    //
    //  Fill tblDetailCostValues with the values out of the database and the calculated
    //  values
    //
    //-----------------------------------------------------------------------------------
    for (int iCnt1 = 0; iCnt1 < DetailedCostSqlTable->iNbRows; iCnt1++)
    {
        ConvertSqlrecordToTableViewRow(iCnt1);
    }
}

//---------------------------------------------------------------------------------------
//
//  DetailCostTableModel destructor
//
//  Clean up first
//
//---------------------------------------------------------------------------------------
DetailCostTableModel::~DetailCostTableModel()
{
    delete DetailedCostSqlTable;
}

//---------------------------------------------------------------------------------------
//
//  Class methodes
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  ConvertSqlrecordToTableViewRow
//
//  Input:
//  - iRowNumber
//
//  Fill the tblDetailCostValues to display the default values
//
//---------------------------------------------------------------------------------------
void DetailCostTableModel::ConvertSqlrecordToTableViewRow(int iRowNumber)
{
    //-----------------------------------------------------------------------------------
    //
    //  Local variables
    //
    //-----------------------------------------------------------------------------------
    double
        dTotalCost;
    int
        iRecId = -1,
        iRecordType = -1,
        iFrequency = -1;

    QString
        strDate = "",
        strDescription = "";

    //-----------------------------------------------------------------------------------
    //
    //  Retrieve and convert record to detailtableview layout
    //
    //-----------------------------------------------------------------------------------
    DetailedCostSqlTable->GetRecordData(iRowNumber,
                                        &iRecId,
                                        &iRecordType,
                                        &strDate,
                                        &strDescription,
                                        &dTotalCost,
                                        &iFrequency);
    tblDetailCostValues[iRowNumber][CostOverViewRecID] = QString::number(iRecId);
    tblDetailCostValues[iRowNumber][CostOverViewRecType] = QString::number(iRecordType);

    QDate dtTemp = QDate::fromString(strDate, "yyyy-MM-dd");
    if (dtTemp.isValid())
    {
        tblDetailCostValues[iRowNumber][CostOverViewDate] = dtTemp.toString("dd-MMM-yyyy");
    }
    tblDetailCostValues[iRowNumber][CostOverViewDescription] = strDescription;

    switch (iRecordType) {
    case 1:
        tblDetailCostValues[iRowNumber][CostOverViewPeriodic] = QString::number(dTotalCost, 'f', 2);
        break;
    case 2:
        tblDetailCostValues[iRowNumber][CostOverViewElectricity] = QString::number(dTotalCost, 'f', 2);
        break;
    case 3:
        tblDetailCostValues[iRowNumber][CostOverViewOther] = QString::number(dTotalCost, 'f', 2);
        break;
    case 4:
        tblDetailCostValues[iRowNumber][CostOverViewAccessory] = QString::number(dTotalCost, 'f', 2);
        break;
    default:
        break;
    }

    tblDetailCostValues[iRowNumber][CostOverViewPeriod] = QString::number(iFrequency);

}


//---------------------------------------------------------------------------------------
//
//  rowCount
//
//  Set the number of rows in the overview
//  Required methods for QAbstractTableModel
//
//---------------------------------------------------------------------------------------
int DetailCostTableModel::rowCount(const QModelIndex & /*parent*/) const
{
    int iNBRows = DetailedCostSqlTable->iNbRows;
    return iNBRows;
}

//---------------------------------------------------------------------------------------
//
//  columnCount
//
//  Set the number of columns in overview
//  Required methods for QAbstractTableModel
//
//---------------------------------------------------------------------------------------
int DetailCostTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return CostOverViewPeriod + 1;
}

//---------------------------------------------------------------------------------------
//
//  data
//
//  Displays the data in tblDetailCostValues
//
//---------------------------------------------------------------------------------------
QVariant DetailCostTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole && checkIndex(index))
        return tblDetailCostValues[index.row()][index.column()];

    //-----------------------------------------------------------------------------------
    //
    //  Set the column and row alignment
    //
    //-----------------------------------------------------------------------------------
    if (role == Qt::TextAlignmentRole)
    {
        switch (index.column()) {
        case CostOverViewRecID:
        case CostOverViewRecType:
        case CostOverViewDate:
            return int(Qt::AlignHCenter | Qt::AlignVCenter);
            break;
        case CostOverViewPeriodic:
        case CostOverViewElectricity:
        case CostOverViewOther:
        case CostOverViewAccessory:
            return int(Qt::AlignRight | Qt::AlignVCenter);
        default:
            return int(Qt::AlignLeft | Qt::AlignVCenter);
            break;
        }
    }

    return QVariant();
}

//---------------------------------------------------------------------------------------
//
//  setData
//
//  Fills tblDetailCostValues with the converted values from the sqlquery
//
//  Now reacts to update in window
//
//---------------------------------------------------------------------------------------
bool DetailCostTableModel::setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)
{
    if (role == Qt::EditRole) {
        if (!checkIndex(index))
            return false;
        //save value from editor to member m_gridData
        tblDetailCostValues[index.row()][index.column()] = value.toString();
        //for presentation purposes only: build and emit a joined string
        QString result;
        for (int row = 0; row < 109; row++) {
            for (int col= 0; col < CostOverViewPeriod; col++)
                result += tblDetailCostValues[row][col] + ' ';
        }
        emit editCompleted(result);
        return true;
    }
    return false;}



//---------------------------------------------------------------------------------------
//
//  headerData
//
//  Set the headers of the columns
//
//---------------------------------------------------------------------------------------
QVariant DetailCostTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case CostOverViewRecID:
            return QString("RecID");
        case CostOverViewRecType:
            return QString("Type");
        case CostOverViewDate:
            return QString("Date");
        case CostOverViewDescription:
            return QString("Description");
        case CostOverViewPeriodic:
            return QString("Periodic");
        case CostOverViewElectricity:
            return QString("Electricity");
        case CostOverViewOther:
            return QString("Other");
        case CostOverViewAccessory:
            return QString("Accessory");
        case CostOverViewMillage:
            return QString("Millage");
        case CostOverViewMillageTrip:
            return QString("Km Trip");
        case CostOverViewKWhTrip:
            return QString("kWh Trip");
        case CostOverViewKWhLoaded:
            return QString("kWh Loaded");
        case CostOverViewCostKWhperKM:
            return QString("Cost kWh/km");
        case CostOverViewAvgEuroPerKWh:
            return QString("Avg Euro/kWh");
        case CostOverViewKWhPerPercentage:
            return QString("kWh/%");
        case CostOverViewKMPerPercentage:
            return QString("km/%");
        case CostOverViewAccuStartPercentage:
            return QString("Accu Start");
        case CostOverViewAccuEndPercentage:
            return QString("Accu End");
        case CostOverViewAccuUsagePercentage:
            return QString("Accu Usage");
        case CostOverViewAccuLoadDeltaPercentage:
            return QString("Load Delta");
        case CostOverViewPeriod:
            return QString("Period");

        }
    }
    return QVariant();
}

Qt::ItemFlags DetailCostTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}