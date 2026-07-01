#include "MyQLCDNumber.h"

MyQLCDNumber::MyQLCDNumber(QWidget *parent):QLCDNumber(parent) {
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimeOut()));
}

void MyQLCDNumber::Start_Cont() {
    timer->start(1);
    start = true;
    going = true;
}

void MyQLCDNumber::Stop_Cont() {
    timer->stop();
    start = false;
}

void MyQLCDNumber::Restart_Cont() {
    if (going) {
        timer->stop();
    
        if (NewTime < TimeRecord) {
            TimeRecord = NewTime;
            Record = Shora + ":" + Smin + ":" + Sseg + ":" + Sms;
            emit enviarTexto(Record);
        }
    
        hora = 0, min = 0, seg = 0, ms = 0;
        Shora = "00", Smin = "00", Sseg = "00", Sms = "000";
        display("00:00:00:000");
        setStyleSheet("color: black");
        going = false;
        start = false;
    }
}

void MyQLCDNumber::TimeOut() {
    ++ms;
    if (ms < 10) Sms = "00" + QString::number(ms,10);
    else if (ms < 100) Sms = "0" + QString::number(ms,10);
    else if (ms < 1000) Sms = QString::number(ms,10);
    
    if (ms >= 1000) {
        ms = 0;
        Sms = "000";
        ++seg;
        if (seg < 10) Sseg = "0" + QString::number(seg,10);
        else Sseg = QString::number(seg,10);
    }
    if (seg >= 60) {
        seg = 0;
        Sseg = "00";
        ++min;
        if (min < 10) Smin = "0" + QString::number(min,10);
        else Smin = QString::number(min,10);
    }
    if (min >= 60) {
        min = 0;
        Smin = "00";
        ++hora;
        if (hora < 10) Shora = "0" + QString::number(hora,10);
        else Shora = QString::number(hora,10);
    }
    if (hora >= 24) {
        hora = 0;
        Shora = "00";
    }
    display(Shora + ":" + Smin + ":" + Sseg + ":" + Sms);
    
    NewTime = QTime(hora, min, seg, ms);
    if (NewTime < TimeRecord) setStyleSheet("color: green");
    else if (NewTime > TimeRecord) setStyleSheet("color: red");
    else setStyleSheet("color: black");
}
