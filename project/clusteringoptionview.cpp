#include "clusteringoptionview.h"
#include "ui_clusteringoptionview.h"

ClusteringOptionView::ClusteringOptionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClusteringOptionView)
{
    ui->setupUi(this);
}

ClusteringOptionView::~ClusteringOptionView()
{
    delete ui;
}
