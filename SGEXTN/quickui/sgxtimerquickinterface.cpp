#include "sgxtimerquickinterface.h"
#include <QTimer>
#include "../timer/sgxtimer.h"

SGXTimerQuickInterface::SGXTimerQuickInterface(SGXTimer *x){
    (*this).x = x;
    connect((*x).timer, &QTimer::timeout, this, &SGXTimerQuickInterface::runFunction);
}

void SGXTimerQuickInterface::runFunction() const {
    (*x).runFunction();
}
