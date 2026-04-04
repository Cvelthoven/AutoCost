//---------------------------------------------------------------------------------------
//
//  Module: DetailCostTableModel.cpp
//
//  This class prepares the data from detailcostsqlmodel to be displayed.
//  All reformating and filling the calculated columns are part of this class
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "detailcosttablemodel.h"

#include <QString>

#include <QDebug>
//---------------------------------------------------------------------------------------
//
//  DetailCostTableModel default constructor
//
//---------------------------------------------------------------------------------------
DetailCostTableModel::DetailCostTableModel()
{

    double
        dTotalCost;
    int
        iRecId = -1,
        iRecordType = -1,
        iFrequency = -1;

    QString
        strDate = "",
        strDescription = "";

    DetailedCostSqlTable = new DetailCostSqlModel();
    int iNBRows = DetailedCostSqlTable->iNbRows;
    qDebug() << "number of records found: " << iNBRows;

    for (int iCnt1 = 0; iCnt1 < iNBRows; iCnt1++)
    {
        DetailedCostSqlTable->GetRecordData(iCnt1, &iRecId, &iRecordType, &strDate, &strDescription, &dTotalCost, &iFrequency);
        qDebug() << iRecId;
    }
}
