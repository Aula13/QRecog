#ifndef PCLVIEWER_H
#define PCLVIEWER_H

#include <QWidget>

// Point Cloud Library
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>

// Visualization Toolkit (VTK)
#include <vtkRenderWindow.h>

#include "observer.h"
#include "cameramodel.h"

#include "logger.h"

namespace Ui {
class PCLViewer;
}

class PCLViewer : public QWidget, Observer
{
    Q_OBJECT

public:
    explicit PCLViewer(QWidget *parent = 0);
    ~PCLViewer();

    void update(Observable *obs);

protected:
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
  pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud;

private:
    Ui::PCLViewer *ui;
};

#endif // PCLVIEWER_H
