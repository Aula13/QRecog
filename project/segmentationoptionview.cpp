#include "segmentationoptionview.h"
#include "ui_segmentationoptionview.h"

SegmentationOptionView::SegmentationOptionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SegmentationOptionView)
{
    ui->setupUi(this);
}

SegmentationOptionView::~SegmentationOptionView()
{
    delete ui;
}
