#include "pclsegmentationfunction.h"

PCLSegmentationFunction::PCLSegmentationFunction()
{
}

cloudPtrType PCLSegmentationFunction::segment(cloudPtrType cloud)
{

    cloudPtrType cloud_f (new cloudType);

    pcl::SACSegmentation<PointType> seg;
    pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
    pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
    cloudPtrType cloud_plane (new cloudType);

    seg.setOptimizeCoefficients (optimazeCoeff);
    seg.setModelType (modelType);
    seg.setMethodType (methodType);
    seg.setMaxIterations (maxIterations);
    seg.setDistanceThreshold (distanceThreashold);

    int nr_points = (int) cloud->points.size ();
    while (cloud->points.size () > 0.3 * nr_points)
    {
        // Segment the largest planar component from the remaining cloud
        seg.setInputCloud (cloud);
        seg.segment (*inliers, *coefficients); //TODO
        if (inliers->indices.size () == 0)
        {
            Logger::logInfo("Could not estimate a planar model for the given dataset.");
            break;
        }

        // Extract the planar inliers from the input cloud
        pcl::ExtractIndices<PointType> extract;
        extract.setInputCloud (cloud);
        extract.setIndices (inliers);
        extract.setNegative (false);

        // Get the points associated with the planar surface
        extract.filter (*cloud_plane);

        // Remove the planar inliers, extract the rest
        extract.setNegative (true);
        extract.filter (*cloud_f);
        *cloud = *cloud_f;
    }

    return cloud;
}
