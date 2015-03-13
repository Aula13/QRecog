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
    ~AcquisitionView();

private slots:
    void on_btnCapture_clicked();

private:
    Ui::AcquisitionView *ui;
};

#endif // AcquisitionView_H
