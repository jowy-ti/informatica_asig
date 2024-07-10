#include "MyQLineEdit.h"

MyQLineEdit::MyQLineEdit(QWidget *parent):QLineEdit(parent) {
}

void MyQLineEdit::capturaReturn() {
    emit enviarTexto(text());
}
