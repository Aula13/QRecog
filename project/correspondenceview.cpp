#include "correspondenceview.h"
#include "ui_correspondenceview.h"

CorrespondenceView::CorrespondenceView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CorrespondenceView)
{
    ui->setupUi(this);
    Models::pcs->attachObserver(this);

    ui->wgtCGFileChooser->asFileOpener();
    ui->wgtCGFileChooser->setSelectedFile(QDir::homePath().toStdString() + "/QRecog/working(old)/cloud_cluster_1.pcd");
    Logger::logInfo("Correspondence view initialized");

    computationTimer = new QElapsedTimer();
}

void CorrespondenceView::viewOnFocus(bool focus)
{
    viewHasFocus = focus;
}

void CorrespondenceView::update(Observable* obs)
{
    if(viewHasFocus)
    {
        computationTimer->restart();
        if (searchedModels.size()!=0)
        {
            PCSource* model = (PCSource*) obs;
            pcl::PointCloud<pcl::PointXYZRGBA>::Ptr sceneCloud = model->getLastAcquisition();
            pcl::PointCloud<pcl::PointXYZRGBA>::Ptr sceneCloudFilter (new pcl::PointCloud<pcl::PointXYZRGBA>);

            computedModels.clear();
            computedModels.push_back(sceneCloud);

            if(ui->wgtFilterOptionView->isFilteringEnabled())
            {
                PCLFilterFunction* filterf = new PCLFilterFunction();

                filterf->leafSize=ui->wgtFilterOptionView->getLeafSize();

                if(computedModels.size()==1)
                {
                    sceneCloudFilter=computedModels[0];
                    computedModels.pop_back();
                    computedModels.push_back(filterf->filter(sceneCloudFilter));
                } else
                    computedModels.push_back(filterf->filter(sceneCloud));
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
                    sceneCloudFilter=computedModels[0];
                    computedModels.pop_back();
                    computedModels.push_back(segf->segment(sceneCloudFilter));
                } else
                    computedModels.push_back(segf->segment(sceneCloud));
            }

            launchRecognizer(cff);

            if(!ui->chkDisableUpdate->isChecked())
            {
                ui->wgtPCLViewer->updateView(sceneCloud);
                visualizeRecognizerOutput(cff);
            }

            ui->lcdNrModelRec->display(cff->getNrModelFounded());
        } else
            ui->lcdNrModelRec->display(0);
        ui->lcdCompTime->display((int)computationTimer->elapsed());
    }
}

void CorrespondenceView::launchRecognizer(PCLCorrGroupFunction *cff){
    cff->modelSampleSize            = ui->spnModelss->value();
    cff->sceneSampleSize            = ui->spnSceness->value();
    cff->descriptorsRadius          = ui->spnDescRad->value();
    cff->referenceFrameRadius       = ui->spnRFRad->value();
    cff->cgSize                     = ui->spnCGSize->value();
    cff->cgThreshold                = ui->spnCGThres->value();
    cff->useHough                   = ui->rdbHough->isChecked();
    cff->applyTrasformationToModel  = ui->chkApplyTrasformModel->isChecked();
    cff->useCloudResolution         = ui->chkComputeModelRes->isChecked();
    cff->model                      = searchedModels[0];
    cff->scene                      = computedModels[0];
    cff->recognize();
}

void CorrespondenceView::visualizeRecognizerOutput(PCLCorrGroupFunction* cff){

    // Set up and show offset model
    if ( ui->chkShowUsedkeypoints->isChecked() || ui->chkShowCorr->isChecked()){
        cff->setUpOffSceneModel();
        pcl::visualization::PointCloudColorHandlerCustom<PointType> offSceneModelColorHandler (cff->offSceneModel, 255, 255, 128);
        ui->wgtPCLViewer->viewer->addPointCloud (cff->offSceneModel, offSceneModelColorHandler, "off_scene_model");
    }
    // show keypoints
    if ( ui->chkShowUsedkeypoints->isChecked()){
        pcl::visualization::PointCloudColorHandlerCustom<PointType> sceneKeypointsColorHandler (cff->sceneKeypoints, 0, 0, 255);
        ui->wgtPCLViewer->viewer->addPointCloud (cff->sceneKeypoints, sceneKeypointsColorHandler, "scene_keypoints");
        ui->wgtPCLViewer->viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "scene_keypoints");

        pcl::visualization::PointCloudColorHandlerCustom<PointType> offSceneModelKeypointsColorHandler (cff->offSceneModelKeypoints, 0, 0, 255);
        ui->wgtPCLViewer->viewer->addPointCloud (cff->offSceneModelKeypoints, offSceneModelKeypointsColorHandler, "off_scene_model_keypoints");
        ui->wgtPCLViewer->viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "off_scene_model_keypoints");
    }

    if(cff->getNrModelFounded()>0) {
        if(correspondenceCloud) {
            ui->wgtPCLViewer->viewer->updatePointCloud (cff->getCorrespondence(), "correspondence");
        } else {
            ui->wgtPCLViewer->viewer->addPointCloud (cff->getCorrespondence(), "correspondence");
            correspondenceCloud=true;
        }
    } else {
        ui->wgtPCLViewer->viewer->removePointCloud("correspondence");
        correspondenceCloud=false;
    }


    // show models correspondences
    /*for (size_t i = 0; i < cff->rototranslations.size (); ++i)
    {
        cloudPtr rotatedModel (new pcl::PointCloud<PointType> ());
        pcl::transformPointCloud(*cff->model, *rotatedModel, cff->rototranslations[i]);


        std::stringstream ssCloud;
        ssCloud << "instance" << i;

        pcl::visualization::PointCloudColorHandlerCustom<PointType> rotatedModelColorHandler (rotatedModel, 255, 0, 0);
        ui->wgtPCLViewer->viewer->removePointCloud(ssCloud.str());
        ui->wgtPCLViewer->viewer->addPointCloud (rotatedModel, rotatedModelColorHandler, ssCloud.str ());

        // show point to point correspondences
        if (ui->chkShowCorr->isChecked())
        {
            for (size_t j = 0; j < cff->clusteredCorrs[i].size (); ++j)
            {
                std::stringstream ssLine;
                ssLine << "correspondence_line" << i << "_" << j;
                PointType& modelPoint = cff->offSceneModelKeypoints->at (cff->clusteredCorrs[i][j].index_query);
                PointType& scenePoint = cff->sceneKeypoints->at (cff->clusteredCorrs[i][j].index_match);

                //  We are drawing a line for each pair of clustered correspondences found between the model and the scene
                ui->wgtPCLViewer->viewer->addLine<PointType, PointType> (modelPoint, scenePoint, 0, 255, 0, ssLine.str ());
            }
        }
    }*/
}

CorrespondenceView::~CorrespondenceView()
{
    delete ui;
}

void CorrespondenceView::on_chkDisableUpdate_stateChanged(int arg1)
{
    if(arg1==0)
        ui->wgtPCLViewer->enableUpdates();
    else
        ui->wgtPCLViewer->disableUpdates();
}

void CorrespondenceView::on_btnSetModel_clicked()
{

    std::string filename = ui->wgtCGFileChooser->getSelectedFile();
    if(filename.empty())
    {
        QMessageBox::warning(this, "Error", "Target file is empty", QMessageBox::Ok);
        Logger::logWarning("Clustering target file is empty");
        return;
    }

    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGBA>);
    pcl::io::loadPCDFile(filename, *cloud);

    searchedModels.clear();
    searchedModels.push_back(cloud);

    QMessageBox::information(this, "Information", "Model set correctly", QMessageBox::Ok);
    Logger::logInfo("Model for correspondence grouping loaded");

    cff->computeModelKeypoints=true;
    ui->wgtPCLViewer->viewer->removePointCloud("correspondence");
    correspondenceCloud=false;
}

void CorrespondenceView::on_spnModelss_valueChanged(double arg1)
{
    cff->computeModelKeypoints=true;
}

void CorrespondenceView::on_spnSceness_valueChanged(double arg1)
{
    cff->computeModelKeypoints=true;
}

void CorrespondenceView::on_spnDescRad_valueChanged(double arg1)
{
    cff->computeModelKeypoints=true;
}

void CorrespondenceView::on_spnRFRad_valueChanged(double arg1)
{
    cff->computeModelKeypoints=true;
}

void CorrespondenceView::on_spnCGSize_valueChanged(double arg1)
{
    cff->computeModelKeypoints=true;
}

void CorrespondenceView::on_spnCGThres_valueChanged(double arg1)
{
    cff->computeModelKeypoints=true;
}
