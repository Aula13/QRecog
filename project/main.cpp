#include "mainwindow.h"
#include <QApplication>

#include "logger.h"

int main(int argc, char *argv[])
{
    Logger::configLoggerLevel(DEBUG);

    QApplication a(argc, argv);
    a.setApplicationName("QRecog");
    MainWindow w;
    //w.setWindowIcon(QIcon("resources/icon.png"))
    w.show();

    return a.exec();
}
