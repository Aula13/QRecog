#include "acquisitionview.h"
#include "ui_acquisitionview.h"

AcquisitionView::AcquisitionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AcquisitionView)
{
    ui->setupUi(this);

    ui->wgtPCLViewer->setModelReference(Models::pcs);
    ui->wgtFIleChooser->asFileSaver();
    Logger::logInfo("Acquisition view initialized");
}

void AcquisitionView::viewOnFocus(bool focus)
{
    if(focus)
    {
        if(ui->chkDisableUpdates->isChecked())
            ui->wgtPCLViewer->disableUpdates();
        else
            ui->wgtPCLViewer->enableUpdates();
    } else {
        ui->wgtPCLViewer->disableUpdates();
    }
}

AcquisitionView::~AcquisitionView()
{
    delete ui;
    Logger::logInfo("Acquisition view deleted");
}

void AcquisitionView::on_btnCapture_clicked()
{
    std::string filename = ui->wgtFIleChooser->getSelectedFile();
    if(!filename.empty())
    {
        if(Models::pcs->getLastAcquisition()==NULL)
        {
            pcl::io::savePCDFileASCII(filename, *Models::pcs->getLastAcquisition());
            Logger::logInfo("Acquisition PCD captured");
            QMessageBox::information(this, "Information", "Filename saved!", QMessageBox::Ok);
        } else {
            QMessageBox::warning(this, "Error", "Nothing to acquire!", QMessageBox::Ok);
            Logger::logWarning("Acquisition PCD try capture, nothing to acquire");
        }
    } else {
        QMessageBox::warning(this, "Error", "Filename is empty!", QMessageBox::Ok);
        Logger::logWarning("Acquisition PCD try capture, filename is empty");
    }
}

void AcquisitionView::on_chkDisableUpdates_stateChanged(int arg1)
{
    if(arg1==0)
        ui->wgtPCLViewer->enableUpdates();
    else
        ui->wgtPCLViewer->disableUpdates();
}
