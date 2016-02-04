#include "mainwindow.h"
#include <QApplication>

#include "logger.h"
#include "help.h"
#include "models.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setApplicationName("QRecog");

    if(argc!=1)
    {
        for(int i=1; i<argc; i++)
        {
            bool match = false;
            if(std::strcmp(argv[i],"-h")==0)
            {
                Help::showHelp();
                return 1;
            }

            if(std::strcmp(argv[i],"-s")==0) {
                Models::initSimulation();
                match = true;
            }

            if(std::strcmp(argv[i],"-gv")==0) {
                Models::initOpenGEVCamera();
                match = true;
            }

            if(std::strcmp(argv[i],"-usb")==0) {
                Models::initRealCamera();
                match = true;
            }

            if(!match) {
                Help::showHelp();
                return 1;
            }
        }
    } else
        Models::initRealCamera();

    Logger::configLoggerLevel(DEBUG);

    MainWindow w;
    //w.setWindowIcon(QIcon("resources/icon.png"))
    w.show();

    return a.exec();
}
