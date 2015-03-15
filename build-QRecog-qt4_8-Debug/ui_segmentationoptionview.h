/********************************************************************************
** Form generated from reading UI file 'segmentationoptionview.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEGMENTATIONOPTIONVIEW_H
#define UI_SEGMENTATIONOPTIONVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SegmentationOptionView
{
public:
    QFrame *frame;
    QLabel *lblDistanceThreshold;
    QComboBox *cmbModelType;
    QSpinBox *spnMaxIterations;
    QLabel *lblMaxIterations;
    QLabel *lblModelType;
    QDoubleSpinBox *spnDistanceThreshold;
    QCheckBox *chkOptimazeCoef;
    QLabel *lblMethodType;
    QComboBox *cmbMethodType;
    QLabel *lblSegmentationOptions;

    void setupUi(QWidget *SegmentationOptionView)
    {
        if (SegmentationOptionView->objectName().isEmpty())
            SegmentationOptionView->setObjectName(QString::fromUtf8("SegmentationOptionView"));
        SegmentationOptionView->resize(240, 230);
        frame = new QFrame(SegmentationOptionView);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 240, 230));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        lblDistanceThreshold = new QLabel(frame);
        lblDistanceThreshold->setObjectName(QString::fromUtf8("lblDistanceThreshold"));
        lblDistanceThreshold->setGeometry(QRect(20, 190, 141, 31));
        lblDistanceThreshold->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        cmbModelType = new QComboBox(frame);
        cmbModelType->setObjectName(QString::fromUtf8("cmbModelType"));
        cmbModelType->setGeometry(QRect(14, 70, 211, 27));
        spnMaxIterations = new QSpinBox(frame);
        spnMaxIterations->setObjectName(QString::fromUtf8("spnMaxIterations"));
        spnMaxIterations->setGeometry(QRect(160, 156, 71, 31));
        lblMaxIterations = new QLabel(frame);
        lblMaxIterations->setObjectName(QString::fromUtf8("lblMaxIterations"));
        lblMaxIterations->setGeometry(QRect(20, 160, 121, 21));
        lblMaxIterations->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblModelType = new QLabel(frame);
        lblModelType->setObjectName(QString::fromUtf8("lblModelType"));
        lblModelType->setGeometry(QRect(20, 50, 201, 21));
        lblModelType->setAlignment(Qt::AlignCenter);
        spnDistanceThreshold = new QDoubleSpinBox(frame);
        spnDistanceThreshold->setObjectName(QString::fromUtf8("spnDistanceThreshold"));
        spnDistanceThreshold->setGeometry(QRect(160, 190, 69, 31));
        chkOptimazeCoef = new QCheckBox(frame);
        chkOptimazeCoef->setObjectName(QString::fromUtf8("chkOptimazeCoef"));
        chkOptimazeCoef->setGeometry(QRect(10, 30, 221, 22));
        lblMethodType = new QLabel(frame);
        lblMethodType->setObjectName(QString::fromUtf8("lblMethodType"));
        lblMethodType->setGeometry(QRect(20, 100, 201, 21));
        lblMethodType->setAlignment(Qt::AlignCenter);
        cmbMethodType = new QComboBox(frame);
        cmbMethodType->setObjectName(QString::fromUtf8("cmbMethodType"));
        cmbMethodType->setGeometry(QRect(14, 120, 211, 27));
        lblSegmentationOptions = new QLabel(frame);
        lblSegmentationOptions->setObjectName(QString::fromUtf8("lblSegmentationOptions"));
        lblSegmentationOptions->setGeometry(QRect(10, 0, 221, 21));
        lblSegmentationOptions->setAlignment(Qt::AlignCenter);

        retranslateUi(SegmentationOptionView);

        QMetaObject::connectSlotsByName(SegmentationOptionView);
    } // setupUi

    void retranslateUi(QWidget *SegmentationOptionView)
    {
        SegmentationOptionView->setWindowTitle(QApplication::translate("SegmentationOptionView", "Form", 0, QApplication::UnicodeUTF8));
        lblDistanceThreshold->setText(QApplication::translate("SegmentationOptionView", "Distance threshold", 0, QApplication::UnicodeUTF8));
        lblMaxIterations->setText(QApplication::translate("SegmentationOptionView", "Max iterations", 0, QApplication::UnicodeUTF8));
        lblModelType->setText(QApplication::translate("SegmentationOptionView", "Model type", 0, QApplication::UnicodeUTF8));
        chkOptimazeCoef->setText(QApplication::translate("SegmentationOptionView", "Optimaze coefficients", 0, QApplication::UnicodeUTF8));
        lblMethodType->setText(QApplication::translate("SegmentationOptionView", "Method type", 0, QApplication::UnicodeUTF8));
        lblSegmentationOptions->setText(QApplication::translate("SegmentationOptionView", "Segmentation options", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SegmentationOptionView: public Ui_SegmentationOptionView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEGMENTATIONOPTIONVIEW_H
