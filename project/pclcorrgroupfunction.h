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
#include "logger.h"


typedef pcl::PointXYZRGBA PointType;
typedef pcl::Normal NormalType;
typedef pcl::ReferenceFrame RFType;
typedef pcl::SHOT352 DescriptorType;
typedef boost::signals2::signal<void ()>  signal_t;
typedef pcl::PointCloud<PointType>::Ptr cloudPtr;
typedef pcl::PointCloud<NormalType>::Ptr normalsPtr;
typedef pcl::PointCloud<DescriptorType>::Ptr descriptorsPtr;

class PCLCorrGroupFunction
{
public:
    PCLCorrGroupFunction();

    cloudPtr getCorrespondence(cloudPtr cloud);
    void setupDefaultValues();
    void recognize (); //TODO REMOVE THIS
    // SETTERS LI RIMUOVIAMO E TENIAMO TUTTE LE VARIABILI PUBBLICHE
    void setModelCloud(cloudPtr &cloud);
    void setSceneCloud(cloudPtr &cloud);
    void setModelFilename(std::string modelFileName);
    void setSceneFilename(std::string sceneFileName);
    void setSceneSampleSize(float sceneSampleSize);
    void setModelSampleSize(float modelSampleSize);
    void setDescriptorsRadius(float descriptorsRadius);
    void setCGSize(float cgSize);
    void setReferenceFrameRadius(float referenceFrameRadius);
    void setCgThreshold(float cgThreshold);
    void setUseHough(bool useHough);
    void setShowUsedKeypoints(bool showUsedKeypoints);
    void setApplyTrasformationToModel(bool applyTrasformationToModel);
    void setShowUsedCorrespondence(bool showUsedCorrespondence);
    void setUseCloudResolution(bool useCloudResolution);
    void loadCloudsFromDefaultFile();
    void loadSceneFromFile(std::string sceneFilename);
    void loadModelFromFile(std::string modelFilename);

    //Variables
    std::string modelFileName;
    std::string sceneFileName;
    cloudPtr model;
    cloudPtr scene;
    float modelSampleSize;
    float sceneSampleSize;
    float descriptorsRadius;
    float referenceFrameRadius;
    float cgSize;
    float cgThreshold;
    bool useHough;
    bool applyTrasformationToModel;
    bool showUsedKeypoints;
    bool showUsedCorrespondence;
    bool useCloudResolution;
    cloudPtr        modelKeypoints;
    cloudPtr        sceneKeypoints;
    normalsPtr      modelNormals;
    normalsPtr      sceneNormals;
    descriptorsPtr  modelDescriptors;
    descriptorsPtr  sceneDescriptors;
    pcl::CorrespondencesPtr modelSceneCorrs;
    std::vector<Eigen::Matrix4f, Eigen::aligned_allocator<Eigen::Matrix4f> > rototranslations;
    std::vector<pcl::Correspondences> clusteredCorrs;

private:
    //Functions
    double computeCloudResolution (const pcl::PointCloud<PointType>::ConstPtr &cloud);
    void transformCloud (pcl::PointCloud<PointType>::Ptr &cloud);
    void setUpResolutionInvariance();
    void computeNormals();
    void downSampleScene();
    void downSampleModel();
    void downSampleCloud(cloudPtr &cloud,  float sampleSize, cloudPtr &keypoints);
    void computeDescriptorsForKeypoints(cloudPtr &cloud,  cloudPtr &keypoints, normalsPtr &normals, descriptorsPtr &descriptors);
    void findCorrespondences();
    void recognizeUsingHough();
    void recognizeUsingGeometricConsistency();
    void printResults();
    void resetValues ();


};

#endif // PCLCORRGROUPFUNCTION_H
