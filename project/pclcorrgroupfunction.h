#ifndef PCLCORRGROUPFUNCTION_H
#define PCLCORRGROUPFUNCTION_H

#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/correspondence.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/shot_omp.h>
#include <pcl/features/board.h>
#include <pcl/keypoints/uniform_sampling.h>
#include <pcl/recognition/cg/hough_3d.h>
#include <pcl/recognition/cg/geometric_consistency.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/kdtree/impl/kdtree_flann.hpp>
#include <pcl/common/transforms.h>
#include <pcl/console/parse.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

class PCLCorrGroupFunction
{
public:
    PCLCorrGroupFunction();

    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr getCorrespondence(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud);

    float model_ss;
    float scene_ss;
    float descr_rad;
    float rf_rad;
    float cg_size;
    float cg_threshold;

    bool applyTrasformationToModel;
    bool showUsedKeypoints;
    bool showUsedCorrespondence;
};

#endif // PCLCORRGROUPFUNCTION_H
