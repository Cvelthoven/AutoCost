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
    if (!index.isValid())
    {
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
        case TotalCostViewYear:
            return Qt::AlignCenter;
            break;
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
    int iRowNb =0,
        iColNb = 0,
        iTotalRows = 0,
        iTotalCol = 0;


    //-----------------------------------------------------------------------------------
    //
    //  Retrieve the total values from the detailModel
    //
    years = detailModel.getYears();
    totalCost = detailModel.getTotalCost();
    periodic = detailModel.getTotalPeriodic();
    electricity = detailModel.getTotalElectricity();
    other = detailModel.getTotalOtherCost();
    accessory = detailModel.getTotalAccessory();

    //-----------------------------------------------------------------------------------
    //
    //  Reset table view datamodel
    //
    iTotalRows = years.size();
    iTotalCol = strHeaders.size();

    beginResetModel();
    m_rows.clear();

    //-----------------------------------------------------------------------------------
    //
    //  Build table view datamodel
    //
    for (iRowNb = 0; iRowNb < iTotalRows; iRowNb++)
    {
        QVector<QVariant> totalrow;
        totalrow.reserve(iTotalCol);
        for (iColNb = 0; iColNb < iTotalCol; iColNb++)
        {
            switch (iColNb) {
            case TotalCostViewYear:
                if (iRowNb == 0)
                {
                    totalrow.append("Total");
                }
                else
                {
                    totalrow.append(QString::number(years.at(iRowNb)));
                }
                break;
            case TotalCostViewTotal:
                totalrow.append(QString::number(totalCost.at(iRowNb), 'f', 2));
                break;
            case TotalCostViewPeriodic:
                totalrow.append(QString::number(periodic.at(iRowNb), 'f', 2));
                break;
            case TotalCostViewElectricity:
                totalrow.append(QString::number(electricity.at(iRowNb), 'f', 2));
                break;
            case TotalCostViewOther:
                totalrow.append(QString::number(other.at(iRowNb), 'f', 2));
                break;
            case TotalCostViewAccessory:
                totalrow.append(QString::number(accessory.at(iRowNb), 'f', 2));
                break;
            case TotalCostViewMillage:
                totalrow.append("Mil");
                break;
            default:
                totalrow.append("Test");
                break;
            }
        }
        m_rows.append(totalrow);
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
