#include "sgwcolourpickerwidget.h"
#include "../../quickui/sgxquickinterface.h"
#include "../../template/sgwcolourpicker.h"
#include "../noninstantiable/sgwwidget.h"
#include "../../primitives/sgxcolourrgba.h"
#include <QQuickItem>
#include <QObject>
#include "../enums/sgwtype.h"
#include <QString>
#include "../../quickui/sgwwidgetquickinterface.h"

SGWColourPickerWidget::SGWColourPickerWidget(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGXColourRGBA defaultColour) : SGWWidget(parent, x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).colour = defaultColour;
    (*this).e1 = 0.0f;
    (*this).e0 = 0.1f;
    (*this).attachedFunction = nullptr;
    (*this).usingTheme = true;
    (*this).backgroundThemeColour = 4;
    (*this).backgroundColour = (*SGXQuickInterface::themeColoursSingleton).getThemeColour((*this).backgroundThemeColour);
    (*this).backgroundHoverThemeColour = 3;
    (*this).backgroundHoverColour = (*SGXQuickInterface::themeColoursSingleton).getThemeColour((*this).backgroundHoverThemeColour);
    (*this).backgroundFocusThemeColour = 2;
    (*this).backgroundFocusColour = (*SGXQuickInterface::themeColoursSingleton).getThemeColour((*this).backgroundFocusThemeColour);
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickInterface::colourPicker).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::ColourPicker;
    SGWWidget::syncQuickProperties();
    SGWColourPickerWidget::syncQuickProperties();
    quickInterface = new SGWWidgetQuickInterface(this);
}

SGXColourRGBA SGWColourPickerWidget::getColour() const {
    return colour;
}

void SGWColourPickerWidget::setColour(SGXColourRGBA colour){
    (*this).colour = colour;
    (*(*this).topObject).setProperty("c", (*this).colour.getQColour());
}

void SGWColourPickerWidget::syncQuickProperties(){
    (*topObject).setProperty("c", colour.getQColour());
    (*topObject).setProperty("e1", e1);
    (*topObject).setProperty("e0", e0);
    (*topObject).setProperty("utc", usingTheme);
    (*topObject).setProperty("bg", backgroundThemeColour);
    (*topObject).setProperty("bgc", backgroundColour.getQColour());
    (*topObject).setProperty("bgh", backgroundHoverThemeColour);
    (*topObject).setProperty("bghc", backgroundHoverColour.getQColour());
    (*topObject).setProperty("bgf", backgroundFocusThemeColour);
    (*topObject).setProperty("bgfc", backgroundFocusColour.getQColour());
}

void SGWColourPickerWidget::eventReceived(const QString &s){
    if(s == "click"){SGWColourPicker::activateColourPicker(this);}
    if(s == "done" && attachedFunction != nullptr){attachedFunction(this);}
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
    (*(*this).topObject).setProperty("bgc", (*this).backgroundColour.getQColour());
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
    (*(*this).topObject).setProperty("bghc", (*this).backgroundHoverColour.getQColour());
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
    (*(*this).topObject).setProperty("bgfc", (*this).backgroundFocusColour.getQColour());
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

void (*SGWColourPickerWidget::getAttachedFunction() const)(SGWColourPickerWidget*){
    return attachedFunction;
}

void SGWColourPickerWidget::setAttachedFunction(void (*function)(SGWColourPickerWidget *)){
    attachedFunction = function;
}

SGWColourPickerWidget::~SGWColourPickerWidget(){
    (*quickInterface).deleteLater();
}
