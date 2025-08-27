#include "sgxresizer.h"
#include "../quickui/sgxquickinterface.h"

float SGXResizer::getAppWindowWidth(){
    return (*SGXQuickInterface::resizerSingleton).appWindowWidth;
}

float SGXResizer::getAppWindowHeight(){
    return (*SGXQuickInterface::resizerSingleton).appWindowHeight;
}

float SGXResizer::getRenderSpaceWidth(){
    return (*SGXQuickInterface::resizerSingleton).renderSpaceWidth;
}

float SGXResizer::getRenderSpaceHeight(){
    return (*SGXQuickInterface::resizerSingleton).renderSpaceHeight;
}

float SGXResizer::getSizeUnit(){
    return (*SGXQuickInterface::resizerSingleton).sizeUnit;
}
