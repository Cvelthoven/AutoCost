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

#include <QSqlDatabase>

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

}
