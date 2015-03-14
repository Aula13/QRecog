#include "clusteringview.h"
#include "ui_clusteringview.h"

ClusteringView::ClusteringView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClusteringView)
{
    ui->setupUi(this);

    ui->wgtSegFileChooser->asFileOpener();
}

ClusteringView::~ClusteringView()
{
    delete ui;
}

void ClusteringView::on_btnSegment_clicked()
{
    std::string filename = ui->wgtSegFileChooser->getSelectedFile();
    if(filename.empty())
    {
        QMessageBox::warning(this, "Error", "Target file is empty", QMessageBox::Ok);
        Logger::logWarning("Clustering target file is empty");
    }

    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGBA>), cloud_f (new pcl::PointCloud<pcl::PointXYZRGBA>);
    pcl::io::loadPCDFile(filename, *cloud);

    PCLFilterFunction* filterf = new PCLFilterFunction();

    filterf->leafSize=ui->wgtFilterOptionView->getLeafSize();

    PCLSegmentationFunction* segf = new PCLSegmentationFunction();

    segf->optimazeCoeff = ui->wgtSegOptionView->getOptimizeCoeff();
    segf->modelType = ui->wgtSegOptionView->getModelType();
    segf->methodType = ui->wgtSegOptionView->getMethodType();
    segf->maxIterations = ui->wgtSegOptionView->getMaxIterations();
    segf->distanceThreashold = ui->wgtSegOptionView->getDistanceThreshold();

    ui->wgtPCLViewer->updateView(segf->segment(filterf->filter(cloud)));
}
