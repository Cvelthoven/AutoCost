//---------------------------------------------------------------------------------------
//
//  Module: autocostdetailsmodel.cpp
//
//  This is the class that does the data retrieval and handling of the auto cost details
//  The result is a table filled with the auto cost details per column. All calculations
//  and positioning will be done in this table. Based on the SQL query to retrieve all
//  autocost details.
//
//  std::wstring sqlQuery = L"SELECT * FROM public.\"acAutoCost\" ORDER BY \"Date\" ASC;";
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "autocostdetailsmodel.h"
#include "postgresqldb.h"

#include <QSqlTableModel>
#include <QString>

#include <QDebug>

//---------------------------------------------------------------------------------------
//
//  AppSettings default constructor
//
//---------------------------------------------------------------------------------------
AutoCostDetailsModel::AutoCostDetailsModel(QObject *parent)
{
    AutoCostData = new PostGreSQLDB(this);

    //-----------------------------------------------------------------------------------
    //
    //  Create a QSqlTableModel
    //
    //-----------------------------------------------------------------------------------
    tmDetailCostRecords = new QSqlTableModel;
    tmDetailCostRecords->setTable("acAutoCost");
    tmDetailCostRecords->setSort(3, Qt::AscendingOrder);
    tmDetailCostRecords->select();
    int iNbRows = tmDetailCostRecords->rowCount();
    if (iNbRows >= 0)
    {
        qDebug() << "number of records found: " << iNbRows;
    }
    else
    {
        qDebug() << "error reading table";
    }
}
