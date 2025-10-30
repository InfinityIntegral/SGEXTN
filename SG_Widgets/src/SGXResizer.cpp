#include <SGXResizer.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <private_api_Widgets/SGXQuickResizer.h>

float SGXResizer::getRenderSpaceWidth(){
    return (*SGXQuickInterface::resizerSingleton).renderSpaceWidth;
}

float SGXResizer::getRenderSpaceHeight(){
    return (*SGXQuickInterface::resizerSingleton).renderSpaceHeight;
}

float SGXResizer::getSizeUnit(){
    return (*SGXQuickInterface::resizerSingleton).sizeUnit;
}
