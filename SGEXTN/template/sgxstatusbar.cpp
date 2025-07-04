#include "sgxstatusbar.h"
#include "../primitives/sgxtimestamp.h"
#include <QQuickItem>
#include <QTimer>

QQuickItem* SGXStatusBar::instance = nullptr;
QTimer* SGXStatusBar::timer = nullptr;

void SGXStatusBar::updateTime(){
    (*SGXStatusBar::instance).setProperty("s", SGXTimeStamp::now().getString());
}
