#ifndef CORRESPONDENCEVIEW_H
#define CORRESPONDENCEVIEW_H

#include <QWidget>

#include "observer.h"

#include "logger.h"

#include <QMessageBox>

#include "pclfilterfunction.h"
#include "pclsegmentationfunction.h"
#include "pclclusteringfunction.h"
#include "pclcorrgroupfunction.h"

#include <pcl/point_types.h>

namespace Ui {
class CorrespondenceView;
}

class CorrespondenceView : public QWidget, Observer
{
    Q_OBJECT

public:
    explicit CorrespondenceView(QWidget *parent = 0);

    void update(Observable* obs);

    ~CorrespondenceView();

private slots:
    void on_chkDisableUpdate_stateChanged(int arg1);
    void on_btnSetModel_clicked();

private:
    void launchRecognizer();
    void visualizeRecognizerOutput();

    Ui::CorrespondenceView *ui;
    PCLCorrGroupFunction* cff;

    std::vector<pcl::PointCloud<pcl::PointXYZRGBA>::Ptr> computedModels;
    std::vector<pcl::PointCloud<pcl::PointXYZRGBA>::Ptr> searchedModels;
};

#endif // CORRESPONDENCEVIEW_H
