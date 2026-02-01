#include <SGEXTN_ApplicationBase_Timer.h>
#include <SGEXTN_Math_FloatMath.h>
#include <QTimer>
#include <private_api/SGEXTN_ApplicationBase_QObjTimerInterface.h>
#include <private_api/SGEXTN_Containers_Crash.h>

SGEXTN::ApplicationBase::Timer::Timer(float t, void (*attachedFunction)()){
    if(t < 0.0f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Timer constructor crashed as time interval is negative");}
    if(attachedFunction == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Timer constructor crashed as function attached is nullptr");}
    private_once = false;
    private_deleted = false;
    private_interval = t;
    (*this).attachedFunction = attachedFunction;
    private_timer = new QTimer();
    (*private_timer).setInterval(SGEXTN::Math::FloatMath<float>::roundToInt(t * 1000.0f));
    private_q = new SGEXTN::ApplicationBase::QObjTimerInterface(this);
    (*private_timer).start();
}

SGEXTN::ApplicationBase::Timer::~Timer(){
    if(private_deleted == false){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Timer destructor crashed as you attempted to directly delete the timer, use SGEXTN::ApplicationBase::Timer::deleteTimer instead to safely delete it");}
    (*private_timer).deleteLater();
    (*private_q).deleteLater();
}

void SGEXTN::ApplicationBase::Timer::stop() const {
    (*private_timer).stop();
}

void SGEXTN::ApplicationBase::Timer::start() const {
    (*private_timer).start();
}

void SGEXTN::ApplicationBase::Timer::private_runFunction(){
    attachedFunction();
    if(private_once == true){deleteTimer();}
}

void SGEXTN::ApplicationBase::Timer::singleCall(float t, void (*attachedFunction)()){
    if(t < 0.0f){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Timer::singleCall crashed as time interval is negative");}
    if(attachedFunction == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Timer::singleCall crashed as function attached is nullptr");}
    SGEXTN::ApplicationBase::Timer* temporaryTimer = new SGEXTN::ApplicationBase::Timer(t, attachedFunction);
    (*temporaryTimer).private_once = true;
}

void SGEXTN::ApplicationBase::Timer::deleteTimer(){
    (*this).private_deleted = true;
    (*private_timer).stop();
    QTimer::singleShot(0, private_q, &SGEXTN::ApplicationBase::QObjTimerInterface::actuallyDeleteTimer);
}
