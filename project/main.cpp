#include "mainwindow.h"
#include <QApplication>

#define LOG_LEVEL 0
#define DEBUG 0

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("QRecog");
    MainWindow w;
    //w.setWindowIcon(QIcon("resources/icon.png"))
    w.show();

    return a.exec();
}
