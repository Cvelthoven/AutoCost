//---------------------------------------------------------------------------------------
//
//  Module: electricityoverviewdatamodel.cpp
//
//  Class ElectricityOverviewDataModel manages the electricity overview
//  The default QT class QTableView handles the presentation
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "AutoCost.h"
#include "electricityoverviewdatamodel.h"
#include "tabledatamodel.h"
#include <QObject>

//---------------------------------------------------------------------------------------
//
//  Class ElectricityOverviewDataModel constructors and destructors
//
//---------------------------------------------------------------------------------------
//
//  Default constructor and destructor
//
//---------------------------------------------------------------------------------------
ElectricityOverviewDataModel::ElectricityOverviewDataModel(QObject *parent)
    : TableDataModel(parent)
{
    //-----------------------------------------------------------------------------------
    //
    //  Set column headers
    //
    strHeaders = {
        "Year",
        "KWh",
        "KWh/km",
        "km/KWh",
        "Euro/KWh"
    };

}

//---------------------------------------------------------------------------------------
//
//  ElectricityOverviewDataModel class methods
//
//---------------------------------------------------------------------------------------
//
//  columnAlignment
//
//---------------------------------------------------------------------------------------
Qt::Alignment ElectricityOverviewDataModel::columnAlignment(int c) const
{
    return c == ElectrictyOverviewYear ? Qt::AlignHCenter : Qt::AlignRight;
}

//---------------------------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------------------------
bool ElectricityOverviewDataModel::loadElectricityData(const DetailCostDataModel &detailModel)
{
    //-----------------------------------------------------------------------------------
    //
    //  Load data from detail cost overview
    //
    years = detailModel.getYears();
    dTotalKWh = detailModel.getDKWhLoaded();

    //-----------------------------------------------------------------------------------
    //
    //  Build data for tabledatamodel
    //
    auto KWh = [](const QVector<double> &v, int iRowNb) { return QString::number(v.at(iRowNb), 'f', 0); };
    rebuild(years.size(), [&](int iRowNb, int iColNb) -> QVariant {
        switch (iColNb)
        {
        case ElectrictyOverviewYear:
            return iRowNb == 0 ? QString("Total") : QString::number(years.at(iRowNb));
        case ElectrictyOverviewKWh:
            if (iRowNb == 0)
            {
                return QString::number(dTotalKWh.at(0), 'f', 2);
            }
            else
            {
                return QString::number(dTotalKWh.at(iRowNb), 'f', 2);
            }
        case ElectrictyOverviewKWhKm:
            //-----------------------------------------------------------------------
            //
            //  Overall millage
        //     //
        //     if (iRowNb == 0)
        //     {
        //         return QString::number(dMillageYearStart.at(0), 'f', 0);
        //     }
        //     //-----------------------------------------------------------------------
        //     //
        //     //  Millage previous years
        //     //
        //     else if (iRowNb < dMillageYearEnd.size())
        //     {
        //         return millage(dMillageYearEnd, iRowNb);
        //     }
        //     //-----------------------------------------------------------------------
        //     //
        //     //  Current year
        //     //
        //     else
        //     {
        //         return QString::number(dMillageCurrent, 'f', 0);
        //     }
        // case ElectrictyOverviewKmKWh:
        //     return iRowNb == 0 ? QString(" ") : QString::number(iMaxMillageYear);
        // case ElectrictyOverviewEuroKWh:
        //     return millage(dMillageYearUsed, iRowNb);
         default:
            return QVariant();
        }
    });

    return true;
}