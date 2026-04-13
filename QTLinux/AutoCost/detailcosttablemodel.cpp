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

    double
        dTotalCost;
    int
        iRecId = -1,
        iRecordType = -1,
        iFrequency = -1;

    QString
        strDate = "",
        strDescription = "";

    DetailedCostSqlTable = new DetailCostSqlModel();
    int iNBRows = DetailedCostSqlTable->iNbRows;
    qDebug() << "number of records found: " << iNBRows;

    // for (int iCnt1 = 0; iCnt1 < iNBRows; iCnt1++)
    // {
    //     DetailedCostSqlTable->GetRecordData(iCnt1, &iRecId, &iRecordType, &strDate, &strDescription, &dTotalCost, &iFrequency);
    //     qDebug() << iRecId;
    // }
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
//  Required methods for QAbstractTableModel
//
//---------------------------------------------------------------------------------------
QVariant DetailCostTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
        return QString("Row%1, Column%2")
            .arg(index.row() + 1)
            .arg(index.column() +1);

    return QVariant();
}