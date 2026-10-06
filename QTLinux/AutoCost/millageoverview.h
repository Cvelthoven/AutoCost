//---------------------------------------------------------------------------------------
//
//  Module: millagemverview.h
//
//  This class manages the millage overview
//  The default QT class QTableView handles the presentation
//
//---------------------------------------------------------------------------------------
#ifndef MILLAGEOVERVIEW_H
#define MILLAGEOVERVIEW_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include <QAbstractTableModel>
#include <QObject>
#include <QString>
#include <QVector>

class MillageOverview : QAbstractTableModel
{
    Q_OBJECT
public:
    MillageOverview(QObject *parent = nullptr);

    // QAbstractTableModel overrides
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    // Override to provide custom headers
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;


private:
    QVector<QString> strHeaders;
    QVector<QVector<QVariant>> m_rows;
};

#endif // MILLAGEOVERVIEW_H
