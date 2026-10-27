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
//  loadElectricityData
//
//---------------------------------------------------------------------------------------
bool ElectricityOverviewDataModel::loadElectricityData(const DetailCostDataModel &detailModel)
{
    //-----------------------------------------------------------------------------------
    //
    //  Load data from detail cost overview
    //
    years = detailModel.getYears();
    dTotalElectricity = detailModel.getTotalElectricity();
    dTotalKWh = detailModel.getDKWhLoaded();
    dMillageYearStart = detailModel.getDMillageYearStart();
    dMillageYearEnd = detailModel.getDMillageYearEnd();

    //-----------------------------------------------------------------------------------
    //
    //  Build data for tabledatamodel
    //
    auto KWh = [](const QVector<double> &v, int iRowNb)
        { return QString::number(v.at(iRowNb), 'f', 0); };
    rebuild(years.size(), [&](int iRowNb, int iColNb) -> QVariant {
        switch (iColNb)
        {
        case ElectrictyOverviewYear:
            return iRowNb == 0 ? QString("Total") : QString::number(years.at(iRowNb));

            //---------------------------------------------------------------------------
            //
            //  Total used KWh or per year
            //
        case ElectrictyOverviewKWh:
                 return QString::number(dTotalKWh.at(iRowNb), 'f', 2);

            //---------------------------------------------------------------------------
            //
            //  Average KWh per km
            //
        case ElectrictyOverviewKWhKm:
            if (iRowNb == 0)
            {
                return QString::number((dTotalKWh.at(iRowNb) /
                    detailModel.getMillageCurrent()), 'f', 4);
            }
            else if (iRowNb == dMillageYearEnd.size())
            {
                return QString::number((dTotalKWh.at(iRowNb) /
                    (detailModel.getMillageCurrent() - dMillageYearStart.at(iRowNb))),
                    'f', 4);
            }
            else
            {
                return QString::number((dTotalKWh.at(iRowNb) /
                    dMillageYearEnd.at(iRowNb)), 'f', 4);
            }

            //---------------------------------------------------------------------------
            //
            //  Average km per KWh
            //
        case ElectrictyOverviewKmKWh:
            if (iRowNb == 0)
            {
                return QString::number(detailModel.getMillageCurrent() /
                    (dTotalKWh.at(iRowNb)), 'f', 4);
            }
            else if (iRowNb == dMillageYearEnd.size())
            {
                return QString::number(
                    (detailModel.getMillageCurrent() - dMillageYearStart.at(iRowNb)) /
                    (dTotalKWh.at(iRowNb)), 'f', 4);
            }
            else
            {
                return QString::number((dMillageYearEnd.at(iRowNb)) /
                    (dTotalKWh.at(iRowNb)), 'f', 4);
            }

            //---------------------------------------------------------------------------
            //
            //  Average price per KWh
            //
        case ElectrictyOverviewEuroKWh:
            return QString::number(
                (dTotalElectricity.at(iRowNb) / dTotalKWh.at(iRowNb)), 'f', 4);

        default:
            return QVariant();
        }
    });

    return true;
}