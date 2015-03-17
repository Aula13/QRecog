#include "pclcorrgroupfunction.h"

PCLCorrGroupFunction::PCLCorrGroupFunction()
{
}

pcl::PointCloud<pcl::PointXYZRGBA>::Ptr PCLCorrGroupFunction::getCorrespondence(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud)
{
    return cloud;
}

void PCLCorrGroupFunction::setModelCloud(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr point)
{

}
