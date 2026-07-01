#include <QLabel>

class MyQLabel: public QLabel {

    Q_OBJECT

    public:
    MyQLabel(QWidget *parent);

    int contador = 0;

    public slots:
    void incrementarContador();
};
