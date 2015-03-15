/********************************************************************************
** Form generated from reading UI file 'cameractrlview.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERACTRLVIEW_H
#define UI_CAMERACTRLVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraCtrlView
{
public:
    QFrame *frmCameraCmd;
    QPushButton *btnStartCamera;
    QPushButton *btnStopCamera;
    QLabel *title;

    void setupUi(QWidget *CameraCtrlView)
    {
        if (CameraCtrlView->objectName().isEmpty())
            CameraCtrlView->setObjectName(QString::fromUtf8("CameraCtrlView"));
        CameraCtrlView->resize(240, 140);
        frmCameraCmd = new QFrame(CameraCtrlView);
        frmCameraCmd->setObjectName(QString::fromUtf8("frmCameraCmd"));
        frmCameraCmd->setGeometry(QRect(0, 0, 241, 141));
        frmCameraCmd->setFrameShape(QFrame::StyledPanel);
        frmCameraCmd->setFrameShadow(QFrame::Sunken);
        btnStartCamera = new QPushButton(frmCameraCmd);
        btnStartCamera->setObjectName(QString::fromUtf8("btnStartCamera"));
        btnStartCamera->setGeometry(QRect(10, 40, 221, 41));
        btnStopCamera = new QPushButton(frmCameraCmd);
        btnStopCamera->setObjectName(QString::fromUtf8("btnStopCamera"));
        btnStopCamera->setGeometry(QRect(10, 90, 221, 41));
        title = new QLabel(frmCameraCmd);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(10, 0, 221, 21));
        title->setAlignment(Qt::AlignCenter);

        retranslateUi(CameraCtrlView);

        QMetaObject::connectSlotsByName(CameraCtrlView);
    } // setupUi

    void retranslateUi(QWidget *CameraCtrlView)
    {
        CameraCtrlView->setWindowTitle(QApplication::translate("CameraCtrlView", "Form", 0, QApplication::UnicodeUTF8));
        btnStartCamera->setText(QApplication::translate("CameraCtrlView", "Start", 0, QApplication::UnicodeUTF8));
        btnStopCamera->setText(QApplication::translate("CameraCtrlView", "Stop", 0, QApplication::UnicodeUTF8));
        title->setText(QApplication::translate("CameraCtrlView", "3D Camera control", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CameraCtrlView: public Ui_CameraCtrlView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERACTRLVIEW_H
