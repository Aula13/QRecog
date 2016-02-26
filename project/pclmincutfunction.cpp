#include "pclmincutfunction.h"

PCLMinCutFunction::PCLMinCutFunction()
    : foreground_points(new cloudType),
      result (new cloudType),
      indicesPointer (new pcl::PointIndices)
{
}

cloudPtrType PCLMinCutFunction::getForegroundPointCloud(cloudPtrType cloud)
{
  reset();

  seg.setInputCloud (cloud);

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

  seg.extract (clusters);

  Logger::logInfo("Min cut segmentation - clusters size " + std::to_string(clusters.size()));
  Logger::logInfo("Min cut segmentation - Maximum flow is " + std::to_string(seg.getMaxFlow ()));

#ifdef ENABLE_ONLY_RGB_FUNC
  if(showPreview) //Show a complete cloud with the difference between fg e bg
    return seg.getColoredCloud();
  else { //Extract only the foreground
#endif

    indicesPointer->indices = clusters[1].indices;
    // TODO: trovare un modo per tirare fuori solo i punti in foreground
    extract.setInputCloud(cloud);
    extract.setIndices(indicesPointer);
    extract.filter(*result);

    return result;
#ifdef ENABLE_ONLY_RGB_FUNC
  }
#endif
}

void PCLMinCutFunction::reset()
{
    //foreground_points.reset();
    clusters.clear();
    //result.reset();
    //indicesPointer.reset();
}
