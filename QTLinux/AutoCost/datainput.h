//---------------------------------------------------------------------------------------
//
//  Module: datainput.h
//
//---------------------------------------------------------------------------------------
#ifndef DATAINPUT_H
#define DATAINPUT_H
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "postgresqldb.h"

#include <QDate>
#include <QString>
#include <QTime>

//---------------------------------------------------------------------------------------
//
//  Class DataInput definitions
//
//---------------------------------------------------------------------------------------
class DataInput
{
public:
    //-----------------------------------------------------------------------------------
    //
    //  Default constructor
    //
    //-----------------------------------------------------------------------------------
    DataInput();

    //-----------------------------------------------------------------------------------
    //
    //  Getters and setters
    //
    //-----------------------------------------------------------------------------------
    int getIRecordType() const;
    void setIRecordType(int newIRecordType);

    QDate getDaDate() const;
    void setDaDate(const QDate &newDaDate);

    QString getStrDescription() const;
    void setStrDescription(const QString &newStrDescription);

    double getDTotalCost() const;
    void setDTotalCost(double newDTotalCost);

    int getIKmTotal() const;
    void setIKmTotal(int newIKmTotal);

    int getICapBatteryStart() const;
    void setICapBatteryStart(int newICapBatteryStart);

    int getICapBatteryEnd() const;
    void setICapBatteryEnd(int newICapBatteryEnd);

    double getDKWhLoaded() const;
    void setDKWhLoaded(double newDKWhLoaded);

    QTime getTiStartTime() const;
    void setTiStartTime(const QTime &newTiStartTime);

    bool getBPublicLoadSession() const;
    void setBPublicLoadSession(bool newBPublicLoadSession);

    //-----------------------------------------------------------------------------------
    //
    //  Other public methods
    //
    //-----------------------------------------------------------------------------------
    int addAcAutoCostRecord();
    int addAcElectricityRecord();

private:

    //-----------------------------------------------------------------------------------
    //
    //  Variables for content of a acAutoCost record
    //
    //-----------------------------------------------------------------------------------
    int
        iAutoCostRecID = -1,
        iRecordType = -1;

    QDate
        daDate;

    QString
        strDescription = "";

    double
        dTotalCost = 0.0;

    //-----------------------------------------------------------------------------------
    //
    //  Variables for content of a acElectricity record
    //
    //-----------------------------------------------------------------------------------
    int
        iElecRecId = -1,
        iKmTotal = -1,
        iCapBatteryStart = -1,
        iCapBatteryEnd = -1,
        iAcAutoCostRecID = -1;

    double
        dKWhLoaded = -1;

    QTime
        tiStartTime;

    bool
        bPublicLoadSession = false;
};

#endif // DATAINPUT_H
