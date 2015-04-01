#ifndef MINCUTOPTIONVIEW_H
#define MINCUTOPTIONVIEW_H

#include <QWidget>
#include "defines.h"

namespace Ui {
class MinCutOptionView;
}

class MinCutOptionView : public QWidget
{
    Q_OBJECT

public:
    explicit MinCutOptionView(QWidget *parent = 0);
    ~MinCutOptionView();

    float getx();
    float gety();
    float getz();

    float getSigma();
    float getRadius();
    int getNrNeighbours();
    float getSourceWeight();

    bool isMinCutEnabled();

private:
    Ui::MinCutOptionView *ui;
};

#endif // MINCUTOPTIONVIEW_H
