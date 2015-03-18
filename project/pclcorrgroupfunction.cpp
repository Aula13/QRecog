#include "pclcorrgroupfunction.h"

PCLCorrGroupFunction::PCLCorrGroupFunction()
{
    //setupDefaultValues();
}

void PCLCorrGroupFunction::recognize ()
    {
        resetValues();
        if (!this->model)
        {
            std::cout << "Error model cloud is null." << std::endl << "returning." << std::endl;
            return;
        }
        if (!this->scene)
        {
            std::cout << "Error scene cloud is null." << std::endl << "returning" << std::endl;
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
    /*  METHOD #2: Using a Affine3f
     This method is easier and less error prone
     */
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

//void PCLCorrGroupFunction::loadClouds{
//    this->loadSceneFromFile();
//    this->loadSceneFromFile();
//}

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

    std::cout << "Model resolution:       " << resolution           << std::endl;
    std::cout << "Model sampling size:    " << modelSampleSize      << std::endl;
    std::cout << "Scene sampling size:    " << sceneSampleSize      << std::endl;
    std::cout << "LRF support radius:     " << referenceFrameRadius << std::endl;
    std::cout << "SHOT descriptor radius: " << descriptorsRadius    << std::endl;
    std::cout << "Clustering bin size:    " << cgSize               << std::endl << std::endl;
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
    std::cout << "TotalScenePoints: "   << scene->size();
    std::cout << "SceneKeypoints: "     << sceneKeypoints->size();
}

void PCLCorrGroupFunction::downSampleModel(){
    downSampleCloud(model, modelSampleSize, modelKeypoints);
    std::cout << "TotalModelPoints: "   << model->size();
    std::cout << "ModelKeypoints: "     << modelKeypoints->size();
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
        {
            continue;
        }
        int foundNeighs = matchSearch.nearestKSearch (sceneDescriptors->at (i), 1, neighIndices, neighSqrDists);
        //  add match only if the squared descriptor distance is less than 0.25 (SHOT descriptor distances are between 0 and 1 by design)
        if(foundNeighs == 1 && neighSqrDists[0] < 0.25f)
        {
            pcl::Correspondence corr (neighIndices[0], static_cast<int> (i), neighSqrDists[0]);
            modelSceneCorrs->push_back (corr);
        }
    }
    std::cout << "Correspondences found: " << modelSceneCorrs->size () << std::endl;
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
        std::cout << "\n    Instance " << i + 1 << ":" << std::endl;
        std::cout << "        Correspondences belonging to this instance: " << clusteredCorrs[i].size () << std::endl;

        // Print the rotation matrix and translation vector
        Eigen::Matrix3f rotation = rototranslations[i].block<3,3>(0, 0);
        Eigen::Vector3f translation = rototranslations[i].block<3,1>(0, 3);

        printf ("\n");
        printf ("            | %6.3f %6.3f %6.3f | \n", rotation (0,0), rotation (0,1), rotation (0,2));
        printf ("        R = | %6.3f %6.3f %6.3f | \n", rotation (1,0), rotation (1,1), rotation (1,2));
        printf ("            | %6.3f %6.3f %6.3f | \n", rotation (2,0), rotation (2,1), rotation (2,2));
        printf ("\n");
        printf ("        t = < %0.3f, %0.3f, %0.3f >\n", translation (0), translation (1), translation (2));
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


//void PCLCorrGroupFunction::setupDefaultValues(){
//    // put files in a qrecog folder in your home directory
//    modelFileName = "~/Qrecog/milk.pcd";
//    sceneFileName = "~/Qrecog/milk_cartoon_all_small_clorox.pcd";
//    //Algorithm params
//    useCloudResolution = false;
//    useHough = true ;
//    applyTrasformationToModel = false;
//    modelSampleSize = 0.01f;
//    sceneSampleSize = 0.03f;
//    descriptorsRadius = 0.02f;
//    referenceFrameRadius = 0.015f;
//    cgSize = 0.01f;
//    cgThreshold = 5.0f;
//}
