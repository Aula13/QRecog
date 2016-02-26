#ifndef CORRESPONDENCEVIEW_H
#define CORRESPONDENCEVIEW_H

#include <QWidget>

#include "observer.h"

#include "logger.h"
#include "defines.h"

#include <QMessageBox>
#include <QElapsedTimer>

#include "pclfilterfunction.h"
#include "pclsegmentationfunction.h"
#include "pclclusteringfunction.h"
#include "pclcorrgroupfunction.h"
#include "pclmincutfunction.h"

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
    void launchRecognizer();
    void visualizeRecognizerOutput();
    void setupColorForClouds();

    Ui::CorrespondenceView *ui;

    std::vector<cloudPtrType> computedModels;
    std::vector<cloudPtrType> searchedModels;
    std::vector<cloudPtrType> cloudsToShow;

    bool viewHasFocus;

    QElapsedTimer* computationTimer;



    bool correspondenceCloud;

    bool modelAdded;
    bool correspondenceAdded;

    PCLFilterFunction filterf;
    PCLMinCutFunction mincut;
    PCLSegmentationFunction segf;
    PCLCorrGroupFunction cff;
};

#endif // CORRESPONDENCEVIEW_H
