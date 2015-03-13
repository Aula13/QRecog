#include "pclfilterfunction.h"

PCLFilterFunction::PCLFilterFunction()
{

}

pcl::PointCloud<pcl::PointXYZRGBA>::Ptr PCLFilterFunction::filter(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud)
{
    pcl::VoxelGrid<pcl::PointXYZRGBA> vg;
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZRGBA>);
    vg.setInputCloud (cloud);
    vg.setLeafSize (leafSize, leafSize, leafSize);
    vg.filter (*cloud_filtered);

    return cloud_filtered;
}
