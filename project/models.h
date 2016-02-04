#ifndef MODELS_H
#define MODELS_H

#include "pcsource.h"
#include "simcameramodel.h"
#include "cameramodel.h"
#include "cameramodelopengev.h"

class Models
{
public:
    Models();

    static void initSimulation();

    static void initRealCamera();

    static void initOpenGEVCamera();

    static PCSource* pcs;

    static bool isSimulation;

private:

    static QThread cameraThread;

};

#endif // MODELS_H
