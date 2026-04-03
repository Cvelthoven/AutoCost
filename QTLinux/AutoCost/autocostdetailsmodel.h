//---------------------------------------------------------------------------------------
//
//  Module: autocostdetailsmodel.h
//
//  This class retrieves the autocost records in a table format which is input for the
//  autodetailcostmodel class.
//
//---------------------------------------------------------------------------------------
#ifndef AUTOCOSTDETAILSMODEL_H
#define AUTOCOSTDETAILSMODEL_H

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
//  Class AutoCostDetailsModel definitions
//
//---------------------------------------------------------------------------------------
class AutoCostDetailsModel : public QSqlTableModel
{
    Q_OBJECT
public:
    AutoCostDetailsModel(QObject *parent = nullptr);

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

#endif // AUTOCOSTDETAILSMODEL_H
