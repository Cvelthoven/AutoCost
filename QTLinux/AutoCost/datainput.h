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
    DataInput();

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
