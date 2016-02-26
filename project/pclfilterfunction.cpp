#include "pclfilterfunction.h"

PCLFilterFunction::PCLFilterFunction()
    : cloud_filtered (new cloudType)
{

}

cloudPtrType PCLFilterFunction::filter(cloudPtrType cloud)
{
    reset();

    vg.setInputCloud (cloud);
    vg.setLeafSize (leafSize, leafSize, leafSize);
    vg.filter (*cloud_filtered);

    return cloud_filtered;
}

void PCLFilterFunction::reset()
{
    cloud_filtered.reset();
}
