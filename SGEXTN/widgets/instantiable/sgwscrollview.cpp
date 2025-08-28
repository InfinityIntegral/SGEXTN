#include "sgwscrollview.h"
#include "../../quickui/sgxquickinterface.h"
#include "../noninstantiable/sgwwidget.h"
#include "../noninstantiable/sgwbackground.h"
#include <QQuickItem>
#include "../enums/sgwtype.h"
#include "../../primitives/sgxcolourrgba.h"
#include "../../bypassquickui/sgxthemecolours.h"

SGWScrollView::SGWScrollView(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float i1, float i0, float s1, float s0, int themeColour) : SGWBackground(parent, x1, x0, y1, y0, w1, w0, h1, h0, themeColour){
    (*this).i1 = i1;
    (*this).i0 = i0;
    (*this).s1 = s1;
    (*this).s0 = s0;
    (*this).scrollbarBackgroundThemeColour = 4;
    (*this).scrollbarBackgroundColour = SGXThemeColours::getThemeColour((*this).scrollbarBackgroundThemeColour);
    (*this).scrollbarForegroundThemeColour = 6;
    (*this).scrollbarForegroundColour = SGXThemeColours::getThemeColour((*this).scrollbarForegroundThemeColour);
    (*this).scrollbarBackgroundHoverThemeColour = 3;
    (*this).scrollbarBackgroundHoverColour = SGXThemeColours::getThemeColour((*this).scrollbarBackgroundHoverThemeColour);
    (*this).scrollbarForegroundHoverThemeColour = 5;
    (*this).scrollbarForegroundHoverColour = SGXThemeColours::getThemeColour((*this).scrollbarForegroundHoverThemeColour);
    (*this).scrollbarBackgroundFocusThemeColour = 2;
    (*this).scrollbarBackgroundFocusColour = SGXThemeColours::getThemeColour((*this).scrollbarBackgroundFocusThemeColour);
    (*this).scrollbarForegroundFocusThemeColour = 4;
    (*this).scrollbarForegroundFocusColour = SGXThemeColours::getThemeColour((*this).scrollbarForegroundFocusThemeColour);
    QQuickItem* thisItem = static_cast<QQuickItem*>((*SGXQuickInterface::scrollView).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::ScrollView;
    SGWWidget::syncQuickProperties();
    SGWBackground::syncQuickProperties();
    SGWScrollView::syncQuickProperties();
}

void SGWScrollView::syncQuickProperties(){
    (*topObject).setProperty("i1", i1);
    (*topObject).setProperty("i0", i0);
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

float SGWScrollView::getI1() const {
    return i1;
}

void SGWScrollView::setI1(float i1){
    (*this).i1 = i1;
    (*(*this).topObject).setProperty("i1", (*this).i1);
}

float SGWScrollView::getI0() const {
    return i0;
}

void SGWScrollView::setI0(float i0){
    (*this).i0 = i0;
    (*(*this).topObject).setProperty("i0", (*this).i0);
}

float SGWScrollView::getS1() const {
    return s1;
}

void SGWScrollView::setS1(float s1){
    (*this).s1 = s1;
    (*(*this).topObject).setProperty("s1", (*this).s1);
}

float SGWScrollView::getS0() const {
    return s0;
}

void SGWScrollView::setS0(float s0){
    (*this).s0 = s0;
    (*(*this).topObject).setProperty("s0", (*this).s0);
}

int SGWScrollView::getScrollbarBackgroundThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarBackgroundThemeColour;
}

void SGWScrollView::setScrollbarBackgroundThemeColour(int themeColour){
    (*this).scrollbarBackgroundThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bs", (*this).scrollbarBackgroundThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWScrollView::getScrollbarBackgroundColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarBackgroundColour;
}

void SGWScrollView::setScrollbarBackgroundColour(SGXColourRGBA colour){
    (*this).scrollbarBackgroundColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bsc", (*this).scrollbarBackgroundColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWScrollView::getScrollbarForegroundThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarForegroundThemeColour;
}

void SGWScrollView::setScrollbarForegroundThemeColour(int themeColour){
    (*this).scrollbarForegroundThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fs", (*this).scrollbarForegroundThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWScrollView::getScrollbarForegroundColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarForegroundColour;
}

void SGWScrollView::setScrollbarForegroundColour(SGXColourRGBA colour){
    (*this).scrollbarForegroundColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fsc", (*this).scrollbarForegroundColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWScrollView::getScrollbarBackgroundHoverThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarBackgroundHoverThemeColour;
}

void SGWScrollView::setScrollbarBackgroundHoverThemeColour(int themeColour){
    (*this).scrollbarBackgroundHoverThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bsh", (*this).scrollbarBackgroundHoverThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWScrollView::getScrollbarBackgroundHoverColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarBackgroundHoverColour;
}

void SGWScrollView::setScrollbarBackgroundHoverColour(SGXColourRGBA colour){
    (*this).scrollbarBackgroundHoverColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bshc", (*this).scrollbarBackgroundHoverColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWScrollView::getScrollbarForegroundHoverThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarForegroundHoverThemeColour;
}

void SGWScrollView::setScrollbarForegroundHoverThemeColour(int themeColour){
    (*this).scrollbarForegroundHoverThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fsh", (*this).scrollbarForegroundHoverThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWScrollView::getScrollbarForegroundHoverColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarForegroundHoverColour;
}

void SGWScrollView::setScrollbarForegroundHoverColour(SGXColourRGBA colour){
    (*this).scrollbarForegroundHoverColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fshc", (*this).scrollbarForegroundHoverColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWScrollView::getScrollbarBackgroundFocusThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarBackgroundFocusThemeColour;
}

void SGWScrollView::setScrollbarBackgroundFocusThemeColour(int themeColour){
    (*this).scrollbarBackgroundFocusThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bsf", (*this).scrollbarBackgroundFocusThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWScrollView::getScrollbarBackgroundFocusColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarBackgroundFocusColour;
}

void SGWScrollView::setScrollbarBackgroundFocusColour(SGXColourRGBA colour){
    (*this).scrollbarBackgroundFocusColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bsfc", (*this).scrollbarBackgroundFocusColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWScrollView::getScrollbarForegroundFocusThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarForegroundFocusThemeColour;
}

void SGWScrollView::setScrollbarForegroundFocusThemeColour(int themeColour){
    (*this).scrollbarForegroundFocusThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fsf", (*this).scrollbarForegroundFocusThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWScrollView::getScrollbarForegroundFocusColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarForegroundFocusColour;
}

void SGWScrollView::setScrollbarForegroundFocusColour(SGXColourRGBA colour){
    (*this).scrollbarForegroundFocusColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fsfc", (*this).scrollbarForegroundFocusColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}
