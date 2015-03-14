#include "pclsegmentationfunction.h"

PCLSegmentationFunction::PCLSegmentationFunction()
{
}

pcl::PointCloud<pcl::PointXYZRGBA>::Ptr PCLSegmentationFunction::segment(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud)
{

    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud_f (new pcl::PointCloud<pcl::PointXYZRGBA>);

    pcl::SACSegmentation<pcl::PointXYZRGBA> seg;
    pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
    pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud_plane (new pcl::PointCloud<pcl::PointXYZRGBA> ());

    seg.setOptimizeCoefficients (optimazeCoeff);
    seg.setModelType (modelType);
    seg.setMethodType (methodType);
    seg.setMaxIterations (maxIterations);
    seg.setDistanceThreshold (distanceThreashold);

    int i=0, nr_points = (int) cloud->points.size ();
    while (cloud->points.size () > 0.3 * nr_points)
    {
        // Segment the largest planar component from the remaining cloud
        seg.setInputCloud (cloud);
        seg.segment (*inliers, *coefficients); //TODO
        if (inliers->indices.size () == 0)
        {
            std::cout << "Could not estimate a planar model for the given dataset." << std::endl;
            break;
        }

        // Extract the planar inliers from the input cloud
        pcl::ExtractIndices<pcl::PointXYZRGBA> extract;
        extract.setInputCloud (cloud);
        extract.setIndices (inliers);
        extract.setNegative (false);

        // Get the points associated with the planar surface
        extract.filter (*cloud_plane);
        std::cout << "PointCloud representing the planar component: " << cloud_plane->points.size () << " data points." << std::endl;

        // Remove the planar inliers, extract the rest
        extract.setNegative (true);
        extract.filter (*cloud_f);
        *cloud = *cloud_f;
    }

    return cloud;
}
