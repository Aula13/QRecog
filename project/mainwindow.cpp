#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "logger.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->acquisition->viewOnFocus(true);
    ui->recognition->viewOnFocus(false);
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
