#include "correspondenceview.h"
#include "ui_correspondenceview.h"

CorrespondenceView::CorrespondenceView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CorrespondenceView)
{
    ui->setupUi(this);

    Models::pcs->attachObserver(this);
    ui->wgtCGFileChooser->asFileOpener();
    Logger::logInfo("Correspondence view initialized");
}

void CorrespondenceView::update(Observable* obs)
{
    if (searchedModels.size()!=0)
    {
        PCSource* model = (PCSource*) obs;
        pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud = model->getLastAcquisition();
        pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud_f (new pcl::PointCloud<pcl::PointXYZRGBA>);

        computedModels.clear();
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

        PCLCorrGroupFunction* cff = new PCLCorrGroupFunction();

        cff->model_ss = ui->spnModelss->value();
        cff->scene_ss = ui->spnSceness->value();
        cff->descr_rad = ui->spnDescRad->value();
        cff->rf_rad = ui->spnRFRad->value();
        cff->cg_size = ui->spnCGSize->value();
        cff->cg_threshold = ui->spnCGThres->value();

        cff->useHough = ui->rdbHough->isChecked();

        cff->applyTrasformationToModel = ui->chkApplyTrasformModel->isChecked();
        cff->showUsedKeypoints = ui->chkShowUsedkeypoints->isChecked();
        cff->showUsedCorrespondence = ui->chkShowCorr->isChecked();

        cff->useCloudResolution = ui->chkComputeModelRes->isChecked();

        cff->setModelCloud(searchedModels[0]);

        std::vector<pcl::PointCloud<pcl::PointXYZRGBA>::Ptr> resultClouds;

        resultClouds.push_back(cff->getCorrespondence(computedModels[0]));

        ui->wgtPCLViewer->updateView(resultClouds);
    }
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

    QMessageBox::information(this, "Information", "Model is setted for correspondence", QMessageBox::Ok);
    Logger::logInfo("Model for correspondence grouping loaded");
}
