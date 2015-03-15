/********************************************************************************
** Form generated from reading UI file 'filechooser.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILECHOOSER_H
#define UI_FILECHOOSER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileChooser
{
public:
    QPushButton *btnChoose;
    QLineEdit *txtPath;

    void setupUi(QWidget *FileChooser)
    {
        if (FileChooser->objectName().isEmpty())
            FileChooser->setObjectName(QString::fromUtf8("FileChooser"));
        FileChooser->resize(221, 30);
        btnChoose = new QPushButton(FileChooser);
        btnChoose->setObjectName(QString::fromUtf8("btnChoose"));
        btnChoose->setGeometry(QRect(190, 0, 31, 31));
        txtPath = new QLineEdit(FileChooser);
        txtPath->setObjectName(QString::fromUtf8("txtPath"));
        txtPath->setGeometry(QRect(0, 0, 191, 31));

        retranslateUi(FileChooser);

        QMetaObject::connectSlotsByName(FileChooser);
    } // setupUi

    void retranslateUi(QWidget *FileChooser)
    {
        FileChooser->setWindowTitle(QApplication::translate("FileChooser", "Form", 0, QApplication::UnicodeUTF8));
        btnChoose->setText(QApplication::translate("FileChooser", "...", 0, QApplication::UnicodeUTF8));
        txtPath->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FileChooser: public Ui_FileChooser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILECHOOSER_H
