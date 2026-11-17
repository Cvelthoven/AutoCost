//---------------------------------------------------------------------------------------
//
//  Module: readcsvelectricityfile.cpp
//
//  Class ReadCsvElectricityFile read the electricity csv file and breaks the lines
//  into the field values.
//  It doesn't store the data to the database only provides data
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "readcsvelectricityfile.h"

//---------------------------------------------------------------------------------------
//
//  Not already defined in readcsvelectricityfile.h
//


#include <QDebug>

//---------------------------------------------------------------------------------------
//
//  Class ReadCsvElectricityFile constructors and destructors
//
//---------------------------------------------------------------------------------------
ReadCsvElectricityFile::ReadCsvElectricityFile()
{

}

//---------------------------------------------------------------------------------------
//
//  Class ElectricityCostInputModel methods
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  ConvertLineToRecord
//
//---------------------------------------------------------------------------------------
void ReadCsvElectricityFile::ConvertLineToRecord(QString strInputLine)
{
    qDebug() << strInputLine;
}

//---------------------------------------------------------------------------------------
//
//  getILineTotal
//
//---------------------------------------------------------------------------------------
int ReadCsvElectricityFile::getILineTotal() const
{
    return iLineTotal;
}

//---------------------------------------------------------------------------------------
//
//  ReadFile
//
//---------------------------------------------------------------------------------------
int ReadCsvElectricityFile::ReadFile(QString *strFileName)
{
    QString line = "";

    //-----------------------------------------------------------------------------------
    //
    //  Verify that strFileName is not empty
    //
    if (strFileName->length() == 0)
    {
        return 1;
    }

    //-----------------------------------------------------------------------------------
    //
    //  Open file
    //
    ElectricityDataFile.setFileName(*strFileName);
    if (!ElectricityDataFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return 2;
    }

    //-----------------------------------------------------------------------------------
    //
    //  Read file line by line
    //
    ElectricityDataStream.setDevice(&ElectricityDataFile);
    iLineTotal = 0;

    //-----------------------------------------------------------------------------------
    //
    //  Read headerline and discard it
    //
    if (!ElectricityDataStream.atEnd())
    {
        line = ElectricityDataStream.readLine();

    }
    //-----------------------------------------------------------------------------------
    //
    //  Data file is empty
    //
    else
    {
        return 3;
    }

    //-----------------------------------------------------------------------------------
    //
    //  Process data lines
    //
    while (!ElectricityDataStream.atEnd())
    {
        line = ElectricityDataStream.readLine();
        ConvertLineToRecord(line);
        iLineTotal++;

    }

    //-----------------------------------------------------------------------------------
    //
    //  Return success
    //
    return 0;
}