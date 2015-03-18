#include "simcameramodel.h"

SimCameraModel::SimCameraModel()
{
}

void SimCameraModel::run()
{
    setChanged();
    notifyObservers();
}

void SimCameraModel::stop()
{
}

pcl::PointCloud<pcl::PointXYZRGBA>::Ptr SimCameraModel::getLastAcquisition()
{
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGBA>), cloud_f (new pcl::PointCloud<pcl::PointXYZRGBA>);
    std::string path = QDir::homePath().toStdString() + "/QRecog/old_scene.pcd";
    pcl::io::loadPCDFile(path, *cloud);
    return cloud;
}

bool SimCameraModel::isRunning()
{
    return false;
}
