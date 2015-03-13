#ifndef PCLFILTERFUNCTION_H
#define PCLFILTERFUNCTION_H

#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>

class PCLFilterFunction
{
public:
    PCLFilterFunction();

    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr filter(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud);

    float leafSize;

};

#endif // PCLFILTERFUNCTION_H
