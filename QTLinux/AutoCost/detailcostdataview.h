// Must be removed
//  only needed in case one of the default QT tableview is not sufficient
//---------------------------------------------------------------------------------------
//
//  Module: detailcostdataview.cpp
//
//  This class manages the presentation of the detailed cost data
//  The class DetailCostDataModel manages the detail cost data
//
//---------------------------------------------------------------------------------------
#ifndef DETAILCOSTDATAVIEW_H
#define DETAILCOSTDATAVIEW_H

//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "detailcostdatamodel.h"

#include <QTableView>
#include <QPushButton>
#include <QWidget>

//---------------------------------------------------------------------------------------
//
//  Class DetailCostDataView definitions
//
//---------------------------------------------------------------------------------------
//class DetailCostDataView : public QWidget
class DetailCostDataView : public QTableView
{
    Q_OBJECT
public:
    explicit DetailCostDataView(QWidget *parent = nullptr);
    ~DetailCostDataView();

    // Set the model for the view
    void setModel(DetailCostDataModel *model);

    // Load and display data
    bool loadData();

private slots:
    void onRefreshClicked();

private:
    QTableView *tableView;
    QPushButton *refreshButton;
    DetailCostDataModel *dataModel;

    void setupUI();
};

#endif // DETAILCOSTDATAVIEW_H
