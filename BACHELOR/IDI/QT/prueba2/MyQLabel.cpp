#include "MyQLabel.h"

MyQLabel::MyQLabel(QWidget *parent):QLabel(parent) {
}

void MyQLabel::incrementarContador() {

    contador++;
    setText(QString::number(contador));
}
