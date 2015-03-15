/********************************************************************************
** Form generated from reading UI file 'clusteringview.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLUSTERINGVIEW_H
#define UI_CLUSTERINGVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
#include <clusteringoptionview.h>
#include <filechooser.h>
#include <filteroptionview.h>
#include <pclviewer.h>
#include <segmentationoptionview.h>

QT_BEGIN_NAMESPACE

class Ui_ClusteringView
{
public:
    QFrame *frmClustering;
    QPushButton *btnSegment;
    QLabel *lblClustering;
    FilterOptionView *wgtFilterOptionView;
    SegmentationOptionView *wgtSegOptionView;
    QLabel *lblSegInputFile;
    FileChooser *wgtSegFileChooser;
    ClusteringOptionView *wgtClusterOptionView;
    QFrame *frmCtrlModel;
    QLabel *lblOutputFile;
    FileChooser *wgtOutFileChooser;
    QPushButton *btnPrevModel;
    QPushButton *btnNextModel;
    QPushButton *btnSaveModel;
    PCLViewer *wgtPCLViewer;
    QLabel *lblExtrModelsPreview;

    void setupUi(QWidget *ClusteringView)
    {
        if (ClusteringView->objectName().isEmpty())
            ClusteringView->setObjectName(QString::fromUtf8("ClusteringView"));
        ClusteringView->resize(981, 651);
        frmClustering = new QFrame(ClusteringView);
        frmClustering->setObjectName(QString::fromUtf8("frmClustering"));
        frmClustering->setGeometry(QRect(10, 10, 261, 631));
        frmClustering->setFrameShape(QFrame::StyledPanel);
        frmClustering->setFrameShadow(QFrame::Sunken);
        btnSegment = new QPushButton(frmClustering);
        btnSegment->setObjectName(QString::fromUtf8("btnSegment"));
        btnSegment->setGeometry(QRect(10, 570, 241, 41));
        lblClustering = new QLabel(frmClustering);
        lblClustering->setObjectName(QString::fromUtf8("lblClustering"));
        lblClustering->setGeometry(QRect(10, 0, 221, 21));
        lblClustering->setAlignment(Qt::AlignCenter);
        wgtFilterOptionView = new FilterOptionView(frmClustering);
        wgtFilterOptionView->setObjectName(QString::fromUtf8("wgtFilterOptionView"));
        wgtFilterOptionView->setGeometry(QRect(10, 20, 240, 80));
        wgtSegOptionView = new SegmentationOptionView(frmClustering);
        wgtSegOptionView->setObjectName(QString::fromUtf8("wgtSegOptionView"));
        wgtSegOptionView->setGeometry(QRect(10, 110, 240, 230));
        lblSegInputFile = new QLabel(frmClustering);
        lblSegInputFile->setObjectName(QString::fromUtf8("lblSegInputFile"));
        lblSegInputFile->setGeometry(QRect(20, 500, 221, 21));
        lblSegInputFile->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        wgtSegFileChooser = new FileChooser(frmClustering);
        wgtSegFileChooser->setObjectName(QString::fromUtf8("wgtSegFileChooser"));
        wgtSegFileChooser->setGeometry(QRect(20, 520, 221, 31));
        wgtClusterOptionView = new ClusteringOptionView(frmClustering);
        wgtClusterOptionView->setObjectName(QString::fromUtf8("wgtClusterOptionView"));
        wgtClusterOptionView->setGeometry(QRect(10, 350, 240, 140));
        frmCtrlModel = new QFrame(ClusteringView);
        frmCtrlModel->setObjectName(QString::fromUtf8("frmCtrlModel"));
        frmCtrlModel->setGeometry(QRect(280, 10, 691, 631));
        frmCtrlModel->setFrameShape(QFrame::StyledPanel);
        frmCtrlModel->setFrameShadow(QFrame::Raised);
        lblOutputFile = new QLabel(frmCtrlModel);
        lblOutputFile->setObjectName(QString::fromUtf8("lblOutputFile"));
        lblOutputFile->setGeometry(QRect(310, 30, 81, 41));
        lblOutputFile->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        wgtOutFileChooser = new FileChooser(frmCtrlModel);
        wgtOutFileChooser->setObjectName(QString::fromUtf8("wgtOutFileChooser"));
        wgtOutFileChooser->setGeometry(QRect(390, 30, 221, 41));
        btnPrevModel = new QPushButton(frmCtrlModel);
        btnPrevModel->setObjectName(QString::fromUtf8("btnPrevModel"));
        btnPrevModel->setGeometry(QRect(10, 30, 121, 41));
        btnNextModel = new QPushButton(frmCtrlModel);
        btnNextModel->setObjectName(QString::fromUtf8("btnNextModel"));
        btnNextModel->setGeometry(QRect(130, 30, 121, 41));
        btnSaveModel = new QPushButton(frmCtrlModel);
        btnSaveModel->setObjectName(QString::fromUtf8("btnSaveModel"));
        btnSaveModel->setGeometry(QRect(610, 30, 71, 41));
        wgtPCLViewer = new PCLViewer(frmCtrlModel);
        wgtPCLViewer->setObjectName(QString::fromUtf8("wgtPCLViewer"));
        wgtPCLViewer->setGeometry(QRect(10, 80, 671, 541));
        lblExtrModelsPreview = new QLabel(frmCtrlModel);
        lblExtrModelsPreview->setObjectName(QString::fromUtf8("lblExtrModelsPreview"));
        lblExtrModelsPreview->setGeometry(QRect(230, 0, 221, 21));
        lblExtrModelsPreview->setAlignment(Qt::AlignCenter);

        retranslateUi(ClusteringView);

        QMetaObject::connectSlotsByName(ClusteringView);
    } // setupUi

    void retranslateUi(QWidget *ClusteringView)
    {
        ClusteringView->setWindowTitle(QApplication::translate("ClusteringView", "Form", 0, QApplication::UnicodeUTF8));
        btnSegment->setText(QApplication::translate("ClusteringView", "Start clustering", 0, QApplication::UnicodeUTF8));
        lblClustering->setText(QApplication::translate("ClusteringView", "Clustering", 0, QApplication::UnicodeUTF8));
        lblSegInputFile->setText(QApplication::translate("ClusteringView", "Target file", 0, QApplication::UnicodeUTF8));
        lblOutputFile->setText(QApplication::translate("ClusteringView", "Output file", 0, QApplication::UnicodeUTF8));
        btnPrevModel->setText(QApplication::translate("ClusteringView", "Previous model", 0, QApplication::UnicodeUTF8));
        btnNextModel->setText(QApplication::translate("ClusteringView", "Next model", 0, QApplication::UnicodeUTF8));
        btnSaveModel->setText(QApplication::translate("ClusteringView", "Save", 0, QApplication::UnicodeUTF8));
        lblExtrModelsPreview->setText(QApplication::translate("ClusteringView", "Extracted models preview", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ClusteringView: public Ui_ClusteringView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLUSTERINGVIEW_H
