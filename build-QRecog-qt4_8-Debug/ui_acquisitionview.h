/********************************************************************************
** Form generated from reading UI file 'acquisitionview.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACQUISITIONVIEW_H
#define UI_ACQUISITIONVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
#include <cameractrlview.h>
#include <filechooser.h>
#include <pclviewer.h>

QT_BEGIN_NAMESPACE

class Ui_AcquisitionView
{
public:
    PCLViewer *wgtPCLViewer;
    QFrame *frmAcquisition;
    QPushButton *btnCapture;
    QLabel *lblAcquisition;
    QLabel *lblOutputFile;
    FileChooser *wgtFIleChooser;
    CameraCtrlView *wgtCameraCtrl;
    QCheckBox *checkBox;

    void setupUi(QWidget *AcquisitionView)
    {
        if (AcquisitionView->objectName().isEmpty())
            AcquisitionView->setObjectName(QString::fromUtf8("AcquisitionView"));
        AcquisitionView->resize(981, 651);
        wgtPCLViewer = new PCLViewer(AcquisitionView);
        wgtPCLViewer->setObjectName(QString::fromUtf8("wgtPCLViewer"));
        wgtPCLViewer->setGeometry(QRect(260, 9, 711, 631));
        frmAcquisition = new QFrame(AcquisitionView);
        frmAcquisition->setObjectName(QString::fromUtf8("frmAcquisition"));
        frmAcquisition->setGeometry(QRect(10, 190, 241, 141));
        frmAcquisition->setFrameShape(QFrame::StyledPanel);
        frmAcquisition->setFrameShadow(QFrame::Sunken);
        btnCapture = new QPushButton(frmAcquisition);
        btnCapture->setObjectName(QString::fromUtf8("btnCapture"));
        btnCapture->setGeometry(QRect(10, 90, 221, 41));
        lblAcquisition = new QLabel(frmAcquisition);
        lblAcquisition->setObjectName(QString::fromUtf8("lblAcquisition"));
        lblAcquisition->setGeometry(QRect(10, 0, 221, 21));
        lblAcquisition->setAlignment(Qt::AlignCenter);
        lblOutputFile = new QLabel(frmAcquisition);
        lblOutputFile->setObjectName(QString::fromUtf8("lblOutputFile"));
        lblOutputFile->setGeometry(QRect(10, 30, 221, 21));
        lblOutputFile->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        wgtFIleChooser = new FileChooser(frmAcquisition);
        wgtFIleChooser->setObjectName(QString::fromUtf8("wgtFIleChooser"));
        wgtFIleChooser->setGeometry(QRect(10, 50, 221, 31));
        wgtCameraCtrl = new CameraCtrlView(AcquisitionView);
        wgtCameraCtrl->setObjectName(QString::fromUtf8("wgtCameraCtrl"));
        wgtCameraCtrl->setGeometry(QRect(10, 10, 241, 141));
        checkBox = new QCheckBox(AcquisitionView);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(20, 160, 221, 22));

        retranslateUi(AcquisitionView);

        QMetaObject::connectSlotsByName(AcquisitionView);
    } // setupUi

    void retranslateUi(QWidget *AcquisitionView)
    {
        AcquisitionView->setWindowTitle(QApplication::translate("AcquisitionView", "Form", 0, QApplication::UnicodeUTF8));
        btnCapture->setText(QApplication::translate("AcquisitionView", "Capture", 0, QApplication::UnicodeUTF8));
        lblAcquisition->setText(QApplication::translate("AcquisitionView", "Acquisition", 0, QApplication::UnicodeUTF8));
        lblOutputFile->setText(QApplication::translate("AcquisitionView", "Output file", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("AcquisitionView", "Disable view updates", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AcquisitionView: public Ui_AcquisitionView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACQUISITIONVIEW_H
