#ifndef SIMCAMERAMODEL_H
#define SIMCAMERAMODEL_H

#include "pcsource.h"
#include <QDir>

class SimCameraModel : public PCSource
{
public:
    SimCameraModel();

    void run();

    void stop();

    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr getLastAcquisition();

    bool isRunning();
};

#endif // SIMCAMERAMODEL_H
