#ifndef CORRESPONDENCEVIEW_H
#define CORRESPONDENCEVIEW_H

#include <QWidget>

#include "observer.h"

#include "logger.h"

#include <QMessageBox>
#include <QElapsedTimer>

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

    void viewOnFocus(bool focus);

    void update(Observable* obs);

    ~CorrespondenceView();

private slots:
    void on_chkDisableUpdate_stateChanged(int arg1);
    void on_btnSetModel_clicked();

    void on_spnModelss_valueChanged(double arg1);

    void on_spnSceness_valueChanged(double arg1);

    void on_spnDescRad_valueChanged(double arg1);

    void on_spnRFRad_valueChanged(double arg1);

    void on_spnCGSize_valueChanged(double arg1);

    void on_spnCGThres_valueChanged(double arg1);

private:
    void launchRecognizer(PCLCorrGroupFunction* cff);
    void visualizeRecognizerOutput(PCLCorrGroupFunction *cff);

    Ui::CorrespondenceView *ui;

    std::vector<pcl::PointCloud<pcl::PointXYZRGBA>::Ptr> computedModels;
    std::vector<pcl::PointCloud<pcl::PointXYZRGBA>::Ptr> searchedModels;

    bool viewHasFocus;

    QElapsedTimer* computationTimer;

    PCLCorrGroupFunction* cff  = new PCLCorrGroupFunction();

    bool correspondenceCloud;
};

#endif // CORRESPONDENCEVIEW_H
