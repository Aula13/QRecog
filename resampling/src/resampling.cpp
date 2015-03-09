#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/surface/mls.h>
#include <pcl/filters/filter.h>

int
main (int argc, char** argv)
{
  typedef pcl::PointCloud<pcl::PointXYZRGB> CloudType;
  // Load input file into a PointCloud<T> with an appropriate type
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB> ());
  // Load bun0.pcd -- should be available with the PCL archive in test
  pcl::io::loadPCDFile ("../data/old_scene.pcd", *cloud);


  cloud->is_dense = false;
  CloudType::PointType p_nan;
  p_nan.x = std::numeric_limits<float>::quiet_NaN();
  p_nan.y = std::numeric_limits<float>::quiet_NaN();
  p_nan.z = std::numeric_limits<float>::quiet_NaN();
  cloud->push_back(p_nan);

  CloudType::PointType p_valid;
  p_valid.x = 1.0f;
  cloud->push_back(p_valid);


  std::cout << "size: " << cloud->points.size () << std::endl;

  std::vector<int> indices;
  pcl::removeNaNFromPointCloud(*cloud, *cloud, indices);
  std::cout << "size: " << cloud->points.size () << std::endl;




  // Create a KD-Tree
  pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZRGB>);

  // Output has the PointNormal type in order to store the normals calculated by MLS
  pcl::PointCloud<pcl::PointNormal> mls_points;

  // Init object (second point type is for the normals, even if unused)
  pcl::MovingLeastSquares<pcl::PointXYZRGB, pcl::PointNormal> mls;

  mls.setComputeNormals (true);

  // Set parameters
  mls.setInputCloud (cloud);
  mls.setPolynomialFit (true);
  mls.setSearchMethod (tree);
  mls.setSearchRadius (0.03);

  // Reconstruct
  mls.process (mls_points);

  // Save output
  pcl::io::savePCDFile ("../data/old_scene_smoothed.pcd", mls_points);
}
