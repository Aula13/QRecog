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
    ~SegmentationOptionView();

private:
    Ui::SegmentationOptionView *ui;
};

#endif // SEGMENTATIONOPTIONVIEW_H
