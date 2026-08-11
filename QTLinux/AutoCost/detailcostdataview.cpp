//---------------------------------------------------------------------------------------
//
//  Module: detailcostdataview.cpp
//
//  This class manages the presentation of the detailed cost data
//  The class DetailCostDataModel manages the detail cost data
//
//---------------------------------------------------------------------------------------
//
//  Header files
//
//---------------------------------------------------------------------------------------
#include "detailcostdataview.h"

#include <QVBoxLayout>
#include <QWidget>

#include <QDebug>

//---------------------------------------------------------------------------------------
//
//  Class DetailCostDataView constructors and destructors
//
//---------------------------------------------------------------------------------------
//
//  constructor and destructor
//
//---------------------------------------------------------------------------------------
DetailCostDataView::DetailCostDataView(QWidget *parent)
    : QWidget(parent), tableView(nullptr), refreshButton(nullptr), dataModel(nullptr)
{
    qDebug() << "Constructor DetailCostDataView called";
    setupUI();
}

DetailCostDataView::~DetailCostDataView()
{
}

//---------------------------------------------------------------------------------------
//
//  DetailCostDataView class methods
//
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//  setupUI
//
//---------------------------------------------------------------------------------------
void DetailCostDataView::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Create table view
    tableView = new QTableView(this);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setAlternatingRowColors(true);
    layout->addWidget(tableView);

    // Create refresh button
    refreshButton = new QPushButton("Refresh Data", this);
    connect(refreshButton, &QPushButton::clicked, this, &DetailCostDataView::onRefreshClicked);
    layout->addWidget(refreshButton);

    setLayout(layout);
}

//---------------------------------------------------------------------------------------
//
//  setModel
//
//---------------------------------------------------------------------------------------
void DetailCostDataView::setModel(DetailCostDataModel *model)
{
    dataModel = model;
    tableView->setModel(dataModel);

    // Set column widths
    tableView->resizeColumnsToContents();
//    tableView->horizontalHeader()->setStretchLastSection(true);
}

//---------------------------------------------------------------------------------------
//
//  loadData
//
//---------------------------------------------------------------------------------------
bool DetailCostDataView::loadData()
{
    if (!dataModel) {
        qWarning() << "No model set for view";
        return false;
    }

    return dataModel->loadDetailCostData();
}

//---------------------------------------------------------------------------------------
//
//  onRefreshClicked
//
//---------------------------------------------------------------------------------------
void DetailCostDataView::onRefreshClicked()
{
    if (!loadData()) {
        qWarning() << "Error refreshing data";
    }
}