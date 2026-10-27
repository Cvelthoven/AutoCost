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
bool AverageCostDataModel::loadCostData(const DetailCostDataModel &detailModel)
{
    return true;
}



