#include "plcviewer.h"
#include "ui_plcviewer.h"

PLCViewer::PLCViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PLCViewer)
{
    ui->setupUi(this);
}

PLCViewer::~PLCViewer()
{
    delete ui;
}
