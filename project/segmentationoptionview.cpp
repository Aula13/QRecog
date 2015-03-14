#include "segmentationoptionview.h"
#include "ui_segmentationoptionview.h"

SegmentationOptionView::SegmentationOptionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SegmentationOptionView)
{
    ui->setupUi(this);

    ui->cmbMethodType->addItem("SAC_RANSAC");
    ui->cmbMethodType->addItem("SAC_LMEDS");
    ui->cmbMethodType->addItem("SAC_MSAC");
    ui->cmbMethodType->addItem("SAC_RRANSAC");
    ui->cmbMethodType->addItem("SAC_RMSAC");
    ui->cmbMethodType->addItem("SAC_MLESAC");
    ui->cmbMethodType->addItem("SAC_PROSAC");

    ui->cmbModelType->addItem("SACMODEL_PLANE");
    ui->cmbModelType->addItem("SACMODEL_LINE");
    ui->cmbModelType->addItem("SACMODEL_CIRCLE2D");
    ui->cmbModelType->addItem("SACMODEL_CIRCLE3D");
    ui->cmbModelType->addItem("SACMODEL_SPHERE");
    ui->cmbModelType->addItem("SACMODEL_CYLINDER");
    ui->cmbModelType->addItem("SACMODEL_CONE");
    ui->cmbModelType->addItem("SACMODEL_TORUS");
    ui->cmbModelType->addItem("SACMODEL_PARALLEL_LINE");
    ui->cmbModelType->addItem("SACMODEL_PERPENDICULAR_PLANE");
    ui->cmbModelType->addItem("SACMODEL_PARALLEL_LINES");
    ui->cmbModelType->addItem("SACMODEL_NORMAL_PLANE");
    ui->cmbModelType->addItem("SACMODEL_NORMAL_SPHERE");
    ui->cmbModelType->addItem("SACMODEL_REGISTRATION");
    ui->cmbModelType->addItem("SACMODEL_REGISTRATION_2D");
    ui->cmbModelType->addItem("SACMODEL_PARALLEL_PLANE");
    ui->cmbModelType->addItem("SACMODEL_NORMAL_PARALLEL_PLANE");
    ui->cmbModelType->addItem("SACMODEL_STICK");
}

bool SegmentationOptionView::getOptimizeCoeff()
{
    return ui->chkOptimazeCoef->isChecked();
}

int SegmentationOptionView::getMethodType()
{
    return ui->cmbMethodType->currentIndex();
}

int SegmentationOptionView::getModelType()
{
    return ui->cmbModelType->currentIndex();
}

int SegmentationOptionView::getMaxIterations()
{
    return ui->spnMaxIterations->value();
}

float SegmentationOptionView::getDistanceThreshold()
{
    return ui->spnDistanceThreshold->value();
}

SegmentationOptionView::~SegmentationOptionView()
{
    delete ui;
}
