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
#include "detailcosttablemodel.h"

#include <QAbstractTableModel>
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
    strRecID = QString::number(iRecId);
    qDebug() << strRecID;

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
    return CostOverViewPeriod;
}

//---------------------------------------------------------------------------------------
//
//  data
//
//  Fills the fields of the table overview
//
//---------------------------------------------------------------------------------------
QVariant DetailCostTableModel::data(const QModelIndex &index, int role) const
{

    if (role == Qt::DisplayRole)
    {
        if (index.row() == CostOverViewRecID)
        {
            QString strFieldText = strRecID;

        }
        else
        {
        return QString("Row%1, Column%2")
            .arg(index.row() + 1)
            .arg(index.column() +1);
        }
    }
    return QVariant();
}

bool DetailCostTableModel::setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)
{
    return true;
}



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