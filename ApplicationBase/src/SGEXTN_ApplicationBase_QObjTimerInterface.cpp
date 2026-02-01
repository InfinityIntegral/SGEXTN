#include <private_api/SGEXTN_ApplicationBase_QObjTimerInterface.h>
#include <QTimer>
#include <SGEXTN_ApplicationBase_Timer.h>
#include <QObject>

SGEXTN::ApplicationBase::QObjTimerInterface::QObjTimerInterface(SGEXTN::ApplicationBase::Timer* x){
    (*this).x = x;
    QObject::connect((*x).private_timer, &QTimer::timeout, this, &SGEXTN::ApplicationBase::QObjTimerInterface::runFunction);
}

void SGEXTN::ApplicationBase::QObjTimerInterface::runFunction() const {
    (*x).private_runFunction();
}

void SGEXTN::ApplicationBase::QObjTimerInterface::actuallyDeleteTimer() const {
    delete x;
}
