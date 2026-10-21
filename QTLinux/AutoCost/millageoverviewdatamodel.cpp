//---------------------------------------------------------------------------------------
//
//  Module: millageoverviewdatamodel.cpp
//
//  Class MillageOverviewDataModel manages the millage overview
//  The default QT class QTableView handles the presentation
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "AutoCost.h"
#include "millageoverviewdatamodel.h"
#include "tabledatamodel.h"

#include <QAbstractTableModel>
#include <QObject>

//---------------------------------------------------------------------------------------
//
//  Class MillageOverview constructors and destructors
//
//---------------------------------------------------------------------------------------
//
//  Default constructor and destructor
//
//---------------------------------------------------------------------------------------
MillageOverviewDataModel::MillageOverviewDataModel(QObject *parent)
    : TableDataModel(parent)
{
    //-----------------------------------------------------------------------------------
    //
    //  Set column headers
    //
    strHeaders = {
        "Year",
        "Start",
        "End/Last",
        "Limit",
        "Used",
        "Rest"
    };

}

//---------------------------------------------------------------------------------------
//
//  MillageOverview class methods
//
//---------------------------------------------------------------------------------------
//
//  columnAlignment
//
//---------------------------------------------------------------------------------------
Qt::Alignment MillageOverviewDataModel::columnAlignment(int c) const
{
    return c == MillageOverviewYear ? Qt::AlignHCenter : Qt::AlignRight;
}

//---------------------------------------------------------------------------------------
//
//  loadMillageData
//
//---------------------------------------------------------------------------------------
bool MillageOverviewDataModel::loadMillageData(const DetailCostDataModel &detailModel)
{
    int iCnt1;

    //-----------------------------------------------------------------------------------
    //
    //  Retrieve data from the detail cost data
    //
    dMillageYearStart = detailModel.getDMillageYearStart();
    dMillageCurrent = detailModel.getMillageCurrent();
    dMillageYearEnd = detailModel.getDMillageYearEnd();
    years = detailModel.getYears();

    //-----------------------------------------------------------------------------------
    //
    //  Calculate year used and remaining millage
    //
    dMillageYearRemaining.append(0);
    for (iCnt1 = 0; iCnt1 < dMillageYearStart.size(); iCnt1++)
    {

        if ((iCnt1 < dMillageYearEnd.size()) && (iCnt1 != 0))
        {
            dMillageYearUsed.append(dMillageYearEnd.at(iCnt1) - dMillageYearStart.at(iCnt1));
            dMillageYearRemaining.append(iMaxMillageYear - dMillageYearEnd.at(iCnt1));
        }
        else
        {
            dMillageYearUsed.append(dMillageCurrent - dMillageYearStart.at(iCnt1));
            if (iCnt1 != 0)
            {
                dMillageYearRemaining.append(iMaxMillageYear - dMillageCurrent);
            }
        }
    }

    //-----------------------------------------------------------------------------------
    //
    //  Build data for tabledatamodel
    //
    auto millage = [](const QVector<double> &v, int iRowNb) { return QString::number(v.at(iRowNb), 'f', 0); };
    rebuild(years.size(), [&](int iRowNb, int iColNb) -> QVariant {
        switch (iColNb)
        {
            case MillageOverviewYear:
                return iRowNb == 0 ? QString("Total") : QString::number(years.at(iRowNb));
            case MillageOverviewStart:
                return iRowNb == 0 ? QString::number(0) : millage(dMillageYearStart, iRowNb);
            case MillageOverviewCurrent:
                //-----------------------------------------------------------------------
                //
                //  Overall millage
                //
                if (iRowNb == 0)
                {
                    return QString::number(dMillageYearStart.at(0), 'f', 0);
                }
                //-----------------------------------------------------------------------
                //
                //  Millage previous years
                //
                else if (iRowNb < dMillageYearEnd.size())
                {
                    return millage(dMillageYearEnd, iRowNb);
                }
                //-----------------------------------------------------------------------
                //
                //  Current year
                //
                else
                {
                    return QString::number(dMillageCurrent, 'f', 0);
                }
            case MillageOverviewLimit:
                return iRowNb == 0 ? QString(" ") : QString::number(iMaxMillageYear);
            case MillageOverviewUsed:
                return millage(dMillageYearUsed, iRowNb);
            case MillageOverviewRemaining:
                return iRowNb == 0 ? QString(" ") : millage(dMillageYearRemaining, iRowNb);
            default:
                return QVariant();
        }
    });

    return true;
}
