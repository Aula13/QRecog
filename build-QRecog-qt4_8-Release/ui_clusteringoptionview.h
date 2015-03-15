/********************************************************************************
** Form generated from reading UI file 'clusteringoptionview.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLUSTERINGOPTIONVIEW_H
#define UI_CLUSTERINGOPTIONVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClusteringOptionView
{
public:
    QFrame *frame;
    QSpinBox *spnMaxClusterSize;
    QLabel *lblMinClusterSize;
    QDoubleSpinBox *spnClusterTolerance;
    QLabel *lblClusterTolerance;
    QSpinBox *spnMinClusterSize;
    QLabel *lblClusteringOptions;
    QLabel *lblMaxClusterSize;

    void setupUi(QWidget *ClusteringOptionView)
    {
        if (ClusteringOptionView->objectName().isEmpty())
            ClusteringOptionView->setObjectName(QString::fromUtf8("ClusteringOptionView"));
        ClusteringOptionView->resize(240, 140);
        frame = new QFrame(ClusteringOptionView);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 240, 140));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        spnMaxClusterSize = new QSpinBox(frame);
        spnMaxClusterSize->setObjectName(QString::fromUtf8("spnMaxClusterSize"));
        spnMaxClusterSize->setGeometry(QRect(160, 96, 71, 31));
        lblMinClusterSize = new QLabel(frame);
        lblMinClusterSize->setObjectName(QString::fromUtf8("lblMinClusterSize"));
        lblMinClusterSize->setGeometry(QRect(20, 66, 121, 21));
        lblMinClusterSize->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spnClusterTolerance = new QDoubleSpinBox(frame);
        spnClusterTolerance->setObjectName(QString::fromUtf8("spnClusterTolerance"));
        spnClusterTolerance->setGeometry(QRect(160, 26, 69, 31));
        lblClusterTolerance = new QLabel(frame);
        lblClusterTolerance->setObjectName(QString::fromUtf8("lblClusterTolerance"));
        lblClusterTolerance->setGeometry(QRect(20, 26, 141, 31));
        lblClusterTolerance->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spnMinClusterSize = new QSpinBox(frame);
        spnMinClusterSize->setObjectName(QString::fromUtf8("spnMinClusterSize"));
        spnMinClusterSize->setGeometry(QRect(160, 62, 71, 31));
        lblClusteringOptions = new QLabel(frame);
        lblClusteringOptions->setObjectName(QString::fromUtf8("lblClusteringOptions"));
        lblClusteringOptions->setGeometry(QRect(10, 6, 221, 21));
        lblClusteringOptions->setAlignment(Qt::AlignCenter);
        lblMaxClusterSize = new QLabel(frame);
        lblMaxClusterSize->setObjectName(QString::fromUtf8("lblMaxClusterSize"));
        lblMaxClusterSize->setGeometry(QRect(20, 100, 121, 21));
        lblMaxClusterSize->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(ClusteringOptionView);

        QMetaObject::connectSlotsByName(ClusteringOptionView);
    } // setupUi

    void retranslateUi(QWidget *ClusteringOptionView)
    {
        ClusteringOptionView->setWindowTitle(QApplication::translate("ClusteringOptionView", "Form", 0, QApplication::UnicodeUTF8));
        lblMinClusterSize->setText(QApplication::translate("ClusteringOptionView", "Min cluster size", 0, QApplication::UnicodeUTF8));
        lblClusterTolerance->setText(QApplication::translate("ClusteringOptionView", "Cluster tolerance", 0, QApplication::UnicodeUTF8));
        lblClusteringOptions->setText(QApplication::translate("ClusteringOptionView", "Clustering options", 0, QApplication::UnicodeUTF8));
        lblMaxClusterSize->setText(QApplication::translate("ClusteringOptionView", "Max cluster size", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ClusteringOptionView: public Ui_ClusteringOptionView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLUSTERINGOPTIONVIEW_H
