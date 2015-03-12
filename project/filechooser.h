#ifndef FILECHOOSER_H
#define FILECHOOSER_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

#include <string>

namespace Ui {
class FileChooser;
}

class FileChooser : public QWidget
{
    Q_OBJECT

public:
    explicit FileChooser(QWidget *parent = 0);

    void asFileSaver();
    void asFileOpener();

    const string getSelectedFile();

    ~FileChooser();

private slots:
    void on_btnChoose_clicked();

private:
    Ui::FileChooser *ui;

    bool saver;
};

#endif // FILECHOOSER_H
