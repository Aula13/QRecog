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

PCLViewer::~PCLViewer()
{
    delete ui;
}
