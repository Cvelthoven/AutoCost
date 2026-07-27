//---------------------------------------------------------------------------------------
//
//  Module: datainput.cpp
//
//---------------------------------------------------------------------------------------
//
//  Postgresql
//  Table layout
//---------------------------------------------------------------------------------------
// CREATE TABLE IF NOT EXISTS public."acAutoCost"
//     (
//         "AutoCostRecID" serial NOT NULL,
//         "RecordType" integer NOT NULL DEFAULT 1,
//         "Date" date NOT NULL,
//         "Description" character varying(256) COLLATE pg_catalog."default" NOT NULL,
//         "TotalCost" real,
//         "Frequency" integer NOT NULL DEFAULT 0,
//         CONSTRAINT "acAutoCost_pkey" PRIMARY KEY ("AutoCostRecID")
//         )
//
//     TABLESPACE pg_default;
//
// ALTER TABLE IF EXISTS public."acAutoCost"
//     OWNER to postgres;
//
// GRANT ALL ON TABLE public."acAutoCost" TO "AutoCostAppUser";
//
// GRANT ALL ON TABLE public."acAutoCost" TO postgres;
// -- Index: acAutoCost_Date_idx
//
//           -- DROP INDEX IF EXISTS public."acAutoCost_Date_idx";
//
// CREATE INDEX IF NOT EXISTS "acAutoCost_Date_idx"
//     ON public."acAutoCost" USING btree
//     ("Date" ASC NULLS LAST)
//     WITH (deduplicate_items=True)
//     TABLESPACE pg_default;
//
//---------------------------------------------------------------------------------------
// CREATE TABLE IF NOT EXISTS public."acElectricity"
//     (
//         "ElecRecId" serial NOT NULL,
//         "KmTotal" integer,
//         "KWhLoaded" real,
//         "CapBatteryStart" integer,
//         "CapBatteryEnd" integer,
//         "StartTime" time without time zone,
//         "PublicLoadSession" boolean,
//         "acAutoCostRecID" integer,
//         CONSTRAINT "acElectricity_pkey" PRIMARY KEY ("ElecRecId")
//         )
//
//     TABLESPACE pg_default;
//
// ALTER TABLE IF EXISTS public."acElectricity"
//     OWNER to postgres;
//
// GRANT ALL ON TABLE public."acElectricity" TO "AutoCostAppUser";
//
// GRANT ALL ON TABLE public."acElectricity" TO postgres;
// -- Index: acElectricity_KmTotal_idx
//
//           -- DROP INDEX IF EXISTS public."acElectricity_KmTotal_idx";
//
// CREATE INDEX IF NOT EXISTS "acElectricity_KmTotal_idx"
//     ON public."acElectricity" USING btree
//     ("KmTotal" ASC NULLS LAST)
//     WITH (deduplicate_items=True)
//     TABLESPACE pg_default;
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "datainput.h"
#include "postgresqldb.h"

#include <QDebug>

//---------------------------------------------------------------------------------------
//
//  DataInput default constructor
//
//---------------------------------------------------------------------------------------
DataInput::DataInput()
{
    qDebug() << "DataInput constructor called";

}

//---------------------------------------------------------------------------------------
//
//  Getters and setters
//
//---------------------------------------------------------------------------------------
bool DataInput::getBPublicLoadSession() const
{
    return bPublicLoadSession;
}

void DataInput::setBPublicLoadSession(bool newBPublicLoadSession)
{
    bPublicLoadSession = newBPublicLoadSession;
}

QTime DataInput::getTiStartTime() const
{
    return tiStartTime;
}

void DataInput::setTiStartTime(const QTime &newTiStartTime)
{
    tiStartTime = newTiStartTime;
}

double DataInput::getDKWhLoaded() const
{
    return dKWhLoaded;
}

void DataInput::setDKWhLoaded(double newDKWhLoaded)
{
    dKWhLoaded = newDKWhLoaded;
}

int DataInput::getICapBatteryEnd() const
{
    return iCapBatteryEnd;
}

void DataInput::setICapBatteryEnd(int newICapBatteryEnd)
{
    iCapBatteryEnd = newICapBatteryEnd;
}

int DataInput::getICapBatteryStart() const
{
    return iCapBatteryStart;
}

void DataInput::setICapBatteryStart(int newICapBatteryStart)
{
    iCapBatteryStart = newICapBatteryStart;
}

int DataInput::getIKmTotal() const
{
    return iKmTotal;
}

void DataInput::setIKmTotal(int newIKmTotal)
{
    iKmTotal = newIKmTotal;
}

double DataInput::getDTotalCost() const
{
    return dTotalCost;
}

void DataInput::setDTotalCost(double newDTotalCost)
{
    dTotalCost = newDTotalCost;
}

QString DataInput::getStrDescription() const
{
    return strDescription;
}

void DataInput::setStrDescription(const QString &newStrDescription)
{
    strDescription = newStrDescription;
}

QDate DataInput::getDaDate() const
{
    return daDate;
}

void DataInput::setDaDate(const QDate &newDaDate)
{
    daDate = newDaDate;
}

int DataInput::getIRecordType() const
{
    return iRecordType;
}

void DataInput::setIRecordType(int newIRecordType)
{
    iRecordType = newIRecordType;
}

//---------------------------------------------------------------------------------------
//
//  addAcAutoCostRecord
//
//---------------------------------------------------------------------------------------
int DataInput::addAcAutoCostRecord()
{

    //-----------------------------------------------------------------------------------
    //
    //  Build query
    //
    //-----------------------------------------------------------------------------------

    return 0;
}

//---------------------------------------------------------------------------------------
//
//  addAcAutoCostRecord
//
//---------------------------------------------------------------------------------------
int DataInput::addAcElectricityRecord()
{
    return 0;
}
