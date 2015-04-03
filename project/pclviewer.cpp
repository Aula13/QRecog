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
    viewer->setupInteractor (ui->qvtkWidget->GetInteractor (), ui->qvtkWidget->GetRenderWindow ());
    ui->qvtkWidget->update ();
    //viewer->resetCamera ();
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

void PCLViewer::updateView(std::vector<cloudPtrType> clouds)
{
    Logger::logDebug("PLCViewer - update view with cloudsToShow size: " + std::to_string(clouds.size()));
    Logger::logDebug("PLCViewer - update view previus clouds size: " + std::to_string(existentClouds.size()));

    //Remove unused existent clouds
    if(clouds.size()<existentClouds.size()) {
        for (unsigned int i=existentClouds.size()-1; i>clouds.size()-1; i--) {
            std::string id = "cloud" + boost::lexical_cast<std::string>(i);
            viewer->removePointCloud(id);
            existentClouds.remove(id);
            Logger::logDebug("PLCViewer - Cloud " + id + " removed");
        }
    }

    //Add or update existent clouds
    int i = 0;
    foreach (cloudPtrType aCloud, clouds) {

        std::string id = "cloud" + boost::lexical_cast<std::string>(i);

        addOrUpdateCloud(aCloud, id);

        i++;
    }

    Logger::logInfo("PCLViewer update");
}

void PCLViewer::updateView(cloudPtrType cloud)
{

    std::string id = "cloud0";

    addOrUpdateCloud(cloud, id);

    Logger::logInfo("PCLViewer - Single cloud update cloud0");
}

void PCLViewer::addOrUpdateCloud(cloudPtrType cloud, std::string cloud_id) {
    cloudPtrType cloud_(new cloudType (*cloud));

    bool cloudExist = false;
    foreach (std::string id, existentClouds) {
        if(id.compare(cloud_id)==0)
        {
            cloudExist = true;
            Logger::logInfo("PLCViewer - addorupdatecloud name: " + id + " already exist");
            break;
        }
    }

    if (cloudExist)
    {
        viewer->updatePointCloud (cloud_, cloud_id);
        Logger::logDebug("Update cloud to PLCViewer name: " + cloud_id);
    } else {
        viewer->addPointCloud (cloud_, cloud_id);
        existentClouds.push_back(cloud_id);
        Logger::logDebug("Add cloud to PLCViewer name: " + cloud_id);
    }

    ui->qvtkWidget->update();
}

void PCLViewer::updateView(){
    ui->qvtkWidget->update ();
}

PCLViewer::~PCLViewer()
{
    delete ui;
}
