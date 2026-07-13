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

//---------------------------------------------------------------------------------------
//
//  DataInput default constructor
//
//---------------------------------------------------------------------------------------
DataInput::DataInput()
{

}
