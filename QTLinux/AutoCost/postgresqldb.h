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
    void close();

    QSqlDatabase dbAppDatabase;

    QStringList stlRecordContent;

    //-----------------------------------------------------------------------------------
    //
    //  Setters
    //
    //-----------------------------------------------------------------------------------
    void setStrConnectionName(const QString &newStrConnectionName);
    void setStrDBServerIP(const QString &newStrDBServerIP);
    void setIDBServerPort(int newIDBServerPort);
    void setStrDBName(const QString &newStrDBName);
    void setStrDBUserID(const QString &newStrDBUserID);
    void setStrDBPassword(const QString &newStrDBPassword);

    //-----------------------------------------------------------------------------------
    //
    //  Other public methods
    //
    //-----------------------------------------------------------------------------------
    int ConnectDatabase();

private:

    int iDBServerPort = 0;

    QString
        strConnectionName = "",
        strDBServerIP = "",
        strDBServerPort = "",
        strDBName = "",
        strDBUserID = "",
        strDBPassword = "";

    QSqlRecord rResult;

};

#endif // POSTGRESQLDB_H
