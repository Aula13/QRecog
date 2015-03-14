#include "clusteringoptionview.h"
#include "ui_clusteringoptionview.h"

ClusteringOptionView::ClusteringOptionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClusteringOptionView)
{
    ui->setupUi(this);
}

bool ClusteringOptionView::isClusteringEnabled()
{
    return ui->chkEnableClustering->isChecked();
}

float ClusteringOptionView::getClusterTolerance()
{
    return ui->spnClusterTolerance->value();
}

int ClusteringOptionView::getMinClusterSize()
{
    return ui->spnMinClusterSize->value();
}

int ClusteringOptionView::getMaxClusterSize()
{
    return ui->spnMaxClusterSize->value();
}

ClusteringOptionView::~ClusteringOptionView()
{
    delete ui;
}
