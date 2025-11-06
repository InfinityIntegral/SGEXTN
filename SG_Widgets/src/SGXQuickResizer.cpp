#include <private_api_Widgets/SGXQuickResizer.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <QQuickItem>
#include <private_api_Widgets/SGXFontSizeCustomisation.h>

SGXQuickResizer::SGXQuickResizer(){
    (*this).renderSpaceWidth = 0.0f;
    (*this).renderSpaceHeight = 0.0f;
    (*this).sizeUnit = 0.0f;
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
    setRenderSpaceWidth(static_cast<float>((*SGXQuickInterface::rootWindow).width()));
    setRenderSpaceHeight(static_cast<float>((*SGXQuickInterface::rootWindow).height()));
    if(renderSpaceWidth * SGXFontSizeCustomisation::fontSize < renderSpaceHeight / (1.0f / SGXFontSizeCustomisation::fontSize + 1.0f)){setSizeUnit(renderSpaceWidth * SGXFontSizeCustomisation::fontSize);}
    else{setSizeUnit(renderSpaceHeight / (1.0f / SGXFontSizeCustomisation::fontSize + 1.0f));}
}
