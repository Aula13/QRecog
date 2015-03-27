#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "logger.h"
#include "models.h"

typedef pcl::io::OpenNI2Grabber onimode;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    onimode::Mode getDepthImageMode();
    onimode::Mode getImageMode();


    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionError_triggered();

    void on_actionWarning_triggered();

    void on_actionInfo_triggered();

    void on_actionDebug_triggered();

    void on_maintab_currentChanged(int index);

    void on_actionUse_simulation_triggered(bool checked);

    void on_actionDepthImgDefault_mode_triggered();

    void on_actionDepthImgSXGA_15Hz_triggered();

    void on_actionDepthImgVGA_30Hz_triggered();

    void on_actionDepthImgVGA_25Hz_triggered();

    void on_actionDepthImgQVGA_25_Hz_triggered();

    void on_actionDepthImgQVGA_30Hz_triggered();

    void on_actionDepthImgQQVGA_60Hz_triggered();

    void on_actionDepthImgQQVGA_30Hz_triggered();

    void on_actionImageSXGA_15Hz_triggered();

    void on_actionImageDefault_mode_triggered();

    void on_actionImageQVGA_60Hz_triggered();

    void on_actionImageQVGA_25Hz_triggered();

    void on_actionImageQVGA_30Hz_triggered();

    void on_actionImageQQVGA_25Hz_triggered();

    void on_actionImageQQVGA_30Hz_triggered();

    void on_actionDepthImgQVGA_60Hz_triggered();

    void on_actionDepthImgQQVGA_25Hz_triggered();

    void on_actionImageQQVGA_60Hz_triggered();

    void on_actionImageVGA_30Hz_triggered();

    void on_actionImageVGA_25Hz_triggered();

private:
    Ui::MainWindow *ui;

    void resetImageModeSelection();

    void resetDepthModeSelection();
};

#endif // MAINWINDOW_H
