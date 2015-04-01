#include "pclmincutfunction.h"

PCLMinCutFunction::PCLMinCutFunction()
{
}

cloudPtrType PCLMinCutFunction::getForegroundPointCloud(cloudPtrType cloud)
{
  pcl::MinCutSegmentation<PointType> seg;
  seg.setInputCloud (cloud);

  cloudPtrType foreground_points(new cloudType);
  PointType point;
  point.x = x;
  point.y = y;
  point.z = z;
  foreground_points->points.push_back(point);
  seg.setForegroundPoints (foreground_points);

  seg.setSigma (sigma);
  seg.setRadius (radius);
  seg.setNumberOfNeighbours (numberOfNeighbours);
  seg.setSourceWeight (sourceWeight);

  std::vector <pcl::PointIndices> clusters;
  seg.extract (clusters);

  Logger::logInfo("Min cut segmentation - Maximum flow is " + std::to_string(seg.getMaxFlow ()));

  if(showPreview)
    return seg.getColoredCloud();
  else {
    cloudPtrType result (new cloudType);
    // TODO: trovare un modo per tirare fuori solo i punti in foreground
    return cloud;
  }
}
