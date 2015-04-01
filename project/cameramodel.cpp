#include "cameramodel.h"

bool CameraModel::instanceFlag=false;
CameraModel* CameraModel::single=NULL;

CameraModel* CameraModel::getInstance()
{
    if(! instanceFlag)
    {
        single = new CameraModel();
        instanceFlag = true;
        Logger::logInfo("Request CameraModel instance (new one builded)");
        return single;
    }
    else
    {
        Logger::logInfo("Request CameraModel instance (already existent)");
        return single;
    }
}

CameraModel::CameraModel()
{
}

void CameraModel::registerCallback(boost::function<void (const cloudType::ConstPtr&)> f)
{
    if(instanceFlag)
        interface->registerCallback(f);
}

void CameraModel::cloud_cb_ (const cloudType::ConstPtr &cloud)
{
    cloudPtrType cloud0(new cloudType (*cloud));
    std::vector<int> mapping;
    pcl::removeNaNFromPointCloud(*cloud, *cloud0, mapping);

    Eigen::Matrix4f TransMat=Eigen::Matrix4f::Identity();

    //Rotazione della point cloud attorno all'asse Z di 180 gradi
    float theta = M_PI; // The angle of rotation in radians
    TransMat(0,0) = cos(theta);
    TransMat(0,1) = -sin(theta);
    TransMat(1,0) = sin(theta);
    TransMat(1,1) = cos(theta);

    cloudPtrType cloud1(new cloudType (*cloud0));


    //trasformedpcd = new cloudPtr (*cloud);
    pcl::transformPointCloud(*cloud1,*cloud1,TransMat);

    //Rotazione della point cloud attorno all'asse Y di 180 gradi
    TransMat=Eigen::Matrix4f::Identity();

    theta = M_PI; // The angle of rotation in radians
    TransMat(0,0) = cos(theta);
    TransMat(0,2) = sin(theta);
    TransMat(2,0) = -sin(theta);
    TransMat(2,2) = cos(theta);

    pcl::transformPointCloud(*cloud1,*cloud1,TransMat);

    trasformedpcd = cloud1;

    Logger::logInfo("Update cloud is coming");

    setChanged();
    notifyObservers();

    std::this_thread::sleep_for(std::chrono::milliseconds(60));
}

void CameraModel::run()
{
    if(instanceFlag)
    {
        interface = new pcl::io::OpenNI2Grabber("", depthImgMode, imgMode);

        boost::function<void (const cloudType::ConstPtr&)> f = boost::bind (&CameraModel::cloud_cb_, this, _1);
        interface->registerCallback(f);

        interface->start ();
        Logger::logInfo("Camera interface is started");
    } else
        Logger::logError("CameraModel is not instanced");
}

void CameraModel::stop()
{
    if(instanceFlag)
    {
        if(interface->isRunning())
        {
            interface->stop();
            Logger::logInfo("Camera interface is stopped");
        } else
            Logger::logWarning("Camera inteface is already stopped");
    } else
        Logger::logError("CameraModel is not instanced");

}

cloudPtrType CameraModel::getLastAcquisition()
{
    Logger::logInfo("Last acquisition requested from CameraModel");
    return trasformedpcd;
}

bool CameraModel::isRunning() {
    if(instanceFlag)
        return interface->isRunning();
    return false;
}

void CameraModel::setDepthImageMode(pcl::io::OpenNI2Grabber::Mode mode)
{
    this->depthImgMode = mode;
}

void CameraModel::setImageMode(pcl::io::OpenNI2Grabber::Mode mode)
{
    this->imgMode = mode;
}


CameraModel::~CameraModel()
{
    if(instanceFlag)
    {
        this->stop();
        instanceFlag=false;
    }
    delete interface;
    Logger::logInfo("CameraModel was deleted");
}
