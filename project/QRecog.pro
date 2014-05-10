#-------------------------------------------------
#
# Project created by QtCreator 2014-03-27T20:14:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QRecog
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    defines.h

FORMS    += mainwindow.ui

unix:!macx {
    INCLUDEPATH += /usr/include/pcl-1.7
}

macx {
    INCLUDEPATH += /
}
