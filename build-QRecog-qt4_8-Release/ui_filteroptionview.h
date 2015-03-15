/********************************************************************************
** Form generated from reading UI file 'filteroptionview.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTEROPTIONVIEW_H
#define UI_FILTEROPTIONVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FilterOptionView
{
public:
    QFrame *frmCameraCmd;
    QLabel *lblFilterOptions;
    QDoubleSpinBox *spnLeafSize;
    QLabel *lblLeafSize;

    void setupUi(QWidget *FilterOptionView)
    {
        if (FilterOptionView->objectName().isEmpty())
            FilterOptionView->setObjectName(QString::fromUtf8("FilterOptionView"));
        FilterOptionView->resize(240, 80);
        frmCameraCmd = new QFrame(FilterOptionView);
        frmCameraCmd->setObjectName(QString::fromUtf8("frmCameraCmd"));
        frmCameraCmd->setGeometry(QRect(0, 0, 240, 80));
        frmCameraCmd->setFrameShape(QFrame::StyledPanel);
        frmCameraCmd->setFrameShadow(QFrame::Sunken);
        lblFilterOptions = new QLabel(frmCameraCmd);
        lblFilterOptions->setObjectName(QString::fromUtf8("lblFilterOptions"));
        lblFilterOptions->setGeometry(QRect(10, 0, 221, 21));
        lblFilterOptions->setAlignment(Qt::AlignCenter);
        spnLeafSize = new QDoubleSpinBox(frmCameraCmd);
        spnLeafSize->setObjectName(QString::fromUtf8("spnLeafSize"));
        spnLeafSize->setGeometry(QRect(160, 30, 69, 31));
        spnLeafSize->setDecimals(3);
        spnLeafSize->setMinimum(0.001);
        spnLeafSize->setSingleStep(1);
        lblLeafSize = new QLabel(frmCameraCmd);
        lblLeafSize->setObjectName(QString::fromUtf8("lblLeafSize"));
        lblLeafSize->setGeometry(QRect(10, 30, 151, 31));
        lblLeafSize->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(FilterOptionView);

        QMetaObject::connectSlotsByName(FilterOptionView);
    } // setupUi

    void retranslateUi(QWidget *FilterOptionView)
    {
        FilterOptionView->setWindowTitle(QApplication::translate("FilterOptionView", "Form", 0, QApplication::UnicodeUTF8));
        lblFilterOptions->setText(QApplication::translate("FilterOptionView", "Filter options", 0, QApplication::UnicodeUTF8));
        lblLeafSize->setText(QApplication::translate("FilterOptionView", "Leaf size", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FilterOptionView: public Ui_FilterOptionView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTEROPTIONVIEW_H
