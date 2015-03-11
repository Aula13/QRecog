#include "cameramodel.h"

bool CameraModel::instanceFlag=false;
CameraModel* CameraModel::single=NULL;

CameraModel* CameraModel::getInstance()
{
    if(! instanceFlag)
    {
        single = new CameraModel();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}

CameraModel::CameraModel()
{
    interface = new pcl::io::OpenNI2Grabber();
}

void CameraModel::registerCallback(boost::function<void (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f)
{
    if(instanceFlag)
        interface->registerCallback(f);
}

void CameraModel::run()
{
    if(instanceFlag)
        interface->start ();
}

void CameraModel::stop()
{
    if(instanceFlag)
        if(interface->isRunning())
            interface->stop();
}

CameraModel::~CameraModel()
{
    if(instanceFlag)
    {
        this->stop();
        instanceFlag=false;
    }
    delete interface;
}
