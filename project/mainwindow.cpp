#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->acquisition->viewOnFocus(true);
    ui->recognition->viewOnFocus(false);

    ui->actionUse_simulation->setChecked(Models::isSimulation);
}

pcl::io::OpenNI2Grabber::Mode MainWindow::getDepthImageMode()
{
    if(ui->actionDepthImgDefault_mode->isChecked())
        return onimode::OpenNI_Default_Mode;
    if(ui->actionDepthImgSXGA_15Hz->isChecked())
        return onimode::OpenNI_SXGA_15Hz;
    if(ui->actionDepthImgVGA_25Hz->isChecked())
        return onimode::OpenNI_VGA_25Hz;
    if(ui->actionDepthImgVGA_30Hz->isChecked())
        return onimode::OpenNI_VGA_30Hz;
    if(ui->actionDepthImgQVGA_25_Hz->isChecked())
        return onimode::OpenNI_QVGA_25Hz;
    if(ui->actionDepthImgQVGA_30Hz->isChecked())
        return onimode::OpenNI_QVGA_30Hz;
    if(ui->actionDepthImgQVGA_60Hz->isChecked())
        return onimode::OpenNI_QVGA_60Hz;
    if(ui->actionDepthImgQQVGA_25Hz->isChecked())
        return onimode::OpenNI_QQVGA_25Hz;
    if(ui->actionDepthImgQQVGA_30Hz->isChecked())
        return onimode::OpenNI_QQVGA_30Hz;
    if(ui->actionDepthImgQQVGA_60Hz->isChecked())
        return onimode::OpenNI_QQVGA_60Hz;
}

pcl::io::OpenNI2Grabber::Mode MainWindow::getImageMode()
{
    if(ui->actionImageDefault_mode->isChecked())
        return onimode::OpenNI_Default_Mode;
    if(ui->actionImageSXGA_15Hz->isChecked())
        return onimode::OpenNI_SXGA_15Hz;
    if(ui->actionImageVGA_25Hz->isChecked())
        return onimode::OpenNI_VGA_25Hz;
    if(ui->actionImageVGA_30Hz->isChecked())
        return onimode::OpenNI_VGA_30Hz;
    if(ui->actionImageQVGA_25Hz->isChecked())
        return onimode::OpenNI_QVGA_25Hz;
    if(ui->actionImageQVGA_30Hz->isChecked())
        return onimode::OpenNI_QVGA_30Hz;
    if(ui->actionImageQVGA_60Hz->isChecked())
        return onimode::OpenNI_QVGA_60Hz;
    if(ui->actionImageQQVGA_25Hz->isChecked())
        return onimode::OpenNI_QQVGA_25Hz;
    if(ui->actionImageQQVGA_30Hz->isChecked())
        return onimode::OpenNI_QQVGA_30Hz;
    if(ui->actionImageQQVGA_60Hz->isChecked())
        return onimode::OpenNI_QQVGA_60Hz;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionError_triggered()
{
    Logger::configLoggerLevel(ERROR);
}

void MainWindow::on_actionWarning_triggered()
{
    Logger::configLoggerLevel(WARNING);
}

void MainWindow::on_actionInfo_triggered()
{
    Logger::configLoggerLevel(INFO);
}

void MainWindow::on_actionDebug_triggered()
{
    Logger::configLoggerLevel(DEBUG);
}

void MainWindow::on_maintab_currentChanged(int index)
{
    switch (index) {
    case 0:
        ui->acquisition->viewOnFocus(true);
        ui->recognition->viewOnFocus(false);
        break;
    case 1:
        ui->acquisition->viewOnFocus(false);
        ui->recognition->viewOnFocus(false);
        break;
    case 2:
        ui->acquisition->viewOnFocus(false);
        ui->recognition->viewOnFocus(true);
        break;
    default:
        break;
    }
}

void MainWindow::on_actionUse_simulation_triggered(bool checked)
{
    if(checked)
        Models::initSimulation();
    if(!checked)
        Models::initRealCamera();
}

void MainWindow::on_actionDepthImgDefault_mode_triggered()
{
    resetDepthModeSelection();
    ui->actionDepthImgDefault_mode->setChecked(true);
}

void MainWindow::on_actionDepthImgSXGA_15Hz_triggered()
{
    resetDepthModeSelection();
    ui->actionDepthImgSXGA_15Hz->setChecked(true);
}

void MainWindow::on_actionDepthImgVGA_30Hz_triggered()
{
    resetDepthModeSelection();
    ui->actionDepthImgVGA_30Hz->setChecked(true);
}

void MainWindow::on_actionDepthImgVGA_25Hz_triggered()
{
    resetDepthModeSelection();
    ui->actionDepthImgVGA_25Hz->setChecked(true);
}

void MainWindow::on_actionDepthImgQVGA_25_Hz_triggered()
{
    resetDepthModeSelection();
    ui->actionDepthImgQVGA_25_Hz->setChecked(true);
}

void MainWindow::on_actionDepthImgQVGA_30Hz_triggered()
{
    resetDepthModeSelection();
    ui->actionDepthImgQVGA_30Hz->setChecked(true);
}

void MainWindow::on_actionDepthImgQVGA_60Hz_triggered()
{
    resetDepthModeSelection();
    ui->actionDepthImgQVGA_60Hz->setChecked(true);
}

void MainWindow::on_actionDepthImgQQVGA_25Hz_triggered()
{
    resetDepthModeSelection();
    ui->actionDepthImgQQVGA_25Hz->setChecked(true);
}

void MainWindow::on_actionDepthImgQQVGA_30Hz_triggered()
{
    resetDepthModeSelection();
    ui->actionDepthImgQQVGA_30Hz->setChecked(true);
}

void MainWindow::on_actionDepthImgQQVGA_60Hz_triggered()
{
    resetDepthModeSelection();
    ui->actionDepthImgQQVGA_60Hz->setChecked(true);
}


void MainWindow::on_actionImageDefault_mode_triggered()
{
    resetImageModeSelection();
    ui->actionImageDefault_mode->setChecked(true);
}

void MainWindow::on_actionImageSXGA_15Hz_triggered()
{
    resetImageModeSelection();
    ui->actionImageSXGA_15Hz->setChecked(true);
}

void MainWindow::on_actionImageVGA_30Hz_triggered()
{
    resetImageModeSelection();
    ui->actionImageVGA_30Hz->setChecked(true);
}

void MainWindow::on_actionImageVGA_25Hz_triggered()
{
    resetImageModeSelection();
    ui->actionImageVGA_25Hz->setChecked(true);
}

void MainWindow::on_actionImageQVGA_25Hz_triggered()
{
    resetImageModeSelection();
    ui->actionImageQVGA_25Hz->setChecked(true);
}

void MainWindow::on_actionImageQVGA_30Hz_triggered()
{
    resetImageModeSelection();
    ui->actionImageQVGA_30Hz->setChecked(true);
}

void MainWindow::on_actionImageQVGA_60Hz_triggered()
{
    resetImageModeSelection();
    ui->actionImageQVGA_60Hz->setChecked(true);
}

void MainWindow::on_actionImageQQVGA_25Hz_triggered()
{
    resetImageModeSelection();
    ui->actionImageQQVGA_25Hz->setChecked(true);
}

void MainWindow::on_actionImageQQVGA_30Hz_triggered()
{
    resetImageModeSelection();
    ui->actionImageQQVGA_30Hz->setChecked(true);
}

void MainWindow::on_actionImageQQVGA_60Hz_triggered()
{
    resetImageModeSelection();
    ui->actionImageQQVGA_60Hz->setChecked(true);
}

void MainWindow::resetDepthModeSelection()
{
    ui->actionDepthImgDefault_mode->setChecked(false);
    ui->actionDepthImgSXGA_15Hz->setChecked(false);
    ui->actionDepthImgVGA_25Hz->setChecked(false);
    ui->actionDepthImgVGA_30Hz->setChecked(false);
    ui->actionDepthImgQVGA_25_Hz->setChecked(false);
    ui->actionDepthImgQVGA_30Hz->setChecked(false);
    ui->actionDepthImgQVGA_60Hz->setChecked(false);
    ui->actionDepthImgQQVGA_25Hz->setChecked(false);
    ui->actionDepthImgQQVGA_30Hz->setChecked(false);
    ui->actionDepthImgQQVGA_60Hz->setChecked(false);
}

void MainWindow::resetImageModeSelection()
{
    ui->actionImageDefault_mode->setChecked(false);
    ui->actionImageSXGA_15Hz->setChecked(false);
    ui->actionImageVGA_25Hz->setChecked(false);
    ui->actionImageVGA_30Hz->setChecked(false);
    ui->actionImageQVGA_25Hz->setChecked(false);
    ui->actionImageQVGA_30Hz->setChecked(false);
    ui->actionImageQVGA_60Hz->setChecked(false);
    ui->actionImageQQVGA_25Hz->setChecked(false);
    ui->actionImageQQVGA_30Hz->setChecked(false);
    ui->actionImageQQVGA_60Hz->setChecked(false);
}
