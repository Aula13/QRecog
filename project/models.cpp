#include "models.h"

PCSource* Models::pcs;
bool Models::isSimulation = false;

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


