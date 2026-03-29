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
#include <QAbstractTableModel>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QString>

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
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

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
