#ifndef SEGMENTATIONVIEW_H
#define SEGMENTATIONVIEW_H

#include <QWidget>
#include "logger.h"

#include <QMessageBox>

#include "pclfilterfunction.h"
#include "pclsegmentationfunction.h"
#include "pclclusteringfunction.h"

#include <pcl/point_types.h>

namespace Ui {
class ClusteringView;
}

class ClusteringView : public QWidget
{
    Q_OBJECT

public:
    explicit ClusteringView(QWidget *parent = 0);

    ~ClusteringView();

private slots:
    void on_btnSegment_clicked();

    void on_btnPrevModel_clicked();

    void on_btnNextModel_clicked();

private:
    Ui::ClusteringView *ui;

    std::vector<pcl::PointCloud<pcl::PointXYZRGBA>::Ptr> computedModels;

    int actualModelViewer;

    void changePClViewerModel(int index);

};

#endif // SEGMENTATIONVIEW_H
