#include <SGXTimer.h>
#include <SGLFloatMath.h>
#include <QTimer>
#include <private_api_Core/SGXTimerQuickInterface.h>
#include <private_api_Containers/SGLCrash.h>

SGXTimer::SGXTimer(float t, void (*attachedFunction)()){
    if(t < 0.0f){SGLCrash::crash("SGXTimer constructor crashed as time interval is negative");}
    if(attachedFunction == nullptr){SGLCrash::crash("SGXTimer constructor crashed as function attached is nullptr");}
    (*this).onceOnly = false;
    (*this).deleted = false;
    (*this).interval = t;
    (*this).attachedFunction = attachedFunction;
    (*this).timer = new QTimer();
    (*(*this).timer).setInterval(SGLFloatMath::roundToInt(t * 1000.0f));
    (*this).quickInterface = new SGXTimerQuickInterface(this);
    (*(*this).timer).start();
}

SGXTimer::SGXTimer(bool x, float t, void (*attachedFunction)()){
    (void)x;
    (*this).onceOnly = true;
    (*this).deleted = false;
    (*this).interval = t;
    (*this).attachedFunction = attachedFunction;
    (*this).timer = new QTimer();
    (*(*this).timer).setInterval(SGLFloatMath::roundToInt(t * 1000.0f));
    (*this).quickInterface = new SGXTimerQuickInterface(this);
    (*(*this).timer).start();
}

SGXTimer::~SGXTimer(){
    if((*this).deleted == false){SGLCrash::crash("SGXTimer destructor crashed as you attempted to directly delete the timer, use SGXTimer::deleteTimer instead to safely delete it");}
    (*(*this).timer).deleteLater();
    (*(*this).quickInterface).deleteLater();
}

void SGXTimer::stop() const {
    (*(*this).timer).stop();
}

void SGXTimer::start() const {
    (*(*this).timer).start();
}

void SGXTimer::runFunction(){
    attachedFunction();
    if(onceOnly == true){(*this).deleteTimer();}
}

void SGXTimer::singleCall(float t, void (*attachedFunction)()){
    if(t < 0.0f){SGLCrash::crash("SGXTimer::singleCall crashed as time delay is negative");}
    if(attachedFunction == nullptr){SGLCrash::crash("SGXTimer::singleCall crashed as function attached is nullptr");}
    new SGXTimer(true, t, attachedFunction);
}

void SGXTimer::deleteTimer(){
    (*this).deleted = true;
    (*(*this).timer).stop();
    QTimer::singleShot(0, (*this).quickInterface, &SGXTimerQuickInterface::actuallyDeleteTimer);
}
