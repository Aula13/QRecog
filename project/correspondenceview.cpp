#include "correspondenceview.h"
#include "ui_correspondenceview.h"

CorrespondenceView::CorrespondenceView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CorrespondenceView)
{
    ui->setupUi(this);

    ui->wgtPCLViewer->setModelReference(Models::pcs);
}

CorrespondenceView::~CorrespondenceView()
{
    delete ui;
}

void CorrespondenceView::on_chkDisableUpdate_stateChanged(int arg1)
{
    if(arg1==0)
        ui->wgtPCLViewer->enableUpdates();
    else
        ui->wgtPCLViewer->disableUpdates();
}
