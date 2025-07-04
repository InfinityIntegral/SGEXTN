#include "sgxcutevesicles.h"
#include "../cutevesicles/sgxrendercutevesiclesquickuielement.h"
#include "../quickui/sgxquickuiinterface.h"
#include <QTimer>
#include <QObject>

float SGXCuteVesicles::framesPerSecond = 0.0f;
bool SGXCuteVesicles::animationOngoing = false;
SGXRenderCuteVesiclesQuickUIElement* SGXCuteVesicles::animationScreen = nullptr;
QTimer* SGXCuteVesicles::timer = nullptr;

void SGXCuteVesicles::refreshAnimation(){
    (*SGXCuteVesicles::animationScreen).update();
}

void SGXCuteVesicles::startAnimation(){
    SGXCuteVesicles::animationOngoing = true;
    if(SGXCuteVesicles::animationScreen == nullptr){
        SGXCuteVesicles::animationScreen = qobject_cast<SGXRenderCuteVesiclesQuickUIElement*>(SGXQuickUIInterface::createCuteVesicles(SGXQuickUIInterface::rootWidget));
        SGXCuteVesicles::timer = new QTimer(SGXCuteVesicles::animationScreen);
        connect(SGXCuteVesicles::timer, &QTimer::timeout, &SGXCuteVesicles::refreshAnimation);
    }
    (*SGXCuteVesicles::animationScreen).setVisible(true);
    (*SGXCuteVesicles::timer).start(static_cast<int>(1000.0f / SGXCuteVesicles::framesPerSecond));
    SGXCuteVesicles::refreshAnimation();
}

void SGXCuteVesicles::stopAnimation(){
    SGXCuteVesicles::animationOngoing = false;
    (*SGXCuteVesicles::animationScreen).setVisible(false);
    (*SGXCuteVesicles::timer).stop();
}

void SGXCuteVesicles::toggleAnimation(){
    if(SGXCuteVesicles::animationOngoing == true){SGXCuteVesicles::stopAnimation();}
    else{SGXCuteVesicles::startAnimation();}
}
