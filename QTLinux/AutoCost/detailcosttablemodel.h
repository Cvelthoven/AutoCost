//---------------------------------------------------------------------------------------
//
//  Module: DetailCostTableModel.h
//
//  This class prepares the data from detailcostsqlmodel to be displayed.
//  All reformating and filling the calculated columns are part of this class
//
//---------------------------------------------------------------------------------------
#ifndef DETAILCOSTTABLEMODEL_H
#define DETAILCOSTTABLEMODEL_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "detailcostsqlmodel.h"
#include <QObject>

//---------------------------------------------------------------------------------------
//
//  Class DetailCostTableModel definitions
//
//---------------------------------------------------------------------------------------
class DetailCostTableModel
{
public:
    DetailCostTableModel();

private:
    DetailCostSqlModel *DetailedCostSqlTable;
};

#endif // DETAILCOSTTABLEMODEL_H
