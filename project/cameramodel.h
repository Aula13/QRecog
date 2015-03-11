#ifndef CAMERAMODEL_H
#define CAMERAMODEL_H

#include <pcl/io/openni2_grabber.h>
#include <pcl/io/pcd_io.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/filter.h>

#include "observable.h"

class CameraModel : Observable
{
public:
    static CameraModel* getInstance();

    void registerCallback(boost::function<void (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f);

    void run();

    void stop();

    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr getLastAcquisition();

    bool isRunning();

    ~CameraModel();



private:
    CameraModel();

    void cloud_cb_ (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr &cloud);

    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr trasformedpcd;

    bool connected;
    pcl::Grabber* interface;


    static bool instanceFlag;
    static CameraModel* single;
};

#endif // CAMERAMODEL_H
