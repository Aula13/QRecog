#ifndef CAMERAMODEL_H
#define CAMERAMODEL_H

#include <pcl/io/openni2_grabber.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/filter.h>

#include "pcsource.h"
#include "logger.h"

class CameraModel : public PCSource
{
public:
    static CameraModel* getInstance();

    void cloud_cb_ (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr &cloud);

    void registerCallback(boost::function<void (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f);

    void run();

    void stop();

    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr getLastAcquisition();

    bool isRunning();

    ~CameraModel();



private:
    CameraModel();

    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr trasformedpcd;

    bool connected;
    pcl::Grabber* interface;


    static bool instanceFlag;
    static CameraModel* single;
};

#endif // CAMERAMODEL_H
