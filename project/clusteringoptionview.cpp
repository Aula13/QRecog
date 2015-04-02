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

bool ClusteringOptionView::showUsedKeypoints()
{
    return ui->chkShowUsedKeypoints->isChecked();
}

float ClusteringOptionView::getModelSample()
{
    return ui->spnModelSample->value();
}

float ClusteringOptionView::getDescriptorRadius()
{
    return ui->spnDescriptorRadius->value();
}

ClusteringOptionView::~ClusteringOptionView()
{
    delete ui;
}

void ClusteringOptionView::on_chkShowUsedKeypoints_toggled(bool checked)
{
    if(checked) {
        ui->spnModelSample->setEnabled(true);
        ui->spnDescriptorRadius->setEnabled(true);
    } else {
        ui->spnModelSample->setEnabled(false);
        ui->spnDescriptorRadius->setEnabled(false);
    }
}
