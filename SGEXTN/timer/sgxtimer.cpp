#include "sgxtimer.h"
#include <cmath>
#include <QTimer>

SGXTimer::SGXTimer(float t, void (*attachedFunction)()){
    (*this).onceOnly = false;
    (*this).interval = t;
    (*this).attachedFunction = attachedFunction;
    (*this).timer = new QTimer();
    (*(*this).timer).setInterval(static_cast<int>(std::roundf(t * 1000.0f)));
    connect((*this).timer, &QTimer::timeout, this, &SGXTimer::runFunction);
    (*(*this).timer).start();
}

SGXTimer::SGXTimer(bool x, float t, void (*attachedFunction)()){
    (void)x;
    (*this).onceOnly = true;
    (*this).interval = t;
    (*this).attachedFunction = attachedFunction;
    (*this).timer = new QTimer();
    (*(*this).timer).setInterval(static_cast<int>(std::roundf(t * 1000.0f)));
    connect((*this).timer, &QTimer::timeout, this, &SGXTimer::runFunction);
    (*(*this).timer).start();
}

SGXTimer::~SGXTimer(){
    delete (*this).timer;
}

void SGXTimer::stop() const {
    (*(*this).timer).stop();
}

void SGXTimer::start() const {
    (*(*this).timer).start();
}

void SGXTimer::runFunction(){
    attachedFunction();
    if(onceOnly == true){(*this).deleteLater();}
}

void SGXTimer::singleCall(float t, void (*attachedFunction)()){
    new SGXTimer(true, t, attachedFunction);
}
