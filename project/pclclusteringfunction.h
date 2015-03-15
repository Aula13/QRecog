#ifndef PCLCLUSTERINGFUNCTION_H
#define PCLCLUSTERINGFUNCTION_H

#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/file_io.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>

class PCLClusteringFunction
{
public:
    PCLClusteringFunction();

    std::vector<pcl::PointCloud<pcl::PointXYZRGBA>::Ptr> clustering(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud);

    float clusterTolerance;
    int minClusterSize;
    int maxClusterSize;

};

#endif // PCLCLUSTERINGFUNCTION_H
