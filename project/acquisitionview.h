#ifndef AcquisitionView_H
#define AcquisitionView_H

#include <QWidget>

#include "models.h"

namespace Ui {
class AcquisitionView;
}

class AcquisitionView : public QWidget
{
    Q_OBJECT

public:
    explicit AcquisitionView(QWidget *parent = 0);
    ~AcquisitionView();

private:
    Ui::AcquisitionView *ui;
};

#endif // AcquisitionView_H
