#ifndef CAMERAMODEL_H
#define CAMERAMODEL_H

#include <thread>
#include <chrono>

#include <pcl/io/openni2_grabber.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/filter.h>

#include "pcsource.h"
#include "logger.h"
#include "defines.h"

class CameraModel : public PCSource
{
public:
    static CameraModel* getInstance();

    void cloud_cb_ (const cloudType::ConstPtr &cloud);

    void registerCallback(boost::function<void (const cloudType::ConstPtr&)> f);

    void run();

    void stop();

    const cloudPtrType getLastAcquisition();

    bool isRunning();

    void setDepthImageMode(pcl::io::OpenNI2Grabber::Mode mode);
    void setImageMode(pcl::io::OpenNI2Grabber::Mode mode);

    ~CameraModel();


private:
    CameraModel();

    cloudPtrType trasformedpcd;
    bool onUpdate = false;

    bool connected;
    pcl::Grabber* interface;

    pcl::io::OpenNI2Grabber::Mode depthImgMode = pcl::io::OpenNI2Grabber::OpenNI_Default_Mode;
    pcl::io::OpenNI2Grabber::Mode imgMode = pcl::io::OpenNI2Grabber::OpenNI_Default_Mode;

    static bool instanceFlag;
    static CameraModel* single;
};

#endif // CAMERAMODEL_H
