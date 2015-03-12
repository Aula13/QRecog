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
        mainwindow.cpp \
    viewermodel.cpp \
    cameramodel.cpp \
    observer.cpp \
    observable.cpp \
    pclviewer.cpp \
    acquisitionview.cpp \
    cameractrlview.cpp \
    logger.cpp \
    pcsource.cpp \
    simcameramodel.cpp \
    models.cpp \
    filechooser.cpp

HEADERS  += mainwindow.h \
    defines.h \
    viewermodel.h \
    cameramodel.h \
    observer.h \
    observable.h \
    pclviewer.h \
    acquisitionview.h \
    cameractrlview.h \
    logger.h \
    pcsource.h \
    simcameramodel.h \
    models.h \
    filechooser.h

FORMS    += mainwindow.ui \
    pclviewer.ui \
    acquisitionview.ui \
    cameractrlview.ui \
    filechooser.ui

unix:!macx {
    INCLUDEPATH += /usr/include/pcl-1.7 \
                   /usr/include/eigen3 \
                   /usr/include/openni2 \
                   /usr/include/vtk-5.8 \
                   /usr/include/boost \
                   /usr/include/flann


    LIBS += "-L/usr/lib"

    LIBS += -lboost_system

    LIBS += -lpcl_apps
    LIBS += -lpcl_common
    LIBS += -lpcl_filters
    LIBS += -lpcl_keypoints
    LIBS += -lpcl_kdtree
    LIBS += -lpcl_search
    LIBS += -lpcl_features
    LIBS += -lpcl_io
    LIBS += -lpcl_io_ply
    LIBS += -lpcl_visualization

    LIBS += -lvtkCommon \
            -lvtkGraphics \
            -lvtkFiltering \
            -lvtkIO \
            -lvtkImaging \
            -lvtkRendering \
            -lQVTK
}

macx {
    INCLUDEPATH += /
}
