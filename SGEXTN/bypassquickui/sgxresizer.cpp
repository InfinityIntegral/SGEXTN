#include "sgxresizer.h"
#include "../quickui/sgxquickinterface.h"
#include "../quickui/sgxquickresizer.h"

float SGXResizer::getRenderSpaceWidth(){
    return (*SGXQuickInterface::resizerSingleton).renderSpaceWidth;
}

float SGXResizer::getRenderSpaceHeight(){
    return (*SGXQuickInterface::resizerSingleton).renderSpaceHeight;
}

float SGXResizer::getSizeUnit(){
    return (*SGXQuickInterface::resizerSingleton).sizeUnit;
}
