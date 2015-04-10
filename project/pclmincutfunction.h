#ifndef PCLMINCUTFUNCTION_H
#define PCLMINCUTFUNCTION_H

#include <iostream>
#include <vector>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/passthrough.h>
#include <pcl/segmentation/min_cut_segmentation.h>
#include <pcl/filters/extract_indices.h>

#include "logger.h"
#include "defines.h"

class PCLMinCutFunction
{
public:
    PCLMinCutFunction();

    cloudPtrType getForegroundPointCloud(cloudPtrType cloud);

    float x;
    float y;
    float z;

    float sigma;
    float radius;
    int numberOfNeighbours;
    float sourceWeight;

    bool showPreview;

};

#endif // PCLMINCUTFUNCTION_H