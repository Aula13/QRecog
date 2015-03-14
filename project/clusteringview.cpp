#include "clusteringview.h"
#include "ui_clusteringview.h"

ClusteringView::ClusteringView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClusteringView)
{
    ui->setupUi(this);

    ui->wgtSegFileChooser->asFileOpener();
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

    computedModels.clear();

    if(ui->wgtFilterOptionView->isFilteringEnabled())
    {
        PCLFilterFunction* filterf = new PCLFilterFunction();

        filterf->leafSize=ui->wgtFilterOptionView->getLeafSize();

        computedModels.push_back(filterf->filter(cloud));
    }

    if(ui->wgtSegOptionView->isSegmentationEnabled())
    {
        PCLSegmentationFunction* segf = new PCLSegmentationFunction();

        segf->optimazeCoeff = ui->wgtSegOptionView->getOptimizeCoeff();
        segf->modelType = ui->wgtSegOptionView->getModelType();
        segf->methodType = ui->wgtSegOptionView->getMethodType();
        segf->maxIterations = ui->wgtSegOptionView->getMaxIterations();
        segf->distanceThreashold = ui->wgtSegOptionView->getDistanceThreshold();

        if(computedModels.size()==1)
        {
            cloud_f=computedModels[0];
            computedModels.pop_back();
            computedModels.push_back(segf->segment(cloud_f));
        } else
            computedModels.push_back(segf->segment(cloud));
    }

    if(ui->wgtClusterOptionView->isClusteringEnabled())
    {

    }

    changePClViewerModel(0);
}

void ClusteringView::changePClViewerModel(int index)
{
    ui->wgtPCLViewer->updateView(computedModels[0]);
}

ClusteringView::~ClusteringView()
{
    delete ui;
}


