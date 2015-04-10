#include "clusteringview.h"
#include "ui_clusteringview.h"

ClusteringView::ClusteringView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClusteringView)
{
    ui->setupUi(this);

    ui->wgtSegFileChooser->asFileOpener();
    ui->wgtOutFileChooser->asFileSaver();
}

void ClusteringView::on_btnSegment_clicked()
{
    std::string filename = ui->wgtSegFileChooser->getSelectedFile();
    if(filename.empty())
    {
        QMessageBox::warning(this, "Error", "Target file is empty", QMessageBox::Ok);
        Logger::logWarning("Clustering target file is empty");
    }

    cloudPtrType cloud (new cloudType), cloud_f (new cloudType);
    pcl::io::loadPCDFile(filename, *cloud);

    computedModels.clear();
    computedModelsKeypoints.clear();
    descriptors.clear();

    computationTimer.restart();

    computedModels.push_back(cloud);

    if(ui->wgtFilterOptionView->isFilteringEnabled())
    {
        PCLFilterFunction* filterf = new PCLFilterFunction();

        filterf->leafSize=ui->wgtFilterOptionView->getLeafSize();

        if(computedModels.size()==1)
        {
            cloud_f=computedModels[0];

            computedModels.pop_back();
            computedModels.push_back(filterf->filter(cloud_f));
        } else
            computedModels.push_back(filterf->filter(cloud));
    }

    if(ui->wgtMinCutOptionView->isMinCutEnabled())
    {
        PCLMinCutFunction* mincut = new PCLMinCutFunction();

        mincut->x = ui->wgtMinCutOptionView->getx();
        mincut->y = ui->wgtMinCutOptionView->gety();
        mincut->z = ui->wgtMinCutOptionView->getz();
        mincut->sigma = ui->wgtMinCutOptionView->getSigma();
        mincut->radius = ui->wgtMinCutOptionView->getRadius();
        mincut->numberOfNeighbours = ui->wgtMinCutOptionView->getNrNeighbours();
        mincut->sourceWeight = ui->wgtMinCutOptionView->getSourceWeight();

        mincut->showPreview = ui->wgtMinCutOptionView->showPreview();

        if(computedModels.size()==1)
        {
            cloud_f=computedModels[0];

            computedModels.pop_back();
            computedModels.push_back(mincut->getForegroundPointCloud(cloud_f));
        } else
            computedModels.push_back(mincut->getForegroundPointCloud(cloud));
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

        if(ui->wgtClusterOptionView->showUsedKeypoints()) {
            PCLCorrGroupFunction* cgf = new PCLCorrGroupFunction();
            cgf->modelSampleSize = ui->wgtClusterOptionView->getModelSample();
            cgf->descriptorsRadius = ui->wgtClusterOptionView->getDescriptorRadius();
            foreach (cloudPtrType model, computedModels) {
                cloudPtrType keypoints = cgf->computeKeypointsForThisModel(model);
                computedModelsKeypoints.push_back(keypoints);
                descriptors.push_back(static_cast<int>(cgf->modelDescriptors->size()));
            }
        }
    }

    ui->lcdCompTime->display((int)computationTimer.elapsed());

    actualModelViewer=0;
    changePClViewerModel(0);
}

void ClusteringView::changePClViewerModel(unsigned int index)
{
    if(computedModels.size()!=0)
    {
        if(index>=computedModels.size())
            index=computedModels.size()-1;

        std::vector<cloudPtrType> modelsToShow;

        modelsToShow.push_back(computedModels[index]);
        ui->lcdNrCloudsPoints->display(static_cast<int>(computedModels[index]->points.size()));

        //Show used key points
        if(ui->wgtClusterOptionView->isClusteringEnabled()) {
            if(ui->wgtClusterOptionView->showUsedKeypoints()) {
                Logger::logDebug("Clustering view - Add keypoint to clustered model");
                modelsToShow.push_back(computedModelsKeypoints[index]);
                ui->lcdNrKeyPoints->display(static_cast<int>(computedModelsKeypoints[index]->points.size()));
                ui->lcdNrDescriptors->display(descriptors[index]);
            } else {
                Logger::logDebug("Clustering view - Not show keypoints for clustered model");
                ui->lcdNrKeyPoints->display(0);
                ui->lcdNrDescriptors->display(0);
            }

            if(ui->wgtClusterOptionView->showUsedKeypoints()) {
                Logger::logDebug("Clustering view - Setting up colors for clusted model keypoints");
                ui->wgtPCLViewer->viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "cloud1");
                ui->wgtPCLViewer->viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 0, 0, 255, "cloud1");
            }
        }

        ui->wgtPCLViewer->updateView(modelsToShow);

        if(actualModelViewer<=0)
            ui->btnPrevModel->setEnabled(false);
        else
            ui->btnPrevModel->setEnabled(true);

        if(actualModelViewer>=computedModels.size()-1)
            ui->btnNextModel->setEnabled(false);
        else
            ui->btnNextModel->setEnabled(true);


        Logger::logDebug("Clustering view - modelsSize: " + std::to_string(modelsToShow.size())
                         + "; Show? " + std::to_string(ui->wgtClusterOptionView->showUsedKeypoints()));

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
            QMessageBox::warning(this, "Info", "Clustered PCD saved!", QMessageBox::Ok);
        } else {
            QMessageBox::warning(this, "Error", "Nothing to save!", QMessageBox::Ok);
            Logger::logWarning("Try save Clustered PCD, but array is empty");
        }
    } else {
        QMessageBox::warning(this, "Error", "Filename is empty!", QMessageBox::Ok);
        Logger::logWarning("Try save Clustered PCD, filename is empty");
    }
}
