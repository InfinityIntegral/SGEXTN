#include <private_api_Core/SGXTimerQuickInterface.h>
#include <QTimer>
#include <SGXTimer.h>

SGXTimerQuickInterface::SGXTimerQuickInterface(SGXTimer *x){
    (*this).x = x;
    connect((*x).timer, &QTimer::timeout, this, &SGXTimerQuickInterface::runFunction);
}

void SGXTimerQuickInterface::runFunction() const {
    (*x).runFunction();
}
