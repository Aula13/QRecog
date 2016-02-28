#ifndef FILECHOOSER_H
#define FILECHOOSER_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

#include <string>

#include "logger.h"

namespace Ui {
class FileChooser;
}

class FileChooser : public QWidget
{
    Q_OBJECT

public:
    explicit FileChooser(QWidget *parent = 0);

    void setFileType(std::string fileType);
    void asFileSaver();
    void asFileOpener();
    void setSelectedFile(const std::string &s);
    const std::string getSelectedFile();

    ~FileChooser();

private slots:
    void on_btnChoose_clicked();

private:
    Ui::FileChooser *ui;

    bool saver;

    std::string fileType;
};

#endif // FILECHOOSER_H
