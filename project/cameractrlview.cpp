#include "cameractrlview.h"
#include "ui_cameractrlview.h"

CameraCtrlView::CameraCtrlView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraCtrlView)
{
    ui->setupUi(this);

    Logger::logInfo("CameraCtrlView initialized");
}

CameraCtrlView::~CameraCtrlView()
{
    delete ui;
    Logger::logInfo("CameraCtrlView deleted");
}

void CameraCtrlView::on_btnStartCamera_clicked()
{
    Models::pcs->run();
    Logger::logInfo("CameraCtrlView btnStartCamera pressed");
}

void CameraCtrlView::on_btnStopCamera_clicked()
{
    Models::pcs->stop();
    Logger::logInfo("CameraCtrlView btnStopCamera pressed");
}
