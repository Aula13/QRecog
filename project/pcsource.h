#ifndef PCSOURCE_H
#define PCSOURCE_H

#include "observable.h"
#include <pcl/io/pcd_io.h>
#include "defines.h"

class PCSource : public Observable
{
public:
    PCSource();

    virtual void run() = 0;

    virtual void stop() = 0;

    virtual const cloudPtrType getLastAcquisition() = 0;

    virtual bool isRunning() = 0;
};

#endif // PCSOURCE_H
