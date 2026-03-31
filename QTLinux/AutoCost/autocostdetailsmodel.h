//---------------------------------------------------------------------------------------
//
//  Module: autocostdetailsmodel.h
//
//  This is the class that does the data retrieval and handling of the auto cost details
//  The result is a table filled with the auto cost details per column. All calculations
//  and positioning will be done in this table. Based on the SQL query to retrieve all
//  autocost details.
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
    AutoCostDetailsModel(QObject *parent);

    QSqlTableModel *tmDetailCostRecords;
    PostGreSQLDB *AutoCostData;
};

#endif // AUTOCOSTDETAILSMODEL_H
