#include "MyQLabel.h"

MyQLabel::MyQLabel(QWidget *parent):QLabel(parent) {
}

void MyQLabel::incrementarContador() {

    if (state == 1) {
        contador++;
        setText(QString::number(contador));
    }
}

void MyQLabel::sumarPrecioCotxe_Moto() {
    if (state == 1) {
        result++;
        setText(QString::number(result));
    }
}

void MyQLabel::sumarPrecioCamion() {

    if (state == 1) {
        result = result+4;
        setText(QString::number(result));
    }
}

void MyQLabel::cambiarEstate() {
    if (state == 1) state = 0;
    else state = 1;
}

void MyQLabel::cambiarColor() {
    QString col;
    if (color == 1) {
        col = "background-color: rgb(255, 0, 0)";
        setStyleSheet(col);
        color = 0;
    }
    else {
        col = "background-color: rgb(255, 255, 255)";
        setStyleSheet(col);
        color = 1;
    }

}
