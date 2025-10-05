#include "sgxquickresizer.h"
#include "../quickui/sgxquickinterface.h"
#include <QQuickItem>
#include "../userDefinedClasses/sgucentralmanagement.h"

SGXQuickResizer::SGXQuickResizer(){
    (*this).appWindowWidth = 0.0f;
    (*this).appWindowHeight = 0.0f;
    (*this).renderSpaceWidth = 0.0f;
    (*this).renderSpaceHeight = 0.0f;
    (*this).sizeUnit = 0.0f;
}

float SGXQuickResizer::getAppWindowWidth() const {
    return (*this).appWindowWidth;
}

void SGXQuickResizer::setAppWindowWidth(float x){
    (*this).appWindowWidth = x;
    (*this).changedAppWindowWidth();
}

float SGXQuickResizer::getAppWindowHeight() const {
    return (*this).appWindowHeight;
}

void SGXQuickResizer::setAppWindowHeight(float x){
    (*this).appWindowHeight = x;
    (*this).changedAppWindowHeight();
}

float SGXQuickResizer::getRenderSpaceWidth() const {
    return (*this).renderSpaceWidth;
}

void SGXQuickResizer::setRenderSpaceWidth(float x){
    (*this).renderSpaceWidth = x;
    (*this).changedRenderSpaceWidth();
}

float SGXQuickResizer::getRenderSpaceHeight() const {
    return (*this).renderSpaceHeight;
}

void SGXQuickResizer::setRenderSpaceHeight(float x){
    (*this).renderSpaceHeight = x;
    (*this).changedRenderSpaceHeight();
}

float SGXQuickResizer::getSizeUnit() const {
    return (*this).sizeUnit;
}

void SGXQuickResizer::setSizeUnit(float x){
    (*this).sizeUnit = x;
    (*this).changedSizeUnit();
}

void SGXQuickResizer::updateAppWindowSize(){
    setAppWindowWidth(static_cast<float>((*SGXQuickInterface::rootWindow).width()));
    setAppWindowHeight(static_cast<float>((*SGXQuickInterface::rootWindow).height()));
    setRenderSpaceWidth(appWindowWidth);
    setRenderSpaceHeight(appWindowHeight);
    // 13 on mobile, 20 on desktop
    if(renderSpaceWidth * SGUCentralManagement::scaleFactor < renderSpaceHeight / (1.0f / SGUCentralManagement::scaleFactor + 1.0f)){setSizeUnit(renderSpaceWidth * SGUCentralManagement::scaleFactor);}
    else{setSizeUnit(renderSpaceHeight / (1.0f / SGUCentralManagement::scaleFactor + 1.0f));}
}
