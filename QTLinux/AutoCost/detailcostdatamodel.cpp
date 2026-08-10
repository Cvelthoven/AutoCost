//---------------------------------------------------------------------------------------
//
//  Module: detailcostdatamodel.cpp
//
//  This class manages the detail cost data
//  The class DetailCostDataView manages the presentation of the detailed cost data
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "AutoCost.h"
#include "detailcostdatamodel.h"

#include <QSqlDatabase>
#include <QAbstractTableModel>

#include <QDebug>

//---------------------------------------------------------------------------------------
//
//  Class DetailCostDataModel constructors and destructors
//
//---------------------------------------------------------------------------------------
//
//  Default constructor
//
//---------------------------------------------------------------------------------------
DetailCostDataModel::DetailCostDataModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    qDebug() << "Constructor DetailCostDataModel called";

    //-----------------------------------------------------------------------------------
    //
    //  Reuse open Application database connection
    //
    dbAutoCost = QSqlDatabase::database(strApplicationDatabaseConnectionName, false);
    if ((dbAutoCost.isValid()) && (dbAutoCost.isOpen()))
    {
        bAppDataOpen = true;
    }
    else
    {
        bAppDataOpen = false;
    }

}

//---------------------------------------------------------------------------------------
//
//  DetailCostDataModel class methods
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  getBAppDataOpen
//
//---------------------------------------------------------------------------------------
bool DetailCostDataModel::getBAppDataOpen() const
{
    return bAppDataOpen;
}

//---------------------------------------------------------------------------------------
//
//  RetrieveDetailCostData
//
//  Output:
//      RetrieveDetailCostData: number of records in dataset
//
//---------------------------------------------------------------------------------------
int DetailCostDataModel::RetrieveDetailCostData()
{
    return 0;
}

//---------------------------------------------------------------------------------------
//
//  Default methods required by QAbstractTableModel
//
//---------------------------------------------------------------------------------------
int DetailCostDataModel::rowCount(const QModelIndex & /*parent*/) const
{
    return 2;
}

int DetailCostDataModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;
}

QVariant DetailCostDataModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
        return QString("Row%1, Column%2")
            .arg(index.row() + 1)
            .arg(index.column() +1);

    return QVariant();
}
