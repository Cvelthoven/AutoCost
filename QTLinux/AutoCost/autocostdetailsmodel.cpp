//---------------------------------------------------------------------------------------
//
//  Module: autocostdetailsmodel.cpp
//
//  This class retrieves the data and handling of the auto cost details
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

#include <QAbstractTableModel>
#include <QSqlRecord>
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
    tmSqlDetailCostRecords = new QSqlTableModel;
    tmSqlDetailCostRecords->setTable("acAutoCost");
    tmSqlDetailCostRecords->setSort(Date, Qt::AscendingOrder);
    tmSqlDetailCostRecords->select();
    iNbRows = tmSqlDetailCostRecords->rowCount();

     if (iNbRows > 0)
    {
//----------  Begin Test only -----------------------------------------------------------------
//
        qDebug() << "number of records found: " << iNbRows;
        QString fieldRecId = "",
                fieldType = "",
                fieldDate = "",
                fieldDescr = "",
                fieldTotal = "",
                fieldFreq = "";
        for (int iCnt1 = 0; iCnt1 < iNbRows; iCnt1++)
        {
            QSqlRecord tmSqlDetailCostRecord = tmSqlDetailCostRecords->record(iCnt1);
            fieldRecId = tmSqlDetailCostRecord.value("AutoCostRecID").toString();
            fieldType = tmSqlDetailCostRecord.value("RecordType").toString();
            fieldDate = tmSqlDetailCostRecord.value("Date").toString();
            fieldDescr = tmSqlDetailCostRecord.value("Description").toString();
            fieldTotal = tmSqlDetailCostRecord.value("TotalCost").toString();
            fieldFreq = tmSqlDetailCostRecord.value("Frequency").toString();
            qDebug() << "RecID: " <<fieldRecId << "RecordType: "<< fieldType << "Date: " << fieldDate << "Description: " << fieldDescr;

        }
    }
    else if (iNbRows == 0)
    {
        qDebug() << "Query succesfull but no records found";

    }
    else
    {
        qDebug() << "error reading table";
    }
    qDebug() << "Method ended succesfull";

//
//---------------- End Test only --------------------------------------------------------
}
