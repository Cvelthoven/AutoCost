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
    QFile ElectricityDataFile;

    QTextStream ElectricityDataStream;
};

#endif // READCSVELECTRICITYFILE_H