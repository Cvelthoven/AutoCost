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
#include "detailcostdatamodel.h"
#include "tabledatamodel.h"
//#include <QAbstractTableModel>
#include <QObject>
//#include <QString>
#include <QVector>

class MillageOverviewDataModel : public TableDataModel
{
    Q_OBJECT
public:
    MillageOverviewDataModel(QObject *parent = nullptr);

    //-----------------------------------------------------------------------------------
    //
    //  Public methods
    //
    bool loadMillageData(const DetailCostDataModel &detailModel);

    //-----------------------------------------------------------------------------------
    //
    //  Default QAbstractTableModel overrides
    //
    // int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    // QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    // QVariant headerData(int section, Qt::Orientation orientation,
    //                     int role = Qt::DisplayRole) const override;

protected:
    //-----------------------------------------------------------------------------------
    //
    //  Subclasses override to customise alignment (default: right aligned)
    //
    virtual Qt::Alignment columnAlignment(int column) const;

    //-----------------------------------------------------------------------------------
    //
    //  Resets the model and fills m_rows with cell(row, col) for every row/column
    //
    //  This method needs to be in the header fill due to CellFn
    //
    template <typename CellFn>
    void rebuild(int rows, CellFn cell)
    {
        beginResetModel();
        m_rows.clear();
        m_rows.reserve(rows);
        for (int r = 0; r < rows; ++r) {
            QVector<QVariant> row;
            row.reserve(strHeaders.size());
            for (int c = 0; c < strHeaders.size(); ++c)
                row.append(cell(r, c));
            m_rows.append(row);
        }
        endResetModel();
    }

private:
    double dMillageCurrent = -1;

    QVector<double>
        dMillageYearEnd,
        dMillageYearRemaining,
        dMillageYearStart,
        dMillageYearUsed;

    QVector<int> years;

    // QVector<QString> strHeaders;

    // QVector<QVector<QVariant>> m_rows;

};

#endif // MILLAGEOVERVIEWDATAMODEL_H
