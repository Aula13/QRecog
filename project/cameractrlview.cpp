#include "cameractrlview.h"
#include "ui_cameractrlview.h"

CameraCtrlView::CameraCtrlView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraCtrlView)
{
    ui->setupUi(this);
}

CameraCtrlView::~CameraCtrlView()
{
    delete ui;
}
