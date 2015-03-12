#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "logger.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    
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
