#ifndef CAMERAMODELOPENGEV_H
#define CAMERAMODELOPENGEV_H

#include <thread>
#include <chrono>
#include <QMutex>

#include <Application/gvapplication.h>
#include <Application/partnerdevice.h>
#include <ApplicationStreamDataObserver/depthcolorstreamdataobserver.h>

#include <pcl/point_cloud.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/filter.h>

#include "pcsource.h"
#include "logger.h"
#include "defines.h"

class CameraModelOpenGEV : public QObject, public PCSource
{
    Q_OBJECT
public:
    static CameraModelOpenGEV* getInstance();

    //void cloud_cb_ (const cloudType::ConstPtr &cloud);

    void run();

    void stop();

    cloudPtrType getLastAcquisition();

    bool isRunning();

    ~CameraModelOpenGEV();

public slots:
    void update(const pcl::PointCloud<pcl::PointXYZRGBA>::Ptr &cloud);

    void sendPeriodicUpdate();

private:
    CameraModelOpenGEV();


    cloudPtrType workingCloud;
    cloudPtrType trasformedpcd;

    bool onUpdate = false;

    QMutex semaphore;

    QTimer updateObserversTimer;
    QThread updateObserversManager;

    QThread updateReceiverThread;

    /*Trasformation*/
    Eigen::Matrix4f TransMatZ, TransMatY;

    bool connected;

    GVApplication *app;
    PartnerDevice device;
    DepthColorStreamDataObserver *observer;

    static bool instanceFlag;
    static CameraModelOpenGEV* single;
};

#endif // CAMERAMODELOPENGEV_H
