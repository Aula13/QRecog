#ifndef PCLFILTERFUNCTION_H
#define PCLFILTERFUNCTION_H

#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>

#include "defines.h"

class PCLFilterFunction
{
public:
    PCLFilterFunction();

    cloudPtrType filter(cloudPtrType cloud);

    float leafSize;

    void reset();

private:
    pcl::VoxelGrid<PointType> vg;
    cloudPtrType cloud_filtered;


};

#endif // PCLFILTERFUNCTION_H
