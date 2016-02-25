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
    cloudPtrType emptyCloud(new cloudType);
    trasformedpcd = emptyCloud;

    //Init matrix for 180° rotation on Z axis
    TransMatZ = Eigen::Matrix4f::Identity();
    float theta = M_PI; // The angle of rotation in radians
    TransMatZ(0,0) = cos(theta);
    TransMatZ(0,1) = -sin(theta);
    TransMatZ(1,0) = sin(theta);
    TransMatZ(1,1) = cos(theta);

    //Init matrix for 180° rotation on X axis
    TransMatY=Eigen::Matrix4f::Identity();

    theta = M_PI; // The angle of rotation in radians
    TransMatY(0,0) = cos(theta);
    TransMatY(0,2) = sin(theta);
    TransMatY(2,0) = -sin(theta);
    TransMatY(2,2) = cos(theta);

    //Configure thread for consumer/view separation
    connect(&updateObserversTimer, SIGNAL(timeout()),
            this, SLOT(sendPeriodicUpdate()),
            Qt::DirectConnection);
    updateObserversTimer.setInterval(33);

    this->moveToThread(&updateReceiverThread);
}

void CameraModel::registerCallback(boost::function<void (const cloudType::ConstPtr&)> f)
{
    if(instanceFlag)
        interface->registerCallback(f);
}

void CameraModel::cloud_cb_ (const cloudType::ConstPtr &cloud)
{
    semaphore.lock();

    cloudPtrType workingCloud(new cloudType);

    //180° rotation around Z axe
    pcl::transformPointCloud(*cloud,*workingCloud,TransMatZ);

    //180° rotation around Y axe
    pcl::transformPointCloud(*workingCloud,*workingCloud,TransMatY);

    Logger::logInfo("CameraModelOpenGEV data received and trasformed: ");
    trasformedpcd = workingCloud;

    semaphore.unlock();
}

void CameraModel::run()
{
    if(instanceFlag)
    {
        interface = new pcl::io::OpenNI2Grabber("", depthImgMode, imgMode);

        boost::function<void (const cloudType::ConstPtr&)> f = boost::bind (&CameraModel::cloud_cb_, this, _1);
        interface->registerCallback(f);

        interface->start ();

        //Receiver for updates
        updateReceiverThread.start();

        //Start update observers
        updateObserversTimer.start();

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
            updateObserversTimer.stop();

            updateReceiverThread.quit();
            updateReceiverThread.wait();

            interface->stop();
            Logger::logInfo("Camera interface is stopped");
        } else
            Logger::logWarning("Camera inteface is already stopped");
    } else
        Logger::logError("CameraModel is not instanced");

}

const cloudPtrType CameraModel::getLastAcquisition()
{
    semaphore.lock();
    Logger::logInfo("Last acquisition requested from CameraModel");
    semaphore.unlock();
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

void CameraModel::sendPeriodicUpdate()
{
    //Logger::logInfo("Observers update: " + QThread::currentThreadId());
    setChanged();
    notifyObservers();
}
