#include <SGWColourPickerWidget.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <private_api_RI/SGWColourPicker.h>
#include <SGWWidget.h>
#include <SGXColourRGBA.h>
#include <QQuickItem>
#include <SGWType.h>
#include <SGXString.h>
#include <private_api_RI/SGWColourPickerWidgetQuickInterface.h>
#include <SGXThemeColours.h>
#include <QColor>
#include <private_api_RI/SGRTransparencyIndicatorRenderer.h>
#include <private_api_RI/SGRRendererGenerator.h>

namespace {
inline QColor temp_getQColour(SGXColourRGBA x){
    return QColor(x.getRed(), x.getGreen(), x.getBlue(), x.getTransparency());
}
}

SGWColourPickerWidget::SGWColourPickerWidget(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGXColourRGBA defaultColour) : SGWWidget(parent, x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).colour = defaultColour;
    (*this).e1 = 0.0f;
    (*this).e0 = 0.1f;
    (*this).attachedInt = 0;
    (*this).attachedString = "";
    (*this).attachedFunction = nullptr;
    (*this).attachedFunctionWithInt = nullptr;
    (*this).attachedFunctionWithString = nullptr;
    (*this).attachedFunctionWithPointer = nullptr;
    (*this).usingTheme = true;
    (*this).backgroundThemeColour = 4;
    (*this).backgroundColour = SGXThemeColours::getThemeColour((*this).backgroundThemeColour);
    (*this).backgroundHoverThemeColour = 3;
    (*this).backgroundHoverColour = SGXThemeColours::getThemeColour((*this).backgroundHoverThemeColour);
    (*this).backgroundFocusThemeColour = 2;
    (*this).backgroundFocusColour = SGXThemeColours::getThemeColour((*this).backgroundFocusThemeColour);
    QQuickItem* thisItem = static_cast<QQuickItem*>((*SGXQuickInterface::colourPicker).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::ColourPicker;
    SGWWidget::syncQuickProperties();
    SGWColourPickerWidget::syncQuickProperties();
    quickInterface = new SGWColourPickerWidgetQuickInterface(this);
    renderControl = new SGRTransparencyIndicatorRenderer();
    new SGRRendererGenerator(renderControl, nullptr, bottomObject);
}

SGXColourRGBA SGWColourPickerWidget::getColour() const {
    return colour;
}

void SGWColourPickerWidget::setColour(SGXColourRGBA colour){
    (*this).colour = colour;
    (*(*this).topObject).setProperty("c", temp_getQColour((*this).colour));
}

void SGWColourPickerWidget::syncQuickProperties(){
    (*topObject).setProperty("c", temp_getQColour(colour));
    (*topObject).setProperty("e1", e1);
    (*topObject).setProperty("e0", e0);
    (*topObject).setProperty("utc", usingTheme);
    (*topObject).setProperty("bg", backgroundThemeColour);
    (*topObject).setProperty("bgc", temp_getQColour(backgroundColour));
    (*topObject).setProperty("bgh", backgroundHoverThemeColour);
    (*topObject).setProperty("bghc", temp_getQColour(backgroundHoverColour));
    (*topObject).setProperty("bgf", backgroundFocusThemeColour);
    (*topObject).setProperty("bgfc", temp_getQColour(backgroundFocusColour));
}

void SGWColourPickerWidget::eventReceived(const SGXString &s){
    if(s == "click"){SGWColourPicker::activateColourPicker(this);}
    if(s == "done"){
        if(attachedFunction != nullptr){attachedFunction();}
        if(attachedFunctionWithInt != nullptr){attachedFunctionWithInt(attachedInt);}
        if(attachedFunctionWithString != nullptr){attachedFunctionWithString(attachedString);}
        if(attachedFunctionWithPointer != nullptr){attachedFunctionWithPointer(this);}
    }
}

int SGWColourPickerWidget::getBackgroundThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return backgroundThemeColour;
}

void SGWColourPickerWidget::setBackgroundThemeColour(int themeColour){
    (*this).backgroundThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bg", (*this).backgroundThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWColourPickerWidget::getBackgroundColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return backgroundColour;
}

void SGWColourPickerWidget::setBackgroundColour(SGXColourRGBA colour){
    (*this).backgroundColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bgc", temp_getQColour((*this).backgroundColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWColourPickerWidget::getBackgroundHoverThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return backgroundHoverThemeColour;
}

void SGWColourPickerWidget::setBackgroundHoverThemeColour(int themeColour){
    (*this).backgroundHoverThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bgh", (*this).backgroundHoverThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWColourPickerWidget::getBackgroundHoverColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return backgroundHoverColour;
}

void SGWColourPickerWidget::setBackgroundHoverColour(SGXColourRGBA colour){
    (*this).backgroundHoverColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bghc", temp_getQColour((*this).backgroundHoverColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWColourPickerWidget::getBackgroundFocusThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return backgroundFocusThemeColour;
}

void SGWColourPickerWidget::setBackgroundFocusThemeColour(int themeColour){
    (*this).backgroundFocusThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bgf", (*this).backgroundFocusThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWColourPickerWidget::getBackgroundFocusColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return backgroundFocusColour;
}

void SGWColourPickerWidget::setBackgroundFocusColour(SGXColourRGBA colour){
    (*this).backgroundFocusColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bgfc", temp_getQColour((*this).backgroundFocusColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

float SGWColourPickerWidget::getE1() const {
    return e1;
}

void SGWColourPickerWidget::setE1(float e1){
    (*this).e1 = e1;
    (*(*this).topObject).setProperty("e1", (*this).e1);
}

float SGWColourPickerWidget::getE0() const {
    return e0;
}

void SGWColourPickerWidget::setE0(float e0){
    (*this).e0 = e0;
    (*(*this).topObject).setProperty("e0", (*this).e0);
}

SGWColourPickerWidget::~SGWColourPickerWidget(){
    (*quickInterface).deleteLater();
    delete renderControl;
}
