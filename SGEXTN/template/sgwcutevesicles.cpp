#include "sgwcutevesicles.h"
#include "../cutevesicles/sgxrendercutevesiclessgwidget.h"
#include <QTimer>
#include "../userDefinedClasses/sgucentralmanagement.h"

float SGWCuteVesicles::framesPerSecond = 0.0f;
SGXRenderCuteVesiclesSGWidget* SGWCuteVesicles::instance = nullptr;
QTimer* SGWCuteVesicles::timer = nullptr;

void SGWCuteVesicles::refreshAnimation(){
    (*SGWCuteVesicles::instance).redraw();
}

void SGWCuteVesicles::startAnimation(){
    SGWCuteVesicles::framesPerSecond = SGUCentralManagement::cuteVesiclesFrameRate;
    SGWCuteVesicles::instance = new SGXRenderCuteVesiclesSGWidget();
    SGWCuteVesicles::timer = new QTimer(SGWCuteVesicles::instance);
    connect(SGWCuteVesicles::timer, &QTimer::timeout, &SGWCuteVesicles::refreshAnimation);
    (*SGWCuteVesicles::timer).start(static_cast<int>(1000.0f / SGWCuteVesicles::framesPerSecond));
    SGWCuteVesicles::refreshAnimation();
}

void SGWCuteVesicles::stopAnimation(){
    (*SGWCuteVesicles::instance).deleteLater();
    SGWCuteVesicles::instance = nullptr;
}

void SGWCuteVesicles::toggleAnimation(){
    if(SGWCuteVesicles::instance == nullptr){SGWCuteVesicles::startAnimation();}
    else{SGWCuteVesicles::stopAnimation();}
}
