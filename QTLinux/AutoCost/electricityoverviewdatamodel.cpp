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
    return true;
}