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
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QVector>

//---------------------------------------------------------------------------------------
//
//  Class ReadCsvElectricityFile definitions
//
//---------------------------------------------------------------------------------------
class ReadCsvElectricityFile
{
public:
    ReadCsvElectricityFile();

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

    QVector<QString>
        vsRecord;
};

#endif // READCSVELECTRICITYFILE_H