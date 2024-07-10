#include "ui_MyForm.h"
#include <QKeyEvent>

namespace Ui {
class MyForm;
}

class MyForm : public QWidget {
    Q_OBJECT

public:
    MyForm(QWidget *parent = 0);
    
protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MyForm *ui;
};
