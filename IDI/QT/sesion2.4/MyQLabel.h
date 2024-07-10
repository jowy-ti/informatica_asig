#include <QLabel>

class MyQLabel: public QLabel {

    Q_OBJECT

    public:
    MyQLabel(QWidget *parent);

    int contador = 0;
    int result = 0;
    int state = 0;
    int color = 0;

    public slots:
    void incrementarContador();
    void sumarPrecioCotxe_Moto();
    void sumarPrecioCamion();
    void cambiarEstate();
    void cambiarColor();
};
