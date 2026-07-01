#include <QLCDNumber>
#include <QTime>
#include <QTimer>

class MyQLCDNumber: public QLCDNumber {

    Q_OBJECT

public:
    MyQLCDNumber(QWidget *parent);
    
    int hora = 0, min = 0, seg = 0, ms = 0;
    QString Shora = "00", Smin = "00", Sseg = "00", Sms = "000";
    QString Record;
    QTime TimeRecord = QTime(23,59,59,999);
    QTime NewTime;
    bool going = false;
    bool start = false;
    
public 

slots:
    void Start_Cont();
    void Stop_Cont();
    void Restart_Cont();
    void TimeOut();
    
signals:
    void enviarTexto(const QString&);
    
private:
    QTimer *timer;
};
