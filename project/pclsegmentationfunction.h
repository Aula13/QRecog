#ifndef PCLSEGMENTATIONFUNCTION_H
#define PCLSEGMENTATIONFUNCTION_H

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

#include "logger.h"
#include "defines.h"

class PCLSegmentationFunction
{
public:
    PCLSegmentationFunction();

    cloudPtrType segment(cloudPtrType cloud);

    bool optimazeCoeff;
    int modelType;
    int methodType;
    int maxIterations;
    float distanceThreashold;

};

#endif // PCLSEGMENTATIONFUNCTION_H
