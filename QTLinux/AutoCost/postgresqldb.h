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
//#include <QAbstractTableModel>
#include <QSqlDatabase>
#include <QtSql>
#include <QSqlQueryModel>
#include <QString>
#include <QStringList>

//---------------------------------------------------------------------------------------
//
//  Class PostGreSQLDB definitions
//
//---------------------------------------------------------------------------------------
class PostGreSQLDB : public QSqlQueryModel
{
    Q_OBJECT
public:
    PostGreSQLDB(QObject *parent = nullptr);
     ~PostGreSQLDB();

    int ExecQuery(QString *strQuery);
    int SelectQuery(QString *strQuery);

    QSqlDatabase dbAppDatabase;

    QStringList stlRecordContent;

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
    QSqlRecord rResult;

};

#endif // POSTGRESQLDB_H
