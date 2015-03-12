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

    CameraModel::getInstance()->attachObserver(this);
}

void PCLViewer::update(Observable *obs)
{
    CameraModel* model = (CameraModel*) obs;
    viewer->addPointCloud (model->getLastAcquisition(), "cloud");
    viewer->resetCamera ();
    ui->qvtkWidget->update ();

    Logger::logInfo("PCLViewer update");
}

PCLViewer::~PCLViewer()
{
    delete ui;
}
