//---------------------------------------------------------------------------------------
//
//  Module: electricityoverviewdatamodel.h
//
//  Class ElectricityOverviewDataModel manages the millage overview
//  The default QT class QTableView handles the presentation
//
//---------------------------------------------------------------------------------------
#ifndef ELECTRICITYOVERVIEWDATAMODEL_H
#define ELECTRICITYOVERVIEWDATAMODEL_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "tabledatamodel.h"
#include <QObject>
#include <QString>
#include <QVector>

class ElectricityOverviewDataModel : public TableDataModel
{
    Q_OBJECT
public:
    ElectricityOverviewDataModel(QObject *parent = nullptr);

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


};

#endif // ELECTRICITYOVERVIEWDATAMODEL_H
