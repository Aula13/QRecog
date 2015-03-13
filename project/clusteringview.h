#ifndef SEGMENTATIONVIEW_H
#define SEGMENTATIONVIEW_H

#include <QWidget>
#include "logger.h"

#include <QMessageBox>

#include "pclfilterfunction.h"

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

private:
    Ui::ClusteringView *ui;
};

#endif // SEGMENTATIONVIEW_H
