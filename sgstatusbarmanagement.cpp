#include "sgstatusbarmanagement.h"
#include "sgcentralmanagement.h"
#include <QDateTime>

SGWidget000411102* SGStatusBarManagement::statusbarbackground = nullptr;
QTimer* SGStatusBarManagement::timecounter = nullptr;
SGText022221131* SGStatusBarManagement::timedisplay = nullptr;
bool SGStatusBarManagement::isnotifying = false;

void SGStatusBarManagement::initialisestatusbar(){
    SGStatusBarManagement::statusbarbackground = new SGWidget000411102(SGCentralManagement::rootwindow, 0.0f, 0.0f, 1.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatescreen, SGStatusBarManagement::statusbarbackground, &SGWidget000411102::ResizeObj);
    SGStatusBarManagement::timedisplay = new SGText022221131(SGStatusBarManagement::statusbarbackground, QString(), 0.0f, 0.0f);
    connect(SGCentralManagement::signalsemitter, &SGSignalsEmitter::updatescreen, SGStatusBarManagement::timedisplay, &SGText022221131::ResizeObj);
    SGStatusBarManagement::timecounter = new QTimer(SGStatusBarManagement::timedisplay);
    connect(SGStatusBarManagement::timecounter, &QTimer::timeout, &SGStatusBarManagement::updatetime);
    (*SGStatusBarManagement::timecounter).start(1000);
}

void SGStatusBarManagement::updatetime(){
    if(isnotifying == false){
        QDateTime now = QDateTime::currentDateTimeUtc();
        now = now.addSecs(8 * 3600);
        (*SGStatusBarManagement::timedisplay).setText(now.toString("yyyyMMdd HHmmss"));
    }
}

void SGStatusBarManagement::notify(QString s){
    SGStatusBarManagement::isnotifying = true;
    (*SGStatusBarManagement::timedisplay).setText(s);
    QTimer::singleShot(3000, &SGStatusBarManagement::donenotify);
}

void SGStatusBarManagement::donenotify(){
    SGStatusBarManagement::isnotifying = false;
}
