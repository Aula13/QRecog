#ifndef AcquisitionView_H
#define AcquisitionView_H

#include <QWidget>
#include <QMessageBox>

#include <string>

#include "models.h"
#include <pcl/io/pcd_io.h>

namespace Ui {
class AcquisitionView;
}

class AcquisitionView : public QWidget
{
    Q_OBJECT

public:
    explicit AcquisitionView(QWidget *parent = 0);

    void viewOnFocus(bool focus);

    ~AcquisitionView();

private slots:
    void on_btnCapture_clicked();

    void on_chkDisableUpdates_stateChanged(int arg1);

private:
    Ui::AcquisitionView *ui;

};

#endif // AcquisitionView_H
