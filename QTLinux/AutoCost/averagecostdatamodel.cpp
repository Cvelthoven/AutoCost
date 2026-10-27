//---------------------------------------------------------------------------------------
//
//  Module: averagecostdatamodel.cpp
//
//  Class AverageCostDataModel manages the average cost overview
//  The default QT class QTableView handles the presentation
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "AutoCost.h"
#include "averagecostdatamodel.h"
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
AverageCostDataModel::AverageCostDataModel(QObject *parent)
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
//  AverageCostDataModel class methods
//
//---------------------------------------------------------------------------------------
//
//  columnAlignment
//
//---------------------------------------------------------------------------------------
Qt::Alignment AverageCostDataModel::columnAlignment(int c) const
{
    return c == ElectrictyOverviewYear ? Qt::AlignHCenter : Qt::AlignRight;
}

//---------------------------------------------------------------------------------------
//
//  loadCostData
//
//---------------------------------------------------------------------------------------
void AverageCostDataModel::loadCostData(const DetailCostDataModel &detailModel)
{
    //-----------------------------------------------------------------------------------
    //
    //  Load data from detail cost overview
    //
    years = detailModel.getYears();
    dCostTotal = detailModel.getTotalCost();
    dCostPeriodic = detailModel.getTotalPeriodic();
    dCostElectricity = detailModel.getTotalElectricity();
    dCostOther = detailModel.getTotalOtherCost();
    dCostAssesory = detailModel.getTotalAccessory();
    dMillageYearStart = detailModel.getDMillageYearStart();
    dMillageYearEnd = detailModel.getDMillageYearEnd();

    //-----------------------------------------------------------------------------------
    //
    //  Build data for tabledatamodel
    //
    rebuild(years.size(), [&](int iRowNb, int iColNb) -> QVariant
    {
        switch (iColNb)
        {
        case ElectrictyOverviewYear:
            return iRowNb == 0 ? QString("Total") : QString::number(years.at(iRowNb));
        case AverageCostOverviewTotal:
            if (iRowNb == 0)
            {
                return QString::number(
                    (dCostTotal.at(iRowNb) / detailModel.getMillageCurrent()), 'f', 4);
            }
            else if (iRowNb == dMillageYearEnd.size())
            {
                return QString::number((dCostTotal.at(iRowNb) /
                    (detailModel.getMillageCurrent() - dMillageYearStart.at(iRowNb))), 'f', 4);
            }
            else
            {
                return QString::number((dCostTotal.at(iRowNb) /
                    (dMillageYearEnd.at(iRowNb) - dMillageYearStart.at(iRowNb))), 'f', 4);
            }
        case AverageCostOverviewPeriodic:
            if (iRowNb == 0)
            {
                return QString::number(
                    (dCostPeriodic.at(iRowNb) / detailModel.getMillageCurrent()), 'f', 4);
            }
            else if (iRowNb == dMillageYearEnd.size())
            {
                return QString::number((dCostPeriodic.at(iRowNb) /
                    (detailModel.getMillageCurrent() - dMillageYearStart.at(iRowNb))), 'f', 4);
            }
            else
            {
                return QString::number((dCostPeriodic.at(iRowNb) /
                    (dMillageYearEnd.at(iRowNb) - dMillageYearStart.at(iRowNb))), 'f', 4);
            }
        case AverageCostOverviewElectricity:
            if (iRowNb == 0)
            {
                return QString::number(
                    (dCostElectricity.at(iRowNb) / detailModel.getMillageCurrent()), 'f', 4);
            }
            else if (iRowNb == dMillageYearEnd.size())
            {
                return QString::number((dCostElectricity.at(iRowNb) /
                    (detailModel.getMillageCurrent() - dMillageYearStart.at(iRowNb))), 'f', 4);
            }
            else
            {
                return QString::number((dCostElectricity.at(iRowNb) /
                    (dMillageYearEnd.at(iRowNb) - dMillageYearStart.at(iRowNb))), 'f', 4);
            }
        case AverageCostOverviewOther:
            if (iRowNb == 0)
            {
                return QString::number(
                    (dCostOther.at(iRowNb) / detailModel.getMillageCurrent()), 'f', 4);
            }
            else if (iRowNb == dMillageYearEnd.size())
            {
                return QString::number((dCostOther.at(iRowNb) /
                    (detailModel.getMillageCurrent() - dMillageYearStart.at(iRowNb))), 'f', 4);
            }
            else
            {
                return QString::number((dCostOther.at(iRowNb) /
                    (dMillageYearEnd.at(iRowNb) - dMillageYearStart.at(iRowNb))), 'f', 4);
            }
        case AverageCostOverviewAccessory:
            if (iRowNb == 0)
            {
                return QString::number(
                    (dCostAssesory.at(iRowNb) / detailModel.getMillageCurrent()), 'f', 4);
            }
            else if (iRowNb == dMillageYearEnd.size())
            {
                return QString::number((dCostAssesory.at(iRowNb) /
                    (detailModel.getMillageCurrent() - dMillageYearStart.at(iRowNb))), 'f', 4);
            }
            else
            {
                return QString::number((dCostAssesory.at(iRowNb) /
                    (dMillageYearEnd.at(iRowNb) - dMillageYearStart.at(iRowNb))), 'f', 4);
            }
        default:
            return QVariant();
        }
    });

}



