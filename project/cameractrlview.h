#ifndef CAMERACTRLVIEW_H
#define CAMERACTRLVIEW_H

#include <QWidget>

namespace Ui {
class CameraCtrlView;
}

class CameraCtrlView : public QWidget
{
    Q_OBJECT

public:
    explicit CameraCtrlView(QWidget *parent = 0);
    ~CameraCtrlView();

private:
    Ui::CameraCtrlView *ui;
};

#endif // CAMERACTRLVIEW_H
