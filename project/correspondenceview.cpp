#include "correspondenceview.h"
#include "ui_correspondenceview.h"

CorrespondenceView::CorrespondenceView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CorrespondenceView)
{
    ui->setupUi(this);
    Models::pcs->attachObserver(this);

    ui->wgtCGFileChooser->asFileOpener();
    ui->wgtCGFileChooser->setSelectedFile(QDir::homePath().toStdString() + "/QRecog/mdl.pcd");

    ui->wgtStatCsvFileChooser->asFileSaver();
    ui->wgtStatCsvFileChooser->setFileType("CSV files (*.csv)");
    ui->wgtStatCsvFileChooser->setSelectedFile(QDir::homePath().toStdString() + "/QRecog/export.csv");
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
            cloudPtrType sceneCloud = model->getLastAcquisition();
            cloudPtrType sceneCloudFilter (new cloudType);

            computedModels.clear();
            computedModels.push_back(sceneCloud);

            if(ui->wgtFilterOptionView->isFilteringEnabled())
            {
                //PCLFilterFunction* filterf = new PCLFilterFunction();
                filterf.leafSize=ui->wgtFilterOptionView->getLeafSize();

                if(computedModels.size()==1)
                {
                    sceneCloudFilter=computedModels[0];
                    computedModels.pop_back();
                    computedModels.push_back(filterf.filter(sceneCloudFilter));
                } else
                    computedModels.push_back(filterf.filter(sceneCloud));
            }

            if(ui->wgtMinCutOptionView->isMinCutEnabled())
            {
                //PCLMinCutFunction* mincut = new PCLMinCutFunction();

                mincut.x = ui->wgtMinCutOptionView->getx();
                mincut.y = ui->wgtMinCutOptionView->gety();
                mincut.z = ui->wgtMinCutOptionView->getz();
                mincut.sigma = ui->wgtMinCutOptionView->getSigma();
                mincut.radius = ui->wgtMinCutOptionView->getRadius();
                mincut.numberOfNeighbours = ui->wgtMinCutOptionView->getNrNeighbours();
                mincut.sourceWeight = ui->wgtMinCutOptionView->getSourceWeight();

                mincut.showPreview = ui->wgtMinCutOptionView->showPreview();

                if(computedModels.size()==1)
                {
                    sceneCloudFilter=computedModels[0];

                    computedModels.pop_back();
                    computedModels.push_back(mincut.getForegroundPointCloud(sceneCloudFilter));
                } else
                    computedModels.push_back(mincut.getForegroundPointCloud(sceneCloud));
            }

            if(ui->wgtSegOptionView->isSegmentationEnabled())
            {
                //PCLSegmentationFunction* segf = new PCLSegmentationFunction();

                segf.optimazeCoeff = ui->wgtSegOptionView->getOptimizeCoeff();
                segf.modelType = ui->wgtSegOptionView->getModelType();
                segf.methodType = ui->wgtSegOptionView->getMethodType();
                segf.maxIterations = ui->wgtSegOptionView->getMaxIterations();
                segf.distanceThreashold = ui->wgtSegOptionView->getDistanceThreshold();

                if(computedModels.size()==1)
                {
                    sceneCloudFilter=computedModels[0];
                    computedModels.pop_back();
                    computedModels.push_back(segf.segment(sceneCloudFilter));
                } else
                    computedModels.push_back(segf.segment(sceneCloud));
            }

            launchRecognizer();

            if(!ui->chkDisableUpdate->isChecked())
            {
                cloudsToShow.clear();
                if(ui->chkShowTreatedScene->isChecked())
                    cloudsToShow.push_back(computedModels[0]);
                else
                    cloudsToShow.push_back(sceneCloud);

                visualizeRecognizerOutput();

                ui->wgtPCLViewer->updateView(cloudsToShow);

                setupColorForClouds();
            }

            ui->lcdNrModelRec->display(cff.getNrModelFound());
            ui->lcdNrCorrespondence->display(static_cast<int>(cff.modelSceneCorrs->size ()));
        } else {
            ui->lcdNrModelRec->display(0);
            ui->lcdNrCorrespondence->display(0);
        }
        ui->lcdCompTime->display((int)computationTimer->elapsed());

        if(ui->chkEnableStatToCsv->isChecked())
            exportResultOnCSV();
    }
}

void CorrespondenceView::launchRecognizer(){
    cff.modelSampleSize            = ui->spnModelss->value();
    cff.sceneSampleSize            = ui->spnSceness->value();
    cff.descriptorsRadius          = ui->spnDescRad->value();
    cff.referenceFrameRadius       = ui->spnRFRad->value();
    cff.cgSize                     = ui->spnCGSize->value();
    cff.cgThreshold                = ui->spnCGThres->value();
    cff.useHough                   = ui->rdbHough->isChecked();
    cff.applyTrasformationToModel  = ui->chkApplyTrasformModel->isChecked();
    cff.useCloudResolution         = ui->chkComputeModelRes->isChecked();
    cff.model                      = searchedModels[0];
    cff.scene                      = computedModels[0];
    cff.recognize();
}

void CorrespondenceView::visualizeRecognizerOutput(){
    modelAdded=false;
    correspondenceAdded=false;
    if(cff.getNrModelFound()>0) {
        cloudsToShow.push_back(cff.getCorrespondence());
        correspondenceAdded=true;
    }

    // Set up and show offset model
    if ( ui->chkShowUsedkeypoints->isChecked() || ui->chkShowCorr->isChecked()){
        cff.setUpOffSceneModel();
        cloudsToShow.push_back(cff.offSceneModel);
        modelAdded=true;
    }

    // show keypoints
    if ( ui->chkShowUsedkeypoints->isChecked()){
        cloudsToShow.push_back(cff.sceneKeypoints);
        cloudsToShow.push_back(cff.offSceneModelKeypoints);
    }
}

void CorrespondenceView::setupColorForClouds()
{
    if(correspondenceAdded)
        ui->wgtPCLViewer->viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "cloud1");

    // show keypoints
    if ( ui->chkShowUsedkeypoints->isChecked()){
        std::string sceneKeypointsCloud;
        std::string modelKeypointsCloud;
        if(!modelAdded && !correspondenceAdded) {
            sceneKeypointsCloud = "cloud1";
            modelKeypointsCloud = "cloud2";
        } else {
            if(modelAdded && correspondenceAdded) {
                sceneKeypointsCloud = "cloud3";
                modelKeypointsCloud = "cloud4";
            } else {
                sceneKeypointsCloud = "cloud2";
                modelKeypointsCloud = "cloud3";
            }
        }

        ui->wgtPCLViewer->viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, sceneKeypointsCloud);
        ui->wgtPCLViewer->viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 0, 0, 255, sceneKeypointsCloud);
        ui->wgtPCLViewer->viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, modelKeypointsCloud);
        ui->wgtPCLViewer->viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 0, 0, 255, modelKeypointsCloud);
    }
}

void CorrespondenceView::exportResultOnCSV()
{
    std::ofstream fwrite;
    fwrite.open(ui->wgtStatCsvFileChooser->getSelectedFile(),
                ios::out | ios::app);
    fwrite
            /********* GENERAL PARAMETER **************/
            <<ui->lcdNrModelRec->value()<<";"
           <<ui->lcdNrCorrespondence->value()<<";"
          <<ui->lcdCompTime->value()<<";"
         <<cff.modelKeypoints->size()<<";"
        <<cff.sceneKeypoints->size()<<";"
       <<cff.modelNormals->size()<<";"
      <<cff.sceneNormals->size()<<";"
     <<cff.modelDescriptors->size()<<";"
    <<cff.sceneDescriptors->size()<<";"
    <<ui->chkDisableUpdate->isChecked()<<";"
    <<ui->chkShowUsedkeypoints->isChecked()<<";"


      /********* FILTER PARAMETERS *************/
    <<ui->wgtFilterOptionView->isFilteringEnabled()<<";"
    <<filterf.leafSize<<";"

      /********* MIN CUT PARAMETER *************/
    <<ui->wgtMinCutOptionView->isMinCutEnabled()<<";"
    <<mincut.x<<";"
    <<mincut.y<<";"
    <<mincut.z<<";"
    <<mincut.sigma<<";"
    <<mincut.radius<<";"
    <<mincut.numberOfNeighbours<<";"
    <<mincut.sourceWeight<<";"

      /********* RANSAC PARAMETER **************/
    <<ui->wgtSegOptionView->isSegmentationEnabled()<<";"
    <<segf.optimazeCoeff<<";"
    <<segf.modelType<<";"
    <<segf.methodType<<";"
    <<segf.maxIterations<<";"
    <<segf.distanceThreashold<<";"

      /*** RECOGNITION PARAMETERS *******/
    <<cff.modelSampleSize<<";"
    <<cff.sceneSampleSize<<";"
    <<cff.descriptorsRadius<<";"
    <<cff.referenceFrameRadius<<";"
    <<cff.cgSize<<";"
    <<cff.cgThreshold<<";"
    <<cff.useHough<<";"
    <<cff.applyTrasformationToModel<<";"
    <<cff.useCloudResolution<<";"

    <<std::endl;

    fwrite.close();
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

    cloudPtrType cloud (new cloudType);
    pcl::io::loadPCDFile(filename, *cloud);

    searchedModels.clear();
    searchedModels.push_back(cloud);

    QMessageBox::information(this, "Information", "Model set correctly", QMessageBox::Ok);
    Logger::logInfo("Model for correspondence grouping loaded");

    cff.computeModelKeypoints=true;
    ui->wgtPCLViewer->viewer->removePointCloud("correspondence");
    correspondenceCloud=false;
}

void CorrespondenceView::on_spnModelss_valueChanged(double arg1)
{
    cff.computeModelKeypoints=true;
}

void CorrespondenceView::on_spnSceness_valueChanged(double arg1)
{
    cff.computeModelKeypoints=true;
}

void CorrespondenceView::on_spnDescRad_valueChanged(double arg1)
{
    cff.computeModelKeypoints=true;
}

void CorrespondenceView::on_spnRFRad_valueChanged(double arg1)
{
    cff.computeModelKeypoints=true;
}

void CorrespondenceView::on_spnCGSize_valueChanged(double arg1)
{
    cff.computeModelKeypoints=true;
}

void CorrespondenceView::on_spnCGThres_valueChanged(double arg1)
{
    cff.computeModelKeypoints=true;
}

void CorrespondenceView::on_chkEnableStatToCsv_toggled(bool checked)
{
    if(checked) {

        std::ofstream fwrite;
        fwrite.open(ui->wgtStatCsvFileChooser->getSelectedFile());
        fwrite
                /********* GENERAL PARAMETER **************/
                <<"#ModelFound;"
               <<"#Correspondence;"
              <<"#ComputationTime;"
             <<"#ModelKeypoints;"
            <<"#SceneKeypoints;"
           <<"#ModelNormals;"
          <<"#SceneNormals;"
         <<"#ModelDescriptors;"
        <<"#SceneDescriptors;"
        <<"UpdateUI?;"
        <<"ShowKeypoints?;"

          /********* FILTER PARAMETERS *************/
        <<"FilterEn?;"
        <<"FilterLeafSize;"

          /********* MIN CUT PARAMETER *************/
        <<"MinCutEn?;"
        <<"MinCutX;"
        <<"MinCutY;"
        <<"MinCutZ;"
        <<"MinCutSigma;"
        <<"MinCutRadius;"
        <<"MinCut#Neighboors;"
        <<"MinCutSourceWeight;"

          /********* RANSAC PARAMETER **************/
        <<"SACEn?;"
        <<"SACOptimazeCoef;"
        <<"SACModelType;"
        <<"SACMethodType;"
        <<"SACMaxIteration;"
        <<"SACDistanceThreashold;"

          /*** RECOGNITION PARAMETERS *******/
        <<"CFFModelDownsample;"
        <<"CFFSceneDownsample;"
        <<"CFFDescrRadius;"
        <<"CFFRefFrameRadius;"
        <<"CFFCGSize;"
        <<"CFFCGThreashold;"
        <<"CFFUseHough;"
        <<"CFFApplyTrasf;"
        <<"CFFUseCloudRes;"

        <<std::endl;

        fwrite.close();
    }
}
