//---------------------------------------------------------------------------------------
//
//  Module: totalcostdatamodel.cpp
//
//  This class manages the total cost data
//  The default QT class QTableView handles the presentation
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "totalcostdatamodel.h"

#include <QAbstractTableModel>
#include <QObject>

//---------------------------------------------------------------------------------------
//
//  Class TotalCostDataModel constructors and destructors
//
//---------------------------------------------------------------------------------------
//
//  Default constructor and destructor
//
//---------------------------------------------------------------------------------------
TotalCostDataModel::TotalCostDataModel(QObject *parent)
    : QAbstractTableModel(parent)
{

    //-----------------------------------------------------------------------------------
    //
    //  Set column headers
    //
    strHeaders = {
        "Year",
        "Total",
        "Periodic",
        "Electricity",
        "Other",
        "Accessories",
        "Millage"
    };

}

//---------------------------------------------------------------------------------------
//
//  TotalCostDataModel class methods
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  columnCount
//
//---------------------------------------------------------------------------------------
int TotalCostDataModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return strHeaders.size();
}

//---------------------------------------------------------------------------------------
//
//  data
//
//---------------------------------------------------------------------------------------
QVariant TotalCostDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    //-----------------------------------------------------------------------------------
    //
    //  Set the field alignment of the columns
    //
    //-----------------------------------------------------------------------------------
    if (role == Qt::TextAlignmentRole)
    {
        switch (index.column())
        {
         default:
            return Qt::AlignRight;
        }
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    const int row = index.row();
    const int col = index.column();

    if (row < 0 || row >= m_rows.size()) {
        return QVariant();
    }

    if (col < 0 || col >= strHeaders.size()) {
        return QVariant();
    }

    return m_rows.at(row).at(col);
}

//---------------------------------------------------------------------------------------
//
//  headerData
//
//---------------------------------------------------------------------------------------
QVariant TotalCostDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < strHeaders.size()) {
            return strHeaders.at(section);
        }
        return QVariant();
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

//---------------------------------------------------------------------------------------
//
//  loadTotals
//
//  Load the total values from the detailcostdata model
//
//---------------------------------------------------------------------------------------
void TotalCostDataModel::loadTotals(const DetailCostDataModel &detailModel)
{
    beginResetModel();
    m_rows.clear();

    QVector<int> years = detailModel.getYears();
    QVector<double> totalCost = detailModel.getTotalCost();
    QVector<double> periodic = detailModel.getTotalPeriodic();
    QVector<double> electricity = detailModel.getTotalElectricity();
    QVector<double> other = detailModel.getTotalOtherCost();
    QVector<double> accessory = detailModel.getTotalAccessory();

    for (int i = 0; i < years.size(); ++i) {
        QVector<QVariant> row;
        row << (i == 0 ? "Total" : QString::number(years.at(i)))
            << QString::number(totalCost.value(i), 'f', 2)
            << QString::number(periodic.value(i), 'f', 2)
            << QString::number(electricity.value(i), 'f', 2)
            << QString::number(other.value(i), 'f', 2)
            << QString::number(accessory.value(i), 'f', 2);
        m_rows.append(row);
    }

    endResetModel();
}

//---------------------------------------------------------------------------------------
//
//  rowCount
//
//---------------------------------------------------------------------------------------
int TotalCostDataModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return m_rows.size();
}
