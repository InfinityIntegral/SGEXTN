#include "sgxstatusbar.h"
#include "../primitives/sgxtimestamp.h"
#include <QQuickItem>
#include <QTimer>
#include <QString>

QQuickItem* SGXStatusBar::instance = nullptr;
QTimer* SGXStatusBar::timer = nullptr;
int SGXStatusBar::secondsLeft = 0;

void SGXStatusBar::updateTime(){
    if(SGXStatusBar::secondsLeft == 0){(*SGXStatusBar::instance).setProperty("s", SGXTimeStamp::now().getString());}
    else{SGXStatusBar::secondsLeft--;}
}

void SGXStatusBar::notify(const QString &notificationMessage, int timeInSeconds){
    SGXStatusBar::secondsLeft = timeInSeconds;
    (*SGXStatusBar::instance).setProperty("s", notificationMessage);
}
