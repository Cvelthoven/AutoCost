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

//---------------------------------------------------------------------------------------
//
//  AppSettings default constructor
//
//---------------------------------------------------------------------------------------
AutoCostDetailsModel::AutoCostDetailsModel(QObject *parent, PostGreSQLDB *AppDatabase)
{

}
