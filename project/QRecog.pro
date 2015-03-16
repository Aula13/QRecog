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
        filechooser.cpp \
        pclfunction.cpp \
        pclfilterfunction.cpp \
        clusteringview.cpp \
        filteroptionview.cpp \
        clusteringoptionview.cpp \
        segmentationoptionview.cpp \
        pclsegmentationfunction.cpp \
        pclclusteringfunction.cpp \
        correspondenceview.cpp \
    pclcorrgroupfunction.cpp

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
            filechooser.h \
            pclfunction.h \
            pclfilterfunction.h \
            clusteringview.h \
            filteroptionview.h \
            clusteringoptionview.h \
            segmentationoptionview.h \
            pclsegmentationfunction.h \
            pclclusteringfunction.h \
            correspondenceview.h \
    pclcorrgroupfunction.h

FORMS    += mainwindow.ui \
            pclviewer.ui \
            acquisitionview.ui \
            cameractrlview.ui \
            filechooser.ui \
            clusteringview.ui \
            filteroptionview.ui \
            clusteringoptionview.ui \
            segmentationoptionview.ui \
            correspondenceview.ui

macx {
    INCLUDEPATH += /usr/local/include/ \
                   /usr/include/ \
                   /usr/local/include/pcl-1.7 \
                   /usr/local/include/eigen3 \
                   /usr/local/include/openni \
                   /usr/local/include/vtk-5.10 \
                   /usr/local/include/boost \
                   /usr/local/include/flann \
                   /usr/local/include/ni2 \
                   /usr/local/include/ni \

    LIBS += "-L/usr/local/lib" \
            "-L/usr/local/lib/ni2" \
            "-L/usr/local/Cellar/vtk5/5.10.1_1/lib/vtk-5.10"
}

unix {
    INCLUDEPATH += /usr/include/pcl-1.7 \
                   /usr/include/eigen3 \
                   /usr/include/openni2 \
                   /usr/include/vtk-5.8 \
                   /usr/include/boost \
                   /usr/include/flann

    LIBS += "-L/usr/lib"
    LIBS += -lboost_system \

    LIBS += -lpcl_apps \
            -lpcl_common \
            -lpcl_filters \
            -lpcl_keypoints \
            -lpcl_kdtree \
            -lpcl_search \
            -lpcl_features \
            -lpcl_io \
            -lpcl_io_ply \
            -lpcl_visualization \
            -lpcl_sample_consensus \
            -lpcl_segmentation \
            -lpcl_recognition \
            -lpcl_registration

    LIBS += -lvtkCommon \
            -lvtkGraphics \
            -lvtkFiltering \
            -lvtkIO \
            -lvtkImaging \
            -lvtkRendering \
            -lQVTK
}

# QMAKE FLAGS
macx {
    IQMAKE_CXXFLAGS_X86_64  -= -mmacosx-version-min=10.5
    QMAKE_LFLAGS_X86_64     -= -mmacosx-version-min=10.5
    QMAKE_CXXFLAGS_X86_64   +=  -mmacosx-version-min=10.9
    QMAKE_LFLAGS_X86_64     += -mmacosx-version-min=10.9
}
