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

    ~ClusteringOptionView();

private:
    Ui::ClusteringOptionView *ui;
};

#endif // CLUSTERINGOPTION_H
