/********************************************************************************
** Form generated from reading UI file 'MyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFORM_H
#define UI_MYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include "MyQLabel.h"
#include "MyQLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_MyForm
{
public:
    MyQLabel *label;
    MyQLineEdit *lineEdit;
    QLabel *label_2;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(795, 603);
        label = new MyQLabel(MyForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(480, 220, 58, 18));
        lineEdit = new MyQLineEdit(MyForm);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(250, 200, 113, 32));
        label_2 = new QLabel(MyForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 220, 58, 18));

        retranslateUi(MyForm);
        QObject::connect(lineEdit, SIGNAL(returnPressed()), label, SLOT(incrementarContador()));
        QObject::connect(lineEdit, SIGNAL(returnPressed()), lineEdit, SLOT(capturaReturn()));
        QObject::connect(lineEdit, SIGNAL(enviarTexto(QString)), label_2, SLOT(setText(QString)));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QCoreApplication::translate("MyForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("MyForm", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("MyForm", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
