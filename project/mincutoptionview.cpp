#include "mincutoptionview.h"
#include "ui_mincutoptionview.h"

MinCutOptionView::MinCutOptionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MinCutOptionView)
{
    ui->setupUi(this);
}

MinCutOptionView::~MinCutOptionView()
{
    delete ui;
}

float MinCutOptionView::getx()
{
    return ui->spnxCenterPoint->value();
}

float MinCutOptionView::gety()
{
    return ui->spnyCenterPoint->value();
}

float MinCutOptionView::getz()
{
    return ui->spnzCenterPoint->value();
}

float MinCutOptionView::getSigma()
{
    return ui->spnSigma->value();
}

float MinCutOptionView::getRadius()
{
    return ui->spnRadius->value();
}

int MinCutOptionView::getNrNeighbours()
{
    return ui->spnNrNeighbours->value();
}

float MinCutOptionView::getSourceWeight()
{
    return ui->spnSourceWeight->value();
}

bool MinCutOptionView::isMinCutEnabled()
{
    return ui->chkEnableMinCut->isChecked();
}
