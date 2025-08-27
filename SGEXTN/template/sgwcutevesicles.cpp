#include "sgwcutevesicles.h"
#include "../cutevesicles/sgxrendercutevesiclessgwidget.h"
#include "../timer/sgxtimer.h"
#include "../userDefinedClasses/sgucentralmanagement.h"

float SGWCuteVesicles::framesPerSecond = 0.0f;
SGXRenderCuteVesiclesSGWidget* SGWCuteVesicles::instance = nullptr;
SGXTimer* SGWCuteVesicles::timer = nullptr;

void SGWCuteVesicles::refreshAnimation(){
    if(SGWCuteVesicles::instance != nullptr){(*SGWCuteVesicles::instance).redraw();}
}

void SGWCuteVesicles::startAnimation(){
    SGWCuteVesicles::framesPerSecond = SGUCentralManagement::cuteVesiclesFrameRate;
    SGWCuteVesicles::instance = new SGXRenderCuteVesiclesSGWidget();
    SGWCuteVesicles::timer = new SGXTimer(1.0f / SGWCuteVesicles::framesPerSecond, &SGWCuteVesicles::refreshAnimation);
    SGWCuteVesicles::refreshAnimation();
}

void SGWCuteVesicles::stopAnimation(){
    delete SGWCuteVesicles::timer;
    delete SGWCuteVesicles::instance;
    SGWCuteVesicles::instance = nullptr;
}

void SGWCuteVesicles::toggleAnimation(){
    if(SGWCuteVesicles::instance == nullptr){SGWCuteVesicles::startAnimation();}
    else{SGWCuteVesicles::stopAnimation();}
}
