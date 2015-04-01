#ifndef SIMCAMERAMODEL_H
#define SIMCAMERAMODEL_H

#include "pcsource.h"
#include <QDir>
#include "defines.h"

class SimCameraModel : public PCSource
{
public:
    SimCameraModel();

    void run();

    void stop();

    cloudPtrType getLastAcquisition();

    bool isRunning();
};

#endif // SIMCAMERAMODEL_H
