//---------------------------------------------------------------------------------------
//
//  Module: DetailCostSqlModel.cpp
//
//  This class retrieves the autocost records in a table format which is input for the
//  DetailCostTableModel class.
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "detailcostsqlmodel.h"
#include "postgresqldb.h"

#include <QSqlRecord>
#include <QSqlTableModel>
#include <QString>

#include <QDebug>

//---------------------------------------------------------------------------------------
//
//  DetailCostSqlModel default constructor
//
//---------------------------------------------------------------------------------------
DetailCostSqlModel::DetailCostSqlModel(QObject *parent)
{
    qDebug() << "DetailCostSqlModel constructor called";
    qDebug() << "db connection for autocost opened in DetailCostSqlModel constructor";
    AutoCostData = new PostGreSQLDB(this);

    //-----------------------------------------------------------------------------------
    //
    //  Create a QSqlTableModel
    //
    //-----------------------------------------------------------------------------------
    qDebug() << "QSqlTableModel constructor called from DetailCostSqlModel constructor";
    tmSqlDetailCostRecords = new QSqlTableModel;
    tmSqlDetailCostRecords->setTable("acAutoCost");
    tmSqlDetailCostRecords->setSort(Date, Qt::AscendingOrder);
    tmSqlDetailCostRecords->select();
    iNbRows = tmSqlDetailCostRecords->rowCount();

}

//---------------------------------------------------------------------------------------
//
//  DetailCostSqlModel destructor
//
//---------------------------------------------------------------------------------------
DetailCostSqlModel::~DetailCostSqlModel()
{
    qDebug() << "DetailCostSqlModel destructor called";
    //-----------------------------------------------------------------------------------
    //
    //  Close autocost db connection
    //
    //-----------------------------------------------------------------------------------
    if (AutoCostData != nullptr)
    {
        qDebug() << "db connection for autocost closed in DetailCostSqlModel destructor";
        delete AutoCostData;
    }

    //-----------------------------------------------------------------------------------
    //
    //  Clean up
    //
    //-----------------------------------------------------------------------------------
    qDebug() << "Destructor of QSqlTableModel called in DetailCostSqlModel destructor";
    delete tmSqlDetailCostRecords;

}

//---------------------------------------------------------------------------------------
//
//  Class methodes
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  GetRecordData
//
//  Input:
//      - iRecordNb: position of the record in sorted table (not RecID)
//  Output:
//      - iRecID: recordID
//      - iRecordType: record type
//      - strDate: content date field
//      - strDescription: content description field
//      - dTotalCost: content totalcost field
//      - iFrequency: content frequency field
//
//---------------------------------------------------------------------------------------
void DetailCostSqlModel::GetRecordData(const int iRecordNb,
                                      int* iRecID,
                                      int* iRecordType,
                                      QString* strDate,
                                      QString* strDescription,
                                      double* dTotalCost,
                                      int* iFrequency)
{
    bool bOk;
    double dTemp;
    int iTemp;
    QSqlRecord tmSqlDetailCostRecord = tmSqlDetailCostRecords->record(iRecordNb);
    iTemp = tmSqlDetailCostRecord.value("AutoCostRecID").toInt(&bOk);
    if (bOk)
    {
        *iRecID = iTemp;
    }
    else
    {
        *iRecID = -1;
    }
    iTemp = tmSqlDetailCostRecord.value("RecordType").toInt(&bOk);
    if (bOk)
    {
        *iRecordType = iTemp;
    }
    else
    {
        *iRecordType = -1;
    }
    *strDate = tmSqlDetailCostRecord.value("Date").toString();
    *strDescription = tmSqlDetailCostRecord.value("Description").toString();
    dTemp = tmSqlDetailCostRecord.value("TotalCost").toDouble(&bOk);
    if (bOk)
    {
        *dTotalCost = dTemp;
    }
    else
    {
        *dTotalCost = -9999999;
    }
    iTemp = tmSqlDetailCostRecord.value("Frequency").toInt(&bOk);
    if (bOk)
    {
        *iFrequency = iTemp;
    }
    else
    {
        *iFrequency = -1;
    }

}

