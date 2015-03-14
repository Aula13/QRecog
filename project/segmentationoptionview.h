#ifndef SEGMENTATIONOPTIONVIEW_H
#define SEGMENTATIONOPTIONVIEW_H

#include <QWidget>

namespace Ui {
class SegmentationOptionView;
}

class SegmentationOptionView : public QWidget
{
    Q_OBJECT

public:
    explicit SegmentationOptionView(QWidget *parent = 0);

    bool getOptimizeCoeff();
    int getModelType();
    int getMethodType();
    int getMaxIterations();
    float getDistanceThreshold();

    ~SegmentationOptionView();

private:
    Ui::SegmentationOptionView *ui;
};

#endif // SEGMENTATIONOPTIONVIEW_H
