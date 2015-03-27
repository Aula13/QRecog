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
    //
    // ho commentato questa linea perchè sembra che sia la causa
    // del problema che ho con la visualizzazione, a me così funziona molto meglio
    // e posso comunque interagire con la pcl, se a te ora non funziona la causa è questa sicuramente.
    //
    // viewer->setupInteractor (ui->qvtkWidget->GetInteractor (), ui->qvtkWidget->GetRenderWindow ());
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

        std::vector<pcl::PointCloud<pcl::PointXYZRGBA>::Ptr> clouds;
        clouds.push_back(model->getLastAcquisition());
        updateView(clouds);
    } else {
        Logger::logInfo("PCLViewer update received but disabled");
    }
}

void PCLViewer::updateView(std::vector<pcl::PointCloud<pcl::PointXYZRGBA>::Ptr> clouds)
{
    viewer->removeAllPointClouds();
    Logger::logDebug("Existent point cloud removed from PLCViewer");

    /*
    int i = 0;
    foreach (pcl::PointCloud<pcl::PointXYZRGBA>::Ptr aCloud, clouds) {
        viewer->addPointCloud (aCloud, "cloud" + boost::lexical_cast<std::string>(i));
        Logger::logDebug("Add cloud to PLCViewer");
        i++;
    }
    */

    viewer->addPointCloud(clouds[0], "c");

    //viewer->resetCamera ();

    ui->qvtkWidget->update ();
    Logger::logInfo("PCLViewer update");
}

void PCLViewer::updateView(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud)
{
    viewer->removeAllPointClouds();
    viewer->removeAllShapes();

    Logger::logDebug("Existent point cloud removed from PLCViewer");

    viewer->addPointCloud (cloud);

    Logger::logDebug("Add cloud to PLCViewer");

    //viewer->resetCamera ();

    ui->qvtkWidget->update ();
    Logger::logInfo("PCLViewer update");
}

void PCLViewer::updateView(){
    ui->qvtkWidget->update ();
}

PCLViewer::~PCLViewer()
{
    delete ui;
}
