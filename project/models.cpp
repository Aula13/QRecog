#include "models.h"

PCSource* Models::pcs;
bool Models::isSimulation = false;
QThread Models::cameraThread;

Models::Models()
{
}

void Models::initSimulation()
{
    pcs = new SimCameraModel();
    isSimulation=true;
}

void Models::initRealCamera()
{
    pcs = CameraModel::getInstance();
    isSimulation=false;
}

void Models::initOpenGEVCamera()
{
    pcs = CameraModelOpenGEV::getInstance();
    isSimulation=false;
}


