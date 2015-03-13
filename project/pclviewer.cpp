#include "pclviewer.h"
#include "ui_pclviewer.h"

PCLViewer::PCLViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PCLViewer)
{
    ui->setupUi(this);

    // Set up the QVTK window
    viewer.reset (new pcl::visualization::PCLVisualizer ("viewer", false));
    ui->qvtkWidget->SetRenderWindow (viewer->getRenderWindow ());
    viewer->setupInteractor (ui->qvtkWidget->GetInteractor (), ui->qvtkWidget->GetRenderWindow ());
    ui->qvtkWidget->update ();
}

void PCLViewer::setModelReference(PCSource *pcs)
{
    pcs->attachObserver(this);
    Logger::logInfo("Observed model attached to PCLViewer");
}

void PCLViewer::disableUpdates()
{
    disableUpdate=true;
}

void PCLViewer::enableUpdates()
{
    disableUpdate=false;
}

void PCLViewer::update(Observable *obs)
{
    if(!disableUpdate) {
        PCSource* model = (PCSource*) obs;
        updateView(model->getLastAcquisition());
    } else {
        Logger::logInfo("PCLViewer update received but disabled");
    }

}

void PCLViewer::updateView(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud)
{
    viewer->removeAllPointClouds();
    viewer->addPointCloud (cloud);
    viewer->resetCamera ();
    ui->qvtkWidget->update ();
    Logger::logInfo("PCLViewer update");
}

PCLViewer::~PCLViewer()
{
    delete ui;
}
