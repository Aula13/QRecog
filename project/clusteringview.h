#ifndef SEGMENTATIONVIEW_H
#define SEGMENTATIONVIEW_H

#include <QWidget>
#include "logger.h"
#include "defines.h"

#include <QMessageBox>

#include "pclfilterfunction.h"
#include "pclmincutfunction.h"
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

    void on_btnSaveModel_clicked();

private:
    Ui::ClusteringView *ui;

    std::vector<cloudPtrType> computedModels;

    unsigned int actualModelViewer;

    void changePClViewerModel(unsigned int index);

};

#endif // SEGMENTATIONVIEW_H
