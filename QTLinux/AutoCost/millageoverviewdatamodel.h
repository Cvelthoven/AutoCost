//---------------------------------------------------------------------------------------
//
//  Module: millageoverviewdatamodel.h
//
//  Class MillageOverviewDataModel manages the millage overview
//  The default QT class QTableView handles the presentation
//
//---------------------------------------------------------------------------------------
#ifndef MILLAGEOVERVIEWDATAMODEL_H
#define MILLAGEOVERVIEWDATAMODEL_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "appsettingdatamodel.h"
#include "detailcostdatamodel.h"
#include "tabledatamodel.h"
#include <QObject>
#include <QVector>

//---------------------------------------------------------------------------------------
//
//  Class MillageOverviewDataModel definitions
//
//---------------------------------------------------------------------------------------
class MillageOverviewDataModel : public TableDataModel,
                                 public AppSettingDataModel
{
    Q_OBJECT
public:
    MillageOverviewDataModel(QObject *parent = nullptr,
                      AppSettingDataModel *AppConfig = nullptr);

    //-----------------------------------------------------------------------------------
    //
    //  Public methods
    //
    void loadMillageData(const DetailCostDataModel &detailModel);

protected:
    //-----------------------------------------------------------------------------------
    //
    //  Subclasses override to customise alignment (default: right aligned)
    //
    virtual Qt::Alignment columnAlignment(int column) const;

private:
    AppSettingDataModel* ApplicationConfiguration = nullptr;

    double dMillageCurrent = -1;

    int
        iMaxMillageYear = -1;

    QVector<double>
        dMillageYearEnd,
        dMillageYearRemaining,
        dMillageYearStart,
        dMillageYearUsed;

    QVector<int> years;

};

//-----------------------------------------------------------------------------------
//
//  Descriptive names for the Millage overview
//
enum MillageOverviewColumn
{
    MillageOverviewYear = 0,
    MillageOverviewStart,
    MillageOverviewCurrent,
    MillageOverviewLimit,
    MillageOverviewUsed,
    MillageOverviewRemaining
};

#endif // MILLAGEOVERVIEWDATAMODEL_H
