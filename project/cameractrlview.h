#ifndef CAMERACTRLVIEW_H
#define CAMERACTRLVIEW_H

#include <QWidget>

#include "cameramodel.h"

namespace Ui {
class CameraCtrlView;
}

class CameraCtrlView : public QWidget
{
    Q_OBJECT

public:
    explicit CameraCtrlView(QWidget *parent = 0);
    ~CameraCtrlView();

private slots:
    void on_btnStartCamera_clicked();

    void on_btnStopCamera_clicked();

private:
    Ui::CameraCtrlView *ui;
};

#endif // CAMERACTRLVIEW_H
