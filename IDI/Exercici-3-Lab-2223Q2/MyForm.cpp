#include "MyForm.h"

MyForm::MyForm(QWidget *parent): QWidget(parent), ui(new Ui::MyForm) {
    ui->setupUi(this);
    ui->lcdNumber->display("00:00:00:000");
}

void MyForm::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_S && event->modifiers() == Qt::AltModifier) { 
        if (ui->lcdNumber->start) ui->pushButton_2->clicked();
        else ui->pushButton->clicked();
    }
    
    if (event->key() == Qt::Key_R && event->modifiers() == Qt::AltModifier) 
        ui->pushButton_3->clicked();
    
    if (event->key() == Qt::Key_Q && event->modifiers() == Qt::AltModifier) 
        ui->pushButton_4->clicked();
}
