#include "pclfilterfunction.h"

PCLFilterFunction::PCLFilterFunction()
{

}

cloudPtrType PCLFilterFunction::filter(cloudPtrType cloud)
{
    pcl::VoxelGrid<PointType> vg;
    cloudPtrType cloud_filtered (new cloudType);
    vg.setInputCloud (cloud);
    vg.setLeafSize (leafSize, leafSize, leafSize);
    vg.filter (*cloud_filtered);

    return cloud_filtered;
}
