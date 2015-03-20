#include "pclcorrgroupfunction.h"

PCLCorrGroupFunction::PCLCorrGroupFunction()
{
    //setupDefaultValues();
    //timer = new QTimer(this);
}

void PCLCorrGroupFunction::recognize ()
    {
        resetValues();
        if (!this->model)
        {
            Logger::logInfo("Error model cloud is null.");
            return;
        }
        if (!this->scene)
        {
            Logger::logInfo("Error scene cloud is null.");
            return;
        }
        if (applyTrasformationToModel)
            transformCloud(model);

        if (useCloudResolution)
            setUpResolutionInvariance();

        computeNormals();

        // Extract keypoints
        downSampleModel();
        downSampleScene();

        // Compute Descriptors
        computeDescriptorsForKeypoints(model, modelKeypoints, modelNormals, modelDescriptors);
        computeDescriptorsForKeypoints(scene, sceneKeypoints, sceneNormals, sceneDescriptors);

        // For each scene keypoint descriptor,find nearest neighbor into the model
        // keypoints descriptor cloud and add it to the correspondences vector.
        findCorrespondences();

        //  Clustering
        if (useHough)
            recognizeUsingHough();
        else
            recognizeUsingGeometricConsistency();

        printResults();
}

double PCLCorrGroupFunction::computeCloudResolution (const pcl::PointCloud<PointType>::ConstPtr &cloud)
    {
        double res = 0.0;
        int n_points = 0;
        int nres;
        std::vector<int> indices (2);
        std::vector<float> sqr_distances (2);
        pcl::search::KdTree<PointType> tree;
        tree.setInputCloud (cloud);

        for (size_t i = 0; i < cloud->size (); ++i)
        {
            if (! pcl_isfinite ((*cloud)[i].x))
                continue;
            //Considering the second neighbor since the first is the point itself.
            nres = tree.nearestKSearch (i, 2, indices, sqr_distances);
            if (nres == 2)
            {
                res += sqrt (sqr_distances[1]);
                ++n_points;
            }
        }
        if (n_points != 0)
            res /= n_points;
        return res;
    }

void PCLCorrGroupFunction::transformCloud(cloudPtr &cloud){

    Eigen::Affine3f transform = Eigen::Affine3f::Identity();
    float theta = M_PI/4; // The angle of rotation in radians

    // Define a translation of 2.5 meters on the x axis.
    transform.translation() << 0.0, 0.0, 0.0;

    // The same rotation matrix as before; tetha radians arround Z axis
    transform.rotate (Eigen::AngleAxisf (theta, Eigen::Vector3f::UnitZ()));

    // Print the transformation
    printf ("\nApplying Transform using an Affine3f\n");
    std::cout << transform.matrix() << std::endl;

    pcl::transformPointCloud (*cloud, *cloud, transform);
}

void PCLCorrGroupFunction::loadCloudsFromDefaultFile(){
    this->loadSceneFromFile("~/Qrecog/milk.pcd");
    this->loadModelFromFile("~/Qrecog/milk_cartoon_all_small_clorox.pcd");
}


void PCLCorrGroupFunction::loadModelFromFile(std::string modelFilename){
    if ( pcl::io::loadPCDFile (modelFilename, *(this->model)) < 0)
        std::cout << "Error loading default model cloud." << std::endl;
}

void PCLCorrGroupFunction::loadSceneFromFile(std::string sceneFilename){

    if ( pcl::io::loadPCDFile (sceneFilename, *(this->scene)) < 0)
        std::cout << "Error loading scene model cloud." << std::endl;
}


void PCLCorrGroupFunction::setUpResolutionInvariance(){
    float resolution = static_cast<float> (computeCloudResolution (model));
    if (resolution != 0.0f)
    {
        modelSampleSize          *= resolution;
        sceneSampleSize          *= resolution;
        referenceFrameRadius     *= resolution;
        descriptorsRadius        *= resolution;
        cgSize                   *= resolution;
    }
    Logger::logInfo("Model resolution:       "  + std::to_string(resolution));
    Logger::logInfo("Model sampling size:    "  + std::to_string(modelSampleSize));
    Logger::logInfo("Scene sampling size:    "  + std::to_string(sceneSampleSize));
    Logger::logInfo("LRF support radius:     "  + std::to_string(referenceFrameRadius));
    Logger::logInfo("SHOT descriptor radius: "  + std::to_string(descriptorsRadius));
    Logger::logInfo("Clustering bin size:    "  + std::to_string(cgSize));
}

void PCLCorrGroupFunction::computeNormals(){
    pcl::NormalEstimationOMP<PointType, NormalType> normEst;
    normEst.setKSearch (10);
    normEst.setInputCloud (model);
    normEst.compute (*modelNormals);

    normEst.setInputCloud (scene);
    normEst.compute (*sceneNormals);
}

void PCLCorrGroupFunction::downSampleScene(){
    downSampleCloud(scene, sceneSampleSize, sceneKeypoints);
    Logger::logInfo("TotalScenePoints: "    + std::to_string(scene->size()));
    Logger::logInfo("SceneKeypoints: "      + std::to_string(sceneKeypoints->size()));
}

void PCLCorrGroupFunction::downSampleModel(){
    downSampleCloud(model, modelSampleSize, modelKeypoints);
    Logger::logInfo("TotalModelPoints: "    + std::to_string(model->size()));
    Logger::logInfo("ModelKeypoints: "    + std::to_string(modelKeypoints->size()));
}

void PCLCorrGroupFunction::downSampleCloud(cloudPtr &cloud,  float sampleSize, cloudPtr &keypoints){
    pcl::PointCloud<int> sampledIndices;
    pcl::UniformSampling<PointType> uniform_sampling;
    uniform_sampling.setInputCloud (cloud);
    uniform_sampling.setRadiusSearch (sampleSize);
    uniform_sampling.compute (sampledIndices);

    pcl::copyPointCloud (*cloud, sampledIndices.points, *keypoints);

}

void PCLCorrGroupFunction::computeDescriptorsForKeypoints(cloudPtr &cloud,  cloudPtr &keypoints, normalsPtr &normals, descriptorsPtr &descriptors){
    pcl::SHOTEstimationOMP<PointType, NormalType, DescriptorType> descriptorEst;
    descriptorEst.setRadiusSearch (descriptorsRadius);

    descriptorEst.setInputCloud (keypoints);
    descriptorEst.setInputNormals (normals);
    descriptorEst.setSearchSurface (cloud);
    descriptorEst.compute (*descriptors);

}

void PCLCorrGroupFunction::findCorrespondences(){
    pcl::KdTreeFLANN<DescriptorType> matchSearch;
    matchSearch.setInputCloud (modelDescriptors);

    for (size_t i = 0; i < sceneDescriptors->size (); ++i)
    {
        std::vector<int> neighIndices (1);
        std::vector<float> neighSqrDists (1);
        if (!pcl_isfinite (sceneDescriptors->at (i).descriptor[0])) //skipping NaNs
            continue;
        int foundNeighs = matchSearch.nearestKSearch (sceneDescriptors->at (i), 1, neighIndices, neighSqrDists);
        //  add match only if the squared descriptor distance is less than 0.25 (SHOT descriptor distances are between 0 and 1 by design)
        if(foundNeighs == 1 && neighSqrDists[0] < 0.25f)
        {
            pcl::Correspondence corr (neighIndices[0], static_cast<int> (i), neighSqrDists[0]);
            modelSceneCorrs->push_back (corr);
        }
    }
    Logger::logInfo("Correspondences found: " + std::to_string(modelSceneCorrs->size ()));
}

void PCLCorrGroupFunction::recognizeUsingHough(){
    //
    //  Compute (Keypoints) Reference Frames only for Hough
    //
    pcl::PointCloud<RFType>::Ptr modelRf (new pcl::PointCloud<RFType> ());
    pcl::PointCloud<RFType>::Ptr sceneRf (new pcl::PointCloud<RFType> ());

    pcl::BOARDLocalReferenceFrameEstimation<PointType, NormalType, RFType> rfEst;
    rfEst.setFindHoles (true);
    rfEst.setRadiusSearch (referenceFrameRadius);

    rfEst.setInputCloud (modelKeypoints);
    rfEst.setInputNormals (modelNormals);
    rfEst.setSearchSurface (model);
    rfEst.compute (*modelRf);

    rfEst.setInputCloud (sceneKeypoints);
    rfEst.setInputNormals (sceneNormals);
    rfEst.setSearchSurface (scene);
    rfEst.compute (*sceneRf);

    //  Clustering
    pcl::Hough3DGrouping<PointType, PointType, RFType, RFType> clusterer;
    clusterer.setHoughBinSize (cgSize);
    clusterer.setHoughThreshold (cgThreshold);
    clusterer.setUseInterpolation (true);
    clusterer.setUseDistanceWeight (false);

    clusterer.setInputCloud (modelKeypoints);
    clusterer.setInputRf (modelRf);
    clusterer.setSceneCloud (sceneKeypoints);
    clusterer.setSceneRf (sceneRf);
    clusterer.setModelSceneCorrespondences (modelSceneCorrs);

    //clusterer.cluster (clustered_corrs);
    clusterer.recognize (rototranslations, clusteredCorrs);
}

void PCLCorrGroupFunction::recognizeUsingGeometricConsistency(){
    pcl::GeometricConsistencyGrouping<PointType, PointType> gcClusterer;
    gcClusterer.setGCSize (cgSize);
    gcClusterer.setGCThreshold (cgThreshold);

    gcClusterer.setInputCloud (modelKeypoints);
    gcClusterer.setSceneCloud (sceneKeypoints);
    gcClusterer.setModelSceneCorrespondences (modelSceneCorrs);

    //gc_clusterer.cluster (clusteredCorrs);
    gcClusterer.recognize (rototranslations, clusteredCorrs);
}

void PCLCorrGroupFunction::printResults(){
    std::cout << "Model instances found: " << rototranslations.size () << std::endl;
    for (size_t i = 0; i < rototranslations.size (); ++i)
    {
        Logger::logInfo("\n    Instance " + std::to_string(i + 1) + ":");
        Logger::logInfo("        Correspondences belonging to this instance: " + std::to_string(clusteredCorrs[i].size ()));

        // Print the rotation matrix and translation vector
        Eigen::Matrix3f rotation = rototranslations[i].block<3,3>(0, 0);
        Eigen::Vector3f translation = rototranslations[i].block<3,1>(0, 3);

        Logger::logInfo("\n");
        Logger::logInfo("            | %6.3f %6.3f %6.3f | \n" + std::to_string(rotation (0,0)) + std::to_string(rotation (0,1)) + std::to_string(rotation (0,2)));
        Logger::logInfo("        R = | %6.3f %6.3f %6.3f | \n" + std::to_string(rotation (1,0)) + std::to_string(rotation (1,1)) + std::to_string(rotation (1,2)));
        Logger::logInfo("            | %6.3f %6.3f %6.3f | \n" + std::to_string(rotation (2,0)) + std::to_string(rotation (2,1)) + std::to_string(rotation (2,2)));
        Logger::logInfo("\n");
        Logger::logInfo("        t = < %0.3f, %0.3f, %0.3f >\n" + std::to_string(rotation (0)) + std::to_string(rotation (1)) + std::to_string(rotation (2)));
    }

}

void PCLCorrGroupFunction::resetValues (){
    modelKeypoints     = (cloudPtr)new pcl::PointCloud<PointType>();
    sceneKeypoints     = (cloudPtr)new pcl::PointCloud<PointType> ();
    modelNormals       = (normalsPtr)new pcl::PointCloud<NormalType> ();
    sceneNormals       = (normalsPtr)new pcl::PointCloud<NormalType> ();
    modelDescriptors   = (descriptorsPtr)new pcl::PointCloud<DescriptorType> ();
    sceneDescriptors   = (descriptorsPtr)new pcl::PointCloud<DescriptorType> ();
    modelSceneCorrs    = (pcl::CorrespondencesPtr)new pcl::Correspondences ();
}

void PCLCorrGroupFunction::setUpOffSceneModel()
{
    offSceneModelKeypoints  = (cloudPtr)new pcl::PointCloud<PointType> ();
    offSceneModel           = (cloudPtr)new pcl::PointCloud<PointType> ();
    //  We are translating the model so that it doesn't end in the middle of the scene representation
    pcl::transformPointCloud (*model, *offSceneModel, Eigen::Vector3f (-1,0,0), Eigen::Quaternionf (1, 0, 0, 0));
    pcl::transformPointCloud (*modelKeypoints, *offSceneModelKeypoints, Eigen::Vector3f (-1,0,0), Eigen::Quaternionf (1, 0, 0, 0));

}

cloudPtr PCLCorrGroupFunction::getCorrespondence()
{
    cloudPtr rotated_model (new pcl::PointCloud<PointType> ());
    for (size_t i = 0; i < rototranslations.size (); ++i)
        pcl::transformPointCloud (*model, *rotated_model, rototranslations[i]);

    for (size_t i = 0; i< rotated_model->points.size(); i++) {
        rotated_model->points[i].r = 255;
        rotated_model->points[i].b = 0;
        rotated_model->points[i].g = 0;
    }
    return rotated_model;
}
