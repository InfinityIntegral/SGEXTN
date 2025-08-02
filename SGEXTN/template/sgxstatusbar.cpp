#include "sgxstatusbar.h"
#include "../primitives/sgxtimestamp.h"
#include <QQuickItem>
#include <QTimer>
#include <QString>

QQuickItem* SGXStatusBar::instance = nullptr;
QTimer* SGXStatusBar::timer = nullptr;
int SGXStatusBar::secondsLeft = 0;
bool SGXStatusBar::isNotifying = false;

void SGXStatusBar::updateTime(){
    if(SGXStatusBar::secondsLeft == 0){
        (*SGXStatusBar::instance).setProperty("s", SGXTimeStamp::now().getString());
        if(SGXStatusBar::isNotifying == true){
            SGXStatusBar::isNotifying = false;
            (*SGXStatusBar::instance).setProperty("notify", false);
        }
    }
    else{SGXStatusBar::secondsLeft--;}
}

void SGXStatusBar::notify(const QString &notificationMessage, int timeInSeconds){
    SGXStatusBar::secondsLeft = timeInSeconds;
    (*SGXStatusBar::instance).setProperty("s", notificationMessage);
    (*SGXStatusBar::instance).setProperty("notify", true);
    SGXStatusBar::isNotifying = true;
}
