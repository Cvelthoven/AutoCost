//---------------------------------------------------------------------------------------
//
//  Module: TableDataModel.h
//
//  Class TableDataModel manages the building of the different tables in the main Gui
//  Prevents duplicate code in the following classes:
//  -
//  The default QT class QTableView handles the presentation
//
//---------------------------------------------------------------------------------------
#ifndef TABLEDATAMODEL_H
#define TABLEDATAMODEL_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include <QAbstractTableModel>
#include <QString>
#include <QVariant>
#include <QVector>

class TableDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TableDataModel(QObject *parent = nullptr);

    //-----------------------------------------------------------------------------------
    //
    //  Public methods
    //
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

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

    QVector<QString> strHeaders;
    QVector<QVector<QVariant>> m_rows;

};

#endif // TABLEDATAMODEL_H
