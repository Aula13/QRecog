#include "filechooser.h"
#include "ui_filechooser.h"

FileChooser::FileChooser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileChooser),
    fileType("PCD files (*.pcd)")
{
    ui->setupUi(this);
}

void FileChooser::setFileType(string fileType)
{
    this->fileType = fileType;
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

void FileChooser::setSelectedFile(const std::string &s)
{
    ui->txtPath->setText(QString::fromStdString(s));
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
                QString::fromStdString(fileType)
                );
    else
        filename= QFileDialog::getOpenFileName(
                this,
                "Open file",
                "",
                QString::fromStdString(fileType)
                );
    ui->txtPath->setText(filename);
    Logger::logInfo("File choosed: " + filename.toStdString());
}
