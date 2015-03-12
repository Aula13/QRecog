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

void CameraCtrlView::on_btnStartCamera_clicked()
{
    CameraModel::getInstance()->run();
    Logger::logInfo("CameraCtrlView btnStartCamera pressed");
}

void CameraCtrlView::on_btnStopCamera_clicked()
{
    CameraModel::getInstance()->stop();
    Logger::logInfo("CameraCtrlView btnStopCamera pressed");
}
