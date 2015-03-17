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
        PCLClusteringFunction* clusterf = new PCLClusteringFunction();

        clusterf->clusterTolerance = ui->wgtClusterOptionView->getClusterTolerance();
        clusterf->minClusterSize = ui->wgtClusterOptionView->getMinClusterSize();
        clusterf->maxClusterSize = ui->wgtClusterOptionView->getMaxClusterSize();

        if(computedModels.size()==1)
        {
            cloud_f=computedModels[0];
            computedModels.pop_back();
            computedModels = clusterf->clustering(cloud_f);
        } else
            computedModels = clusterf->clustering(cloud);
    }
    actualModelViewer=0;
    changePClViewerModel(0);
}

void ClusteringView::changePClViewerModel(int index)
{
    if(computedModels.size()!=0)
    {
        if(index<0)
            index=0;
        if(index>=computedModels.size())
            index=computedModels.size()-1;

        ui->wgtPCLViewer->updateView(computedModels);

        if(actualModelViewer<=0)
            ui->btnPrevModel->setEnabled(false);
        else
            ui->btnPrevModel->setEnabled(true);

        if(actualModelViewer>=computedModels.size()-1)
            ui->btnNextModel->setEnabled(false);
        else
            ui->btnNextModel->setEnabled(true);
    }
}

ClusteringView::~ClusteringView()
{
    delete ui;
}



void ClusteringView::on_btnPrevModel_clicked()
{
    if(computedModels.size()!=0)
    {
        actualModelViewer--;
        if(actualModelViewer<=0)
            actualModelViewer=0;

        changePClViewerModel(actualModelViewer);
    }
}

void ClusteringView::on_btnNextModel_clicked()
{
    if(computedModels.size()!=0)
    {
        actualModelViewer++;
        if(actualModelViewer>=computedModels.size()-1)
            actualModelViewer=computedModels.size()-1;

        changePClViewerModel(actualModelViewer);
    }
}

void ClusteringView::on_btnSaveModel_clicked()
{
    std::string filename = ui->wgtOutFileChooser->getSelectedFile();
    if(!filename.empty())
    {
        if(!computedModels.empty())
        {
            pcl::io::savePCDFileASCII(filename, *computedModels[actualModelViewer]);
            Logger::logWarning("Clustered PCD saved");
            QMessageBox::warning(this, "Error", "Clustered PCD saved!", QMessageBox::Ok);
        } else {
            QMessageBox::warning(this, "Error", "Nothing to save!", QMessageBox::Ok);
            Logger::logWarning("Try save Clustered PCD, but array is empty");
        }
    } else {
        QMessageBox::warning(this, "Error", "Filename is empty!", QMessageBox::Ok);
        Logger::logWarning("Try save Clustered PCD, filename is empty");
    }
}
