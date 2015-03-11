#ifndef CAMERAMODEL_H
#define CAMERAMODEL_H

#include <pcl/io/openni2_grabber.h>
#include <pcl/io/pcd_io.h>

class CameraModel
{
public:
    static CameraModel* getInstance();

    void registerCallback(boost::function<void (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f);

    void run();

    void stop();

    ~CameraModel();



private:
    CameraModel();

    bool connected;
    pcl::Grabber* interface;


    static bool instanceFlag;
    static CameraModel* single;
};

#endif // CAMERAMODEL_H
