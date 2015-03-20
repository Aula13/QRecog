#ifndef MODELS_H
#define MODELS_H

#include "pcsource.h"
#include "simcameramodel.h"
#include "cameramodel.h"

class Models
{
public:
    Models();

    static void initSimulation();

    static void initRealCamera();

    static PCSource* pcs;

    static bool isSimulation;

};

#endif // MODELS_H
