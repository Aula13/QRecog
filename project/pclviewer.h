#ifndef PCLVIEWER_H
#define PCLVIEWER_H

#include <QWidget>

// Point Cloud Library
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <list>

// Visualization Toolkit (VTK)
#include <vtkRenderWindow.h>

#include "observer.h"
#include "pcsource.h"

#include "logger.h"
#include "defines.h"

namespace Ui {
class PCLViewer;
}

class PCLViewer : public QWidget, Observer
{
    Q_OBJECT

public:
    explicit PCLViewer(QWidget *parent = 0);
    ~PCLViewer();

    void setModelReference(PCSource* pcs);

    void update(Observable *obs);

    void disableUpdates();
    void enableUpdates();

    void updateView(std::vector<cloudPtrType> clouds);
    void updateView(cloudPtrType cloud);
    void updateView();
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;

protected:

  cloudPtrType cloud;

private:
    Ui::PCLViewer *ui;

    bool disableUpdate;

    std::list<std::string> existentClouds;

    void addOrUpdateCloud(cloudPtrType cloud, std::string cloud_id);
};

#endif // PCLVIEWER_H
