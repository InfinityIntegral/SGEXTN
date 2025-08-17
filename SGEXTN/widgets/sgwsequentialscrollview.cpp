#include "sgwsequentialscrollview.h"
#include "../quickui/sgxquickinterface.h"
#include "sgwwidget.h"
#include "sgwbackground.h"
#include <QQuickItem>
#include <QObject>
#include "sgwtype.h"
#include "../primitives/sgxcolourrgba.h"

SGWSequentialScrollView::SGWSequentialScrollView(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float s1, float s0, int themeColour, bool frequentlyUsed) : SGWBackground(parent, x1, x0, y1, y0, w1, w0, h1, h0, themeColour, frequentlyUsed){
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
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickInterface::sequentialScrollView).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::SequentialScrollView;
    SGWWidget::syncQuickProperties();
    SGWBackground::syncQuickProperties();
    SGWSequentialScrollView::syncQuickProperties();
}

void SGWSequentialScrollView::syncQuickProperties(){
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

float SGWSequentialScrollView::getS1() const {
    return s1;
}

void SGWSequentialScrollView::setS1(float s1){
    (*this).s1 = s1;
    (*(*this).topObject).setProperty("s1", (*this).s1);
}

float SGWSequentialScrollView::getS0() const {
    return s0;
}

void SGWSequentialScrollView::setS0(float s0){
    (*this).s0 = s0;
    (*(*this).topObject).setProperty("s0", (*this).s0);
}

int SGWSequentialScrollView::getScrollbarBackgroundThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarBackgroundThemeColour;
}

void SGWSequentialScrollView::setScrollbarBackgroundThemeColour(int themeColour){
    (*this).scrollbarBackgroundThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bs", (*this).scrollbarBackgroundThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWSequentialScrollView::getScrollbarBackgroundColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarBackgroundColour;
}

void SGWSequentialScrollView::setScrollbarBackgroundColour(SGXColourRGBA colour){
    (*this).scrollbarBackgroundColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bsc", (*this).scrollbarBackgroundColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWSequentialScrollView::getScrollbarForegroundThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarForegroundThemeColour;
}

void SGWSequentialScrollView::setScrollbarForegroundThemeColour(int themeColour){
    (*this).scrollbarForegroundThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fs", (*this).scrollbarForegroundThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWSequentialScrollView::getScrollbarForegroundColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarForegroundColour;
}

void SGWSequentialScrollView::setScrollbarForegroundColour(SGXColourRGBA colour){
    (*this).scrollbarForegroundColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fsc", (*this).scrollbarForegroundColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWSequentialScrollView::getScrollbarBackgroundHoverThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarBackgroundHoverThemeColour;
}

void SGWSequentialScrollView::setScrollbarBackgroundHoverThemeColour(int themeColour){
    (*this).scrollbarBackgroundHoverThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bsh", (*this).scrollbarBackgroundHoverThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWSequentialScrollView::getScrollbarBackgroundHoverColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarBackgroundHoverColour;
}

void SGWSequentialScrollView::setScrollbarBackgroundHoverColour(SGXColourRGBA colour){
    (*this).scrollbarBackgroundHoverColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bshc", (*this).scrollbarBackgroundHoverColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWSequentialScrollView::getScrollbarForegroundHoverThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarForegroundHoverThemeColour;
}

void SGWSequentialScrollView::setScrollbarForegroundHoverThemeColour(int themeColour){
    (*this).scrollbarForegroundHoverThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fsh", (*this).scrollbarForegroundHoverThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWSequentialScrollView::getScrollbarForegroundHoverColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarForegroundHoverColour;
}

void SGWSequentialScrollView::setScrollbarForegroundHoverColour(SGXColourRGBA colour){
    (*this).scrollbarForegroundHoverColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fshc", (*this).scrollbarForegroundHoverColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWSequentialScrollView::getScrollbarBackgroundFocusThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarBackgroundFocusThemeColour;
}

void SGWSequentialScrollView::setScrollbarBackgroundFocusThemeColour(int themeColour){
    (*this).scrollbarBackgroundFocusThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bsf", (*this).scrollbarBackgroundFocusThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWSequentialScrollView::getScrollbarBackgroundFocusColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarBackgroundFocusColour;
}

void SGWSequentialScrollView::setScrollbarBackgroundFocusColour(SGXColourRGBA colour){
    (*this).scrollbarBackgroundFocusColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bsfc", (*this).scrollbarBackgroundFocusColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWSequentialScrollView::getScrollbarForegroundFocusThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarForegroundFocusThemeColour;
}

void SGWSequentialScrollView::setScrollbarForegroundFocusThemeColour(int themeColour){
    (*this).scrollbarForegroundFocusThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fsf", (*this).scrollbarForegroundFocusThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWSequentialScrollView::getScrollbarForegroundFocusColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarForegroundFocusColour;
}

void SGWSequentialScrollView::setScrollbarForegroundFocusColour(SGXColourRGBA colour){
    (*this).scrollbarForegroundFocusColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fsfc", (*this).scrollbarForegroundFocusColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}
