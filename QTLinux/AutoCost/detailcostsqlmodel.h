//---------------------------------------------------------------------------------------
//
//  This class will be removed replacement is the setup with detaildatacost(model/view)
//
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

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include <QObject>
#include <QSqlRelationalTableModel>
#include <QString>

//---------------------------------------------------------------------------------------
//
//  Class DetailCostSqlModel definitions
//
//---------------------------------------------------------------------------------------
class DetailCostSqlModel
  : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    DetailCostSqlModel(QObject *parent = nullptr);

    ~DetailCostSqlModel();


    //-----------------------------------------------------------------------------------
    //
    //  Public class variables
    //
    //-----------------------------------------------------------------------------------

private:
    //-----------------------------------------------------------------------------------
    //
    //  Private class methods
    //
    //-----------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------
    //
    //  Private class variables
    //
    //-----------------------------------------------------------------------------------
    bool
        bAppDataOpen = false;
};

//------------------------------------------------
// Old code
//-------------------------------------------------
// class DetailCostSqlModel
//     : public QSqlRelationalTableModel
// {
//     Q_OBJECT
// public:
//     DetailCostSqlModel(QObject *parent = nullptr);

//     ~DetailCostSqlModel();

//     int LoadDetailCostData();

//     // void GetRecordData(const int iRecordNb,
//     //                   int* iRecID,
//     //                   int* iRecordType,
//     //                   QString* strDate,
//     //                   QString* strDescription,
//     //                   double* dTotalCost,
//     //                   int* iFrequency);

//     //-----------------------------------------------------------------------------------
//     //
//     //  Public class variables
//     //
//     //-----------------------------------------------------------------------------------
//     QSqlQuery quDetailCostOverview;

//     //    QSqlTableModel *tmSqlDetailCostRecords;

//     bool bAppDataOpen = false;

//     int
//         iNbRows = 0;

// private:
//     //-----------------------------------------------------------------------------------
//     //
//     //  Private class methods
//     //
//     //-----------------------------------------------------------------------------------

//     //-----------------------------------------------------------------------------------
//     //
//     //  Private class variables
//     //
//     //-----------------------------------------------------------------------------------
//     PostGreSQLDB* acAutoCostTblData;

//     bool bEncrypted = false;

//     enum acAutoCostFields
//     {
//         RecordID = 0,
//         RecordType,
//         Date,
//         Description,
//         Amount,
//         Frequency
//     };

// };

#endif // DETAILCOSTSQLMODEL_H
