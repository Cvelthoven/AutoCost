//---------------------------------------------------------------------------------------
//
//  Module: autocostdetailsmodel.cpp
//
//  This class retrieves the autocost records in a table format which is input for the
//  autodetailcostmodel class.
//
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
//  AutoCostDetailsModel default constructor
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
