#include "sgwlonginput.h"
#include "../quickui/sgxquickinterface.h"
#include "sgwwidget.h"
#include "sgwinput.h"
#include "sgwhorizontalalignment.h"
#include "sgwverticalalignment.h"
#include <QQuickItem>
#include <QObject>
#include "sgwtype.h"
#include "../primitives/sgxcolourrgba.h"

SGWLongInput::SGWLongInput(SGWWidget *parent, void (*validationFunction)(SGWInput *), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, float s1, float s0) : SGWInput(parent, validationFunction, x1, x0, y1, y0, w1, w0, h1, h0, f1, f0, SGWHorizontalAlignment::Left, SGWVerticalAlignment::Top){
    (*this).s1 = s1;
    (*this).s0 = s0;
    (*this).scrollbarBackgroundThemeColour = 4;
    (*this).scrollbarBackgroundColour = (*SGXQuickInterface::themeColoursSingleton).getThemeColour((*this).scrollbarBackgroundThemeColour);
    (*this).scrollbarForegroundThemeColour = 6;
    (*this).scrollbarForegroundColour = (*SGXQuickInterface::themeColoursSingleton).getThemeColour((*this).scrollbarForegroundThemeColour);
    (*this).scrollbarBackgroundHoverThemeColour = 3;
    (*this).scrollbarBackgroundHoverColour = (*SGXQuickInterface::themeColoursSingleton).getThemeColour((*this).scrollbarBackgroundHoverThemeColour);
    (*this).scrollbarForegroundHoverThemeColour = 5;
    (*this).scrollbarForegroundHoverColour = (*SGXQuickInterface::themeColoursSingleton).getThemeColour((*this).scrollbarForegroundHoverThemeColour);
    (*this).scrollbarBackgroundFocusThemeColour = 2;
    (*this).scrollbarBackgroundFocusColour = (*SGXQuickInterface::themeColoursSingleton).getThemeColour((*this).scrollbarBackgroundFocusThemeColour);
    (*this).scrollbarForegroundFocusThemeColour = 4;
    (*this).scrollbarForegroundFocusColour = (*SGXQuickInterface::themeColoursSingleton).getThemeColour((*this).scrollbarForegroundFocusThemeColour);
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickInterface::longInput).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::LongInput;
    SGWWidget::syncQuickProperties();
    SGWInput::syncQuickProperties();
    SGWLongInput::syncQuickProperties();
}

void SGWLongInput::syncQuickProperties(){
    (*topObject).setProperty("s1", s1);
    (*topObject).setProperty("s0", s0);
    (*topObject).setProperty("bs", scrollbarBackgroundThemeColour);
    (*topObject).setProperty("bsc", scrollbarBackgroundColour.getQColour());
    (*topObject).setProperty("fs", scrollbarForegroundThemeColour);
    (*topObject).setProperty("fsc", scrollbarForegroundColour.getQColour());
    (*topObject).setProperty("bsh", scrollbarBackgroundHoverThemeColour);
    (*topObject).setProperty("bshc", scrollbarBackgroundHoverColour.getQColour());
    (*topObject).setProperty("fsh", scrollbarForegroundHoverThemeColour);
    (*topObject).setProperty("fshc", scrollbarForegroundHoverColour.getQColour());
    (*topObject).setProperty("bsf", scrollbarBackgroundFocusThemeColour);
    (*topObject).setProperty("bsfc", scrollbarBackgroundFocusColour.getQColour());
    (*topObject).setProperty("fsf", scrollbarForegroundFocusThemeColour);
    (*topObject).setProperty("fsfc", scrollbarForegroundFocusColour.getQColour());
}

float SGWLongInput::getS1() const {
    return s1;
}

void SGWLongInput::setS1(float s1){
    (*this).s1 = s1;
    (*(*this).topObject).setProperty("s1", (*this).s1);
}

float SGWLongInput::getS0() const {
    return s0;
}

void SGWLongInput::setS0(float s0){
    (*this).s0 = s0;
    (*(*this).topObject).setProperty("s0", (*this).s0);
}

int SGWLongInput::getScrollbarBackgroundThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarBackgroundThemeColour;
}

void SGWLongInput::setScrollbarBackgroundThemeColour(int themeColour){
    (*this).scrollbarBackgroundThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bs", (*this).scrollbarBackgroundThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWLongInput::getScrollbarBackgroundColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarBackgroundColour;
}

void SGWLongInput::setScrollbarBackgroundColour(SGXColourRGBA colour){
    (*this).scrollbarBackgroundColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bsc", (*this).scrollbarBackgroundColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWLongInput::getScrollbarForegroundThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarForegroundThemeColour;
}

void SGWLongInput::setScrollbarForegroundThemeColour(int themeColour){
    (*this).scrollbarForegroundThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fs", (*this).scrollbarForegroundThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWLongInput::getScrollbarForegroundColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarForegroundColour;
}

void SGWLongInput::setScrollbarForegroundColour(SGXColourRGBA colour){
    (*this).scrollbarForegroundColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fsc", (*this).scrollbarForegroundColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWLongInput::getScrollbarBackgroundHoverThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarBackgroundHoverThemeColour;
}

void SGWLongInput::setScrollbarBackgroundHoverThemeColour(int themeColour){
    (*this).scrollbarBackgroundHoverThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bsh", (*this).scrollbarBackgroundHoverThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWLongInput::getScrollbarBackgroundHoverColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarBackgroundHoverColour;
}

void SGWLongInput::setScrollbarBackgroundHoverColour(SGXColourRGBA colour){
    (*this).scrollbarBackgroundHoverColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bsch", (*this).scrollbarBackgroundHoverColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWLongInput::getScrollbarForegroundHoverThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarForegroundHoverThemeColour;
}

void SGWLongInput::setScrollbarForegroundHoverThemeColour(int themeColour){
    (*this).scrollbarForegroundHoverThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fsh", (*this).scrollbarForegroundHoverThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWLongInput::getScrollbarForegroundHoverColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarForegroundHoverColour;
}

void SGWLongInput::setScrollbarForegroundHoverColour(SGXColourRGBA colour){
    (*this).scrollbarForegroundHoverColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fsch", (*this).scrollbarForegroundHoverColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWLongInput::getScrollbarBackgroundFocusThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarBackgroundFocusThemeColour;
}

void SGWLongInput::setScrollbarBackgroundFocusThemeColour(int themeColour){
    (*this).scrollbarBackgroundFocusThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bsf", (*this).scrollbarBackgroundFocusThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWLongInput::getScrollbarBackgroundFocusColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarBackgroundFocusColour;
}

void SGWLongInput::setScrollbarBackgroundFocusColour(SGXColourRGBA colour){
    (*this).scrollbarBackgroundFocusColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bscf", (*this).scrollbarBackgroundFocusColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWLongInput::getScrollbarForegroundFocusThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarForegroundFocusThemeColour;
}

void SGWLongInput::setScrollbarForegroundFocusThemeColour(int themeColour){
    (*this).scrollbarForegroundFocusThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fsf", (*this).scrollbarForegroundFocusThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWLongInput::getScrollbarForegroundFocusColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarForegroundFocusColour;
}

void SGWLongInput::setScrollbarForegroundFocusColour(SGXColourRGBA colour){
    (*this).scrollbarForegroundFocusColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fscf", (*this).scrollbarForegroundFocusColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}
