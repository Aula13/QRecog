#include "filechooser.h"
#include "ui_filechooser.h"

FileChooser::FileChooser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileChooser)
{
    ui->setupUi(this);
}

void FileChooser::asFileSaver()
{
    saver=true;
}

void FileChooser::asFileOpener()
{
    saver=false;
}

const std::string FileChooser::getSelectedFile()
{
    return ui->txtPath->text().toStdString();
}

FileChooser::~FileChooser()
{
    delete ui;
}

void FileChooser::on_btnChoose_clicked()
{
    QString filename;
    if(saver)
        filename= QFileDialog::getSaveFileName(
                this,
                "Save file",
                "",
                "PCD files (*.pcd)"
                );
    else
        filename= QFileDialog::getOpenFileName(
                this,
                "Open file",
                "",
                "PCD files (*.pcd)"
                );
    ui->txtPath->setText(filename);
    Logger::logInfo("File choosed: " + filename.toStdString());
}
