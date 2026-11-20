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
#include <QDateTime>
#include <QStringList>
#include <QVector>

// #include <QDebug>

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
//  The inputline consists out of the following elements:
//      Periode
//      Levering (kWh),
//      Teruglevering (kWh),
//      Marktprijskosten (€),
//      Leveringskosten (€),
//      Energiebelasting (€),
//      Totale variable kosten (€),
//      Vermindering Energiebelasting (€),
//      Vaste leveringskosten (€),
//      Netbeheerkosten (€),
//      Totale vaste kosten (€),
//      Totale kosten (€),
//      Geschat
//
//---------------------------------------------------------------------------------------
void ReadCsvElectricityFile::ConvertLineToRecord(QString strInputLine)
{
    //-----------------------------------------------------------------------------------
    //
    //  Local variables
    //
    QDateTime
        dtDateTime;

    QStringList
        stlDataParts;

    ElectricityData
        stRecordData;

    //-----------------------------------------------------------------------------------
    //
    //  Replace ',' with '.' for the conversion to double
    //
    for (int iCnt1 = 0; iCnt1 < strInputLine.length(); iCnt1++)
    {
        if (strInputLine[iCnt1] == ",")
        {
            strInputLine[iCnt1] = '.';
        }
    }

    //-----------------------------------------------------------------------------------
    //
    //  Split input line into data parts
    //
    stlDataParts = strInputLine.split(';');

    //-----------------------------------------------------------------------------------
    //
    //  Convert the strings to electricity record parts
    //
    dtDateTime = QDateTime::fromString(stlDataParts[0], "dd-MM-yyyy HH:mm");
    stRecordData.qdRecordDate = dtDateTime.date();
    stRecordData.qtRecordTime = dtDateTime.time();
    stRecordData.dUsedKWh = stlDataParts[1].toDouble();
    stRecordData.dReturnKWh = stlDataParts[2].toDouble();
    stRecordData.dMarketPrice = stlDataParts[3].toDouble();
    stRecordData.dDeliveryCost = stlDataParts[4].toDouble();
    stRecordData.dEnergyTax = stlDataParts[5].toDouble();
    stRecordData.dTotalVariableCost = stlDataParts[6].toDouble();
    stRecordData.dReductionEngeryTax = stlDataParts[7].toDouble();
    stRecordData.dFixedDeliveryCost = stlDataParts[8].toDouble();
    stRecordData.dNetworkCost = stlDataParts[9].toDouble();
    stRecordData.dTotalFixedCost = stlDataParts[10].toDouble();
    stRecordData.dTotalCost = stlDataParts[11].toDouble();

    vedElectricityRecords.append(stRecordData);
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
//  getQdLastRecordDate
//
//---------------------------------------------------------------------------------------
QDate ReadCsvElectricityFile::getQdLastRecordDate() const
{
    return qdLastRecordDate;
}

//---------------------------------------------------------------------------------------
//
//  getQdFirstRecordDate
//
//---------------------------------------------------------------------------------------
QDate ReadCsvElectricityFile::getQdFirstRecordDate() const
{
    return qdFirstRecordDate;
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
    //  Get date of the first and the last record
    //
    qdFirstRecordDate = vedElectricityRecords[0].qdRecordDate;
    qdLastRecordDate = vedElectricityRecords[iLineTotal - 1].qdRecordDate;

    //-----------------------------------------------------------------------------------
    //
    //  Return success
    //
    return 0;
}