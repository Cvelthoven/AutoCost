//---------------------------------------------------------------------------------------
//
//  This class will be removed replacement is the setup with detaildatacost(model/view)
//
//---------------------------------------------------------------------------------------
//
//  Module: DetailCostSqlModel.h
//
//  This class retrieves the autocost records in a table format which is input for the
//  DetailCostTableModel class.
//
//---------------------------------------------------------------------------------------
#ifndef DETAILCOSTSQLMODEL_H
#define DETAILCOSTSQLMODEL_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include <QObject>
#include <QSqlRelationalTableModel>

//---------------------------------------------------------------------------------------
//
//  Class DetailCostSqlModel definitions
//
//---------------------------------------------------------------------------------------
class DetailCostSqlModel
  : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    DetailCostSqlModel(QObject *parent = nullptr);

    ~DetailCostSqlModel();

private:
    bool
        bAppDataOpen = false;
};

#endif // DETAILCOSTSQLMODEL_H
