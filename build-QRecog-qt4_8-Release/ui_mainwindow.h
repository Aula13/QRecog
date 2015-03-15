/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include <acquisitionview.h>
#include <clusteringview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionError;
    QAction *actionWarning;
    QAction *actionInfo;
    QAction *actionDebug;
    QWidget *tabMain;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QTabWidget *maintab;
    AcquisitionView *acquisition;
    ClusteringView *Clustering;
    QWidget *recognition;
    QMenuBar *menuBar;
    QMenu *menu3D_Camera;
    QMenu *menuLogger;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 750);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionError = new QAction(MainWindow);
        actionError->setObjectName(QString::fromUtf8("actionError"));
        actionWarning = new QAction(MainWindow);
        actionWarning->setObjectName(QString::fromUtf8("actionWarning"));
        actionInfo = new QAction(MainWindow);
        actionInfo->setObjectName(QString::fromUtf8("actionInfo"));
        actionDebug = new QAction(MainWindow);
        actionDebug->setObjectName(QString::fromUtf8("actionDebug"));
        tabMain = new QWidget(MainWindow);
        tabMain->setObjectName(QString::fromUtf8("tabMain"));
        horizontalLayout_2 = new QHBoxLayout(tabMain);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        maintab = new QTabWidget(tabMain);
        maintab->setObjectName(QString::fromUtf8("maintab"));
        acquisition = new AcquisitionView();
        acquisition->setObjectName(QString::fromUtf8("acquisition"));
        maintab->addTab(acquisition, QString());
        Clustering = new ClusteringView();
        Clustering->setObjectName(QString::fromUtf8("Clustering"));
        maintab->addTab(Clustering, QString());
        recognition = new QWidget();
        recognition->setObjectName(QString::fromUtf8("recognition"));
        recognition->setContextMenuPolicy(Qt::NoContextMenu);
        maintab->addTab(recognition, QString());

        horizontalLayout->addWidget(maintab);


        horizontalLayout_2->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(tabMain);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 25));
        menu3D_Camera = new QMenu(menuBar);
        menu3D_Camera->setObjectName(QString::fromUtf8("menu3D_Camera"));
        menuLogger = new QMenu(menuBar);
        menuLogger->setObjectName(QString::fromUtf8("menuLogger"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu3D_Camera->menuAction());
        menuBar->addAction(menuLogger->menuAction());
        menu3D_Camera->addAction(actionExit);
        menuLogger->addAction(actionError);
        menuLogger->addAction(actionWarning);
        menuLogger->addAction(actionInfo);
        menuLogger->addAction(actionDebug);

        retranslateUi(MainWindow);

        maintab->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionError->setText(QApplication::translate("MainWindow", "Error", 0, QApplication::UnicodeUTF8));
        actionWarning->setText(QApplication::translate("MainWindow", "Warning", 0, QApplication::UnicodeUTF8));
        actionInfo->setText(QApplication::translate("MainWindow", "Info", 0, QApplication::UnicodeUTF8));
        actionDebug->setText(QApplication::translate("MainWindow", "Debug", 0, QApplication::UnicodeUTF8));
        maintab->setTabText(maintab->indexOf(acquisition), QApplication::translate("MainWindow", "Acquisition", 0, QApplication::UnicodeUTF8));
        maintab->setTabText(maintab->indexOf(Clustering), QApplication::translate("MainWindow", "Clustering", 0, QApplication::UnicodeUTF8));
        maintab->setTabText(maintab->indexOf(recognition), QApplication::translate("MainWindow", "Recognition", 0, QApplication::UnicodeUTF8));
        menu3D_Camera->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuLogger->setTitle(QApplication::translate("MainWindow", "Logger", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
