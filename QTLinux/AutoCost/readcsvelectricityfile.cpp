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

#include <QDebug>

//---------------------------------------------------------------------------------------
//
//  Not already defined in readcsvelectricityfile.h
//

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
int ReadCsvElectricityFile::ReadFile(QString *strFileName)
{
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
    while (!ElectricityDataStream.atEnd())
    {
        QString line = ElectricityDataStream.readLine();
        qDebug() << line;
    }

    //-----------------------------------------------------------------------------------
    //
    //  Return success
    //
    return 0;
}