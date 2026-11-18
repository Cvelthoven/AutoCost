//---------------------------------------------------------------------------------------
//
//  Module: readcsvelectricityfile.h
//
//  Class ReadCsvElectricityFile read the electricity csv file and breaks the lines
//  into the field values.
//  It doesn't store the data to the database only provides data
//
//---------------------------------------------------------------------------------------
#ifndef READCSVELECTRICITYFILE_H
#define READCSVELECTRICITYFILE_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include <QDateTime>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QVector>

//---------------------------------------------------------------------------------------
//
//  Structure of the electricity data record
//
struct ElectricityData
{
    QDate qdRecordDate;
    QTime qtRecordTime;
    double
        dUsedKWh,
        dReturnKWh,
        dMarketPrice,
        dDeliveryCost,
        dEnergyTax,
        dTotalVariableCost,// No needed to store
        dReductionEngeryTax,
        dFixedDeliveryCost,
        dNetworkCost,
        dTotalFixedCost,// not needed to store
        dTotalCost;// not needed to store
};

//---------------------------------------------------------------------------------------
//
//  Class ReadCsvElectricityFile definitions
//
//---------------------------------------------------------------------------------------
class ReadCsvElectricityFile
{
public:
    ReadCsvElectricityFile();

    //-----------------------------------------------------------------------------------
    //
    //  Public methods
    //
    int getILineTotal() const;
    int ReadFile(QString *strFileName);

private:
    //-----------------------------------------------------------------------------------
    //
    //  Private methods
    //
    void ConvertLineToRecord(QString strInputLine);

    //-----------------------------------------------------------------------------------
    //
    //  Private variables
    //
    int
        iLineTotal = 0;

    QFile ElectricityDataFile;

    QTextStream ElectricityDataStream;

    QVector<ElectricityData> vedElectricityRecords;

    // QVector<QString>
    //     vsRecord;
};

#endif // READCSVELECTRICITYFILE_H