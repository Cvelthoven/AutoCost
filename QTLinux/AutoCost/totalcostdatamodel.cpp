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
#include "AutoCost.h"
#include "tabledatamodel.h"
#include "totalcostdatamodel.h"

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
    : TableDataModel(parent)
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
        "Accessories"
    };

}

//---------------------------------------------------------------------------------------
//
//  TotalCostDataModel class methods
//
//---------------------------------------------------------------------------------------
//
//  columnCount
//
//---------------------------------------------------------------------------------------
Qt::Alignment TotalCostDataModel::columnAlignment(int c) const
{
    return c == TotalCostViewYear ? Qt::AlignHCenter : Qt::AlignRight;
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
    MillageYearStart = detailModel.getDMillageYearStart();

    //-----------------------------------------------------------------------------------
    //
    //  Build the data for the tabledatamodel
    //
    //  Define the layout for the money data values
    auto money = [](const QVector<double> &v, int r) { return QString::number(v.at(r), 'f', 2); };

    rebuild(years.size(), [&](int r, int c) -> QVariant
    {
        switch (c)
        {
            case TotalCostViewYear:
                return r == 0 ? QString("Total") : QString::number(years.at(r));
            case TotalCostViewTotal:
                return money(totalCost, r);
            case TotalCostViewPeriodic:
                return money(periodic, r);
            case TotalCostViewElectricity:
                return money(electricity, r);
            case TotalCostViewOther:
                return money(other, r);
            case TotalCostViewAccessory:
                return money(accessory, r);
            default:
                return QVariant();
        }
    });
}