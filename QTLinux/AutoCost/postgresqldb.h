//---------------------------------------------------------------------------------------
//
//  Module: postgresqldb.h
//
//  This class manages an instance of a connection to a PostGreSql database
//
//---------------------------------------------------------------------------------------
#ifndef POSTGRESQLDB_H
#define POSTGRESQLDB_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
//#include "appsettings.h"
#include "appconfiguration.h"

#include <QSqlDatabase>
#include <QtSql>
#include <QSqlQueryModel>
#include <QString>
//#include <QStringList>

//---------------------------------------------------------------------------------------
//
//  Class PostGreSQLDB definitions
//
//---------------------------------------------------------------------------------------
class PostGreSQLDB : public QSqlQueryModel
{
    Q_OBJECT
public:
//    PostGreSQLDB(QObject *parent = nullptr);
//    explicit PostGreSQLDB(AppSettings *Application);// needs to be removed
    explicit PostGreSQLDB(AppConfiguration *appSettings);
    ~PostGreSQLDB();



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
    //    int ExecQuery(QString *strQuery);
    //    int SelectQuery(QString *strQuery);
    void close();

    //-----------------------------------------------------------------------------------
    //
    //  Public variables
    //
    //-----------------------------------------------------------------------------------
    QSqlDatabase dbAppDatabase;

    //    QStringList stlRecordContent;

private:
    //-----------------------------------------------------------------------------------
    //
    //  Private variables
    //
    //-----------------------------------------------------------------------------------
//    int LoadDatabaseSettings();

    AppConfiguration *ApplicationConfig = nullptr;
//    AppSettings *Application = nullptr;

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
