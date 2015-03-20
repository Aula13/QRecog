#include "mainwindow.h"
#include <QApplication>

#include "logger.h"
#include "help.h"
#include "models.h"

int main(int argc, char *argv[])
{

    if(argc!=1)
    {
        for(int i=1; i<argc; i++)
        {
            if(std::strcmp(argv[i],"-h")==0)
            {
                Help::showHelp();
                return 1;
            } else {
                if(std::strcmp(argv[i],"-s")==0)
                    Models::initSimulation();
                else {
                    Help::showHelp();
                    return 1;
                }
            }
        }
    } else
        Models::initRealCamera();

    Logger::configLoggerLevel(DEBUG);

    QApplication a(argc, argv);
    a.setApplicationName("QRecog");
    MainWindow w;
    //w.setWindowIcon(QIcon("resources/icon.png"))
    w.show();

    return a.exec();
}
