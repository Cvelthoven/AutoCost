//---------------------------------------------------------------------------------------
//
//  Module: postgresqldb.h
//
//---------------------------------------------------------------------------------------
#ifndef POSTGRESQLDB_H
#define POSTGRESQLDB_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "appsettings.h"
#include "AutoCost.h"

//#include <QObject>
#include <QSqlDatabase>
#include <QString>

//---------------------------------------------------------------------------------------
//
//  Clsass AppSettings definitions
//
//---------------------------------------------------------------------------------------
class PostGreSQLDB
{
//    Q_OBJECT
public:
    PostGreSQLDB();

private:
    bool bEncrypted = false;
    QString
        strSectionName = strSectionNameAppDB,
        strKeyName = "",
        strDBServerIP = "",
        strDBServerPort = "",
        strDBName = "",
        strDBUserID = "",
        strDBPassword = "";

    AppSettings *ApplicationConfig;

    QSqlDatabase dbAppDatabase;

};

#endif // POSTGRESQLDB_H
