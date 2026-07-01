#include <QLineEdit>

class MyQLineEdit: public QLineEdit {

    Q_OBJECT

    public:
        MyQLineEdit(QWidget *parent);

    public slots:
        void capturaReturn();

    signals:
        void enviarTexto(const QString&);
};
