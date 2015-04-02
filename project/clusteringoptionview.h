#ifndef CLUSTERINGOPTION_H
#define CLUSTERINGOPTION_H

#include <QWidget>
#include "defines.h"

namespace Ui {
class ClusteringOptionView;
}

class ClusteringOptionView : public QWidget
{
    Q_OBJECT

public:
    explicit ClusteringOptionView(QWidget *parent = 0);

    bool isClusteringEnabled();

    float getClusterTolerance();
    int getMinClusterSize();
    int getMaxClusterSize();

    bool showUsedKeypoints();

    float getModelSample();
    float getDescriptorRadius();

    ~ClusteringOptionView();

private slots:
    void on_chkShowUsedKeypoints_toggled(bool checked);

private:
    Ui::ClusteringOptionView *ui;
};

#endif // CLUSTERINGOPTION_H
