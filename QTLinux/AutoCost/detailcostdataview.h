//---------------------------------------------------------------------------------------
//
//  Module: detailcostdataview.cpp
//
//  This class manages the presentation of the detailed cost data
//  The class DetailCostDataModel manages the detail cost data
//
//---------------------------------------------------------------------------------------
#ifndef DETAILCOSTDATAVIEW_H
#define DETAILCOSTDATAVIEW_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "detailcostdatamodel.h"
#include <QObject>
#include <QWidget>

//---------------------------------------------------------------------------------------
//
//  Class DetailCostDataView definitions
//
//---------------------------------------------------------------------------------------
class DetailCostDataView
{
public:
    DetailCostDataView();

private:
    DetailCostDataModel* DetailCostData;

    int iDetailCostRecordNb = -1;
};

#endif // DETAILCOSTDATAVIEW_H
