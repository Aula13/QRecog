#ifndef PCLVIEWER_H
#define PCLVIEWER_H

#include <QWidget>

// Point Cloud Library
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>

// Visualization Toolkit (VTK)
#include <vtkRenderWindow.h>

namespace Ui {
class PCLViewer;
}

class PCLViewer : public QWidget
{
    Q_OBJECT

public:
    explicit PCLViewer(QWidget *parent = 0);
    ~PCLViewer();

protected:
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
  pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud;

private:
    Ui::PCLViewer *ui;
};

#endif // PCLVIEWER_H