//---------------------------------------------------------------------------------------
//
//  Module: averagecostdatamodel.h
//
//  Class AverageCostDataModel manages the average cost overview
//  The default QT class QTableView handles the presentation
//
//---------------------------------------------------------------------------------------
#ifndef AVERAGECOSTDATAMODEL_H
#define AVERAGECOSTDATAMODEL_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "detailcostdatamodel.h"
#include "tabledatamodel.h"
#include <QObject>
#include <QString>
#include <QVector>

class AverageCostDataModel : public TableDataModel
{
    Q_OBJECT
public:
    AverageCostDataModel(QObject *parent = nullptr);

    //-----------------------------------------------------------------------------------
    //
    //  Public methods
    //
    bool loadCostData(const DetailCostDataModel &detailModel);

protected:
    //-----------------------------------------------------------------------------------
    //
    //  Subclasses override to customise alignment (default: right aligned)
    //
    virtual Qt::Alignment columnAlignment(int column) const;

private:
    QVector<int>
        years;


};

#endif // AVERAGECOSTDATAMODEL_H
