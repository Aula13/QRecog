#include "mainwindow.h"
#include <QApplication>
#include "OpenNI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("QRecog");
    MainWindow w;
    //w.setWindowIcon(QIcon("resources/icon.png"))
    w.show();

    return a.exec();
}

