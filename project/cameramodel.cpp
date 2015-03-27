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

void CameraModel::registerCallback(boost::function<void (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f)
{
    if(instanceFlag)
        interface->registerCallback(f);
}

void CameraModel::cloud_cb_ (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr &cloud)
{
    Eigen::Matrix4f TransMat=Eigen::Matrix4f::Identity();

    //Rotazione della point cloud attorno all'asse Z di 180 gradi
    float theta = M_PI; // The angle of rotation in radians
    TransMat(0,0) = cos(theta);
    TransMat(0,1) = -sin(theta);
    TransMat(1,0) = sin(theta);
    TransMat(1,1) = cos(theta);

    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud1(new pcl::PointCloud<pcl::PointXYZRGBA> (*cloud));
    trasformedpcd = cloud1;

    //trasformedpcd = new pcl::PointCloud<pcl::PointXYZRGBA> (*cloud);

    pcl::transformPointCloud(*trasformedpcd,*trasformedpcd,TransMat);

    //Rotazione della point cloud attorno all'asse Y di 180 gradi
    TransMat=Eigen::Matrix4f::Identity();

    theta = M_PI; // The angle of rotation in radians
    TransMat(0,0) = cos(theta);
    TransMat(0,2) = sin(theta);
    TransMat(2,0) = -sin(theta);
    TransMat(2,2) = cos(theta);

    pcl::transformPointCloud(*trasformedpcd,*trasformedpcd,TransMat);

    Logger::logInfo("Update cloud is coming");

    setChanged();
    notifyObservers();
}

void CameraModel::run()
{
    if(instanceFlag)
    {
        interface = new pcl::io::OpenNI2Grabber();
        interface->start ();
        boost::function<void (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f = boost::bind (&CameraModel::cloud_cb_, this, _1);
        interface->registerCallback(f);
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

pcl::PointCloud<pcl::PointXYZRGBA>::Ptr CameraModel::getLastAcquisition()
{
    Logger::logInfo("Last acquisition requested from CameraModel");
    return trasformedpcd;
}

bool CameraModel::isRunning() {
    if(instanceFlag)
        return interface->isRunning();
    return false;
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
