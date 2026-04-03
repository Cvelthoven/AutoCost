//---------------------------------------------------------------------------------------
//
//  Module: DetailCostSqlModel.h
//
//  This class retrieves the autocost records in a table format which is input for the
//  DetailCostTableModel class.
//
//---------------------------------------------------------------------------------------
#ifndef DETAILCOSTSQLMODEL_H
#define DETAILCOSTSQLMODEL_H

#include <QObject>

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "postgresqldb.h"

#include <QObject>
#include <QSqlTableModel>

//---------------------------------------------------------------------------------------
//
//  Class DetailCostSqlModel definitions
//
//---------------------------------------------------------------------------------------
class DetailCostSqlModel
  : public QSqlTableModel
{
    Q_OBJECT
public:
    DetailCostSqlModel(QObject *parent = nullptr);

private:
    QSqlTableModel *tmSqlDetailCostRecords;
    PostGreSQLDB *AutoCostData;

    int
        iNbRows = 0;

    enum acAutoCostFields
    {
        RecordID = 0,
        RecordType,
        Date,
        Description,
        Amount,
        Frequency
    };

};

#endif // DETAILCOSTSQLMODEL_H
