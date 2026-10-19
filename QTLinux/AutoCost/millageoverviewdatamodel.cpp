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
    int iCnt1,
        iColNb = 0,
        iRowNb = 0,
        iTotalCol = 0,
        iTotalRows = 0;

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
    auto millage = [](const QVector<double> &v, int r) { return QString::number(v.at(r), 'f', 0); };
    rebuild(years.size(), [&](int r, int c) -> QVariant {
        switch (c)
        {
            case MillageOverviewYear:
                return r == 0 ? QString("Total") : QString::number(years.at(r));
            case MillageOverviewStart:
                return r == 0 ? QString::number(0) : millage(dMillageYearStart, r);
            case MillageOverviewCurrent:
                //-----------------------------------------------------------------------
                //
                //  Overall millage
                //
                if (r == 0)
                {
                    return QString::number(dMillageYearStart.at(iRowNb), 'f', 0);
                }
                //-----------------------------------------------------------------------
                //
                //  Millage previous years
                //
                else if (r < dMillageYearEnd.size())
                {
                    return millage(dMillageYearEnd, r);
                }
                //-----------------------------------------------------------------------
                //
                //  Current year
                //
                else
                {
                    return QString::number(dMillageYearStart.at(iRowNb), 'f', 0);
                }
            case MillageOverviewLimit:
                return r == 0 ? QString(" ") : QString::number(iMaxMillageYear);
            case MillageOverviewUsed:
                return millage(dMillageYearUsed, r);
            case MillageOverviewRemaining:
                return r == 0 ? QString(" ") : millage(dMillageYearRemaining, r);
            default:
                return QVariant();
        }
    });

    return true;
}
