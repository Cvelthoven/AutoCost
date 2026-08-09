//---------------------------------------------------------------------------------------
//
//  This class will be removed replacement is the setup with detaildatacost(model/view)
//
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
#include "AutoCost.h"
#include "detailcostsqlmodel.h"

#include <QMessageBox>
#include <QSqlDatabase>
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
    //-----------------------------------------------------------------------------------
    //
    //  Reuse open Application datbase connection
    //
    QSqlDatabase acAutoCostTblData = QSqlDatabase::database(strApplicationDatabaseConnectionName, false);
    if ((acAutoCostTblData.isValid())&&(acAutoCostTblData.isOpen()))
    {
        bAppDataOpen = true;
    }
    else
    {
        bAppDataOpen = false;
    }
}

//---------------------------------------------------------------------------------------
//
//  DetailCostSqlModel destructor
//
//---------------------------------------------------------------------------------------
DetailCostSqlModel::~DetailCostSqlModel()
{
    //-----------------------------------------------------------------------------------
    //
    //  Clean up
    //
    //-----------------------------------------------------------------------------------
    qDebug() << "Destructor of QSqlTableModel called in DetailCostSqlModel destructor";
//    delete tmSqlDetailCostRecords;

}

//---------------------------------------------------------------------------------------
//
//  Class methodes
//
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//
//  Old code that could be reused or deleted
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
//  The following LEFT JOIN can be used to retrieve all field of both
//  acAutoCost and acElectricity into 1 table (tested with pgAdmin)
// SELECT
//     ac."AutoCostRecID",
//     ac."RecordType",
//     ac."Date",
//     ac."Description",
//     ac."TotalCost",
//     ac."Frequency",
//     el."ElecRecId",
//     el."KmTotal",
//     el."KWhLoaded",
//     el."CapBatteryStart",
//     el."CapBatteryEnd",
//     el."StartTime",
//     el."AutoCostRecId"
//     FROM public."acAutoCost" ac
//     LEFT JOIN public."acElectricity" el
//         ON el."AutoCostRecId" = ac."AutoCostRecID"
//         ORDER BY ac."Date" ASC;,
//         el."KmTotal" ASC NULLS LAST;
//---------------------------------------------------------------------------------------
//}

