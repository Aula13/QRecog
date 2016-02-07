#include "cameramodelopengev.h"

bool CameraModelOpenGEV::instanceFlag=false;
CameraModelOpenGEV* CameraModelOpenGEV::single=NULL;

CameraModelOpenGEV* CameraModelOpenGEV::getInstance()
{
    if(! instanceFlag)
    {
        single = new CameraModelOpenGEV();
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

CameraModelOpenGEV::CameraModelOpenGEV()
{
    app = new GVApplication();

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
            this, SLOT(sendPeriodicUpdate()));
    updateObserversTimer.setInterval(33);

    this->moveToThread(&updateReceiverThread);
}

void CameraModelOpenGEV::run()
{
    if(instanceFlag)
    {
        if(connected) {
            Logger::logWarning("CameraModelOpenGEV already connected");
            return;
        }

        if(app->discoverDevices()>0) {
            device = *(app->getDiscoveredDevices().at(0));
            device.openControlChannel(5001);
            if(device.getStreamingChannelNumber()>0) {
                if(device.openStreamChannel(2)==GEV_STATUS_SUCCESS) {
                    device.setStreamChannelPacketLength(2,65000);
                    device.setStreamChannelDelay(2,10000);
                    StreamDataReceiver *channel = device.getStreamChannel(2);
                    observer = new DepthColorStreamDataObserver(*channel,
                                                                device.getHorizontalFieldOfView(),
                                                                device.getVerticalFieldOfView());
                    observer->moveToThread(&updateReceiverThread);
                    connect(observer, SIGNAL(pointCloudUpdate()),
                            this, SLOT(update()));

                    //Receiver for updates
                    updateReceiverThread.start();

                    //Start update observers
                    updateObserversTimer.start();

                    connected=true;
                    return;
                } else
                    Logger::logError("CameraModelOpenGEV can't open stream channel");
            } else
                Logger::logError("CameraModelOpenGEV no stream channels");
        } else
            Logger::logError("CameraModelOpenGEV no device discovered");
    } else
        Logger::logError("CameraModelOpenGEV is not instanced");
    connected=false;
}

void CameraModelOpenGEV::stop()
{
    if(instanceFlag)
    {
        if(connected)
        {
            //Stop update observers
            updateObserversTimer.stop();

            device.closeStreamChannel(2);
            device.closeControlChannel();

            disconnect(observer, SIGNAL(pointCloudUpdate()),
                       this, SLOT(update()));

            updateReceiverThread.quit();
            updateReceiverThread.wait();

            delete observer;
            app->clearDevices();
            connected=false;
            Logger::logInfo("Camera interface is stopped");
        } else
            Logger::logWarning("Camera inteface is already stopped");
    } else
        Logger::logError("CameraModel is not instanced");

}

const cloudPtrType CameraModelOpenGEV::getLastAcquisition()
{
    Logger::logInfo("Last acquisition requested from CameraModel");
    return trasformedpcd;
}

bool CameraModelOpenGEV::isRunning() {
    if(instanceFlag)
        return connected;
    return false;
}

CameraModelOpenGEV::~CameraModelOpenGEV()
{
    if(instanceFlag)
    {
        this->stop();
        instanceFlag=false;
    }

    Logger::logInfo("CameraModelOpenGEV was deleted");
}

void CameraModelOpenGEV::update()
{
    if(!semaphore.tryLock())
        return;

    cloudPtrType workingCloud(new cloudType);

    //180° rotation around Z axe
    pcl::transformPointCloud(*(observer->ptrCloud),*workingCloud,TransMatZ);

    //180° rotation around Y axe
    pcl::transformPointCloud(*workingCloud,*workingCloud,TransMatY);

    Logger::logInfo("CameraModelOpenGEV data received and trasformed: ");
    trasformedpcd = workingCloud;

    /*
    setChanged();
    notifyObservers();
    */

    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    semaphore.unlock();
}

void CameraModelOpenGEV::sendPeriodicUpdate()
{
    Logger::logInfo("Observers update: " + QThread::currentThreadId());
    setChanged();
    notifyObservers();
}
