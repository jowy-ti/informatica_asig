/********************************************************************************
** Form generated from reading UI file 'MyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFORM_H
#define UI_MYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyQLabel.h"

QT_BEGIN_NAMESPACE

class Ui_MyForm
{
public:
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    MyQLabel *label;
    QRadioButton *radioButton;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    MyQLabel *label_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_2;
    MyQLabel *label_3;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_3;
    MyQLabel *label_4;
    QSpacerItem *horizontalSpacer;
    MyQLabel *label_5;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(795, 603);
        verticalLayout_6 = new QVBoxLayout(MyForm);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new MyQLabel(MyForm);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        radioButton = new QRadioButton(MyForm);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        horizontalLayout->addWidget(radioButton);


        verticalLayout_5->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton = new QPushButton(MyForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        label_2 = new MyQLabel(MyForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);


        verticalLayout_5->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_2 = new QPushButton(MyForm);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_3->addWidget(pushButton_2);

        label_3 = new MyQLabel(MyForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);


        verticalLayout_5->addLayout(horizontalLayout_3);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButton_3 = new QPushButton(MyForm);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_4->addWidget(pushButton_3);

        label_4 = new MyQLabel(MyForm);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);


        verticalLayout_5->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout_5);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        label_5 = new MyQLabel(MyForm);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);


        verticalLayout_6->addLayout(horizontalLayout_5);


        retranslateUi(MyForm);
        QObject::connect(pushButton, SIGNAL(clicked()), label_2, SLOT(incrementarContador()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), label_3, SLOT(incrementarContador()));
        QObject::connect(radioButton, SIGNAL(clicked()), label_2, SLOT(cambiarEstate()));
        QObject::connect(radioButton, SIGNAL(clicked()), label_3, SLOT(cambiarEstate()));
        QObject::connect(pushButton, SIGNAL(clicked()), label_5, SLOT(sumarPrecioCotxe_Moto()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), label_5, SLOT(sumarPrecioCotxe_Moto()));
        QObject::connect(radioButton, SIGNAL(clicked()), label_5, SLOT(cambiarEstate()));
        QObject::connect(radioButton, SIGNAL(clicked()), label, SLOT(cambiarColor()));
        QObject::connect(radioButton, SIGNAL(clicked()), label_4, SLOT(cambiarEstate()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), label_4, SLOT(incrementarContador()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), label_5, SLOT(sumarPrecioCamion()));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QCoreApplication::translate("MyForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("MyForm", "TextLabel", nullptr));
        radioButton->setText(QCoreApplication::translate("MyForm", "RadioButton", nullptr));
        pushButton->setText(QCoreApplication::translate("MyForm", "Coche", nullptr));
        label_2->setText(QCoreApplication::translate("MyForm", "TextLabel", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MyForm", "Moto", nullptr));
        label_3->setText(QCoreApplication::translate("MyForm", "TextLabel", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MyForm", "Cami\303\263n", nullptr));
        label_4->setText(QCoreApplication::translate("MyForm", "TextLabel", nullptr));
        label_5->setText(QCoreApplication::translate("MyForm", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
