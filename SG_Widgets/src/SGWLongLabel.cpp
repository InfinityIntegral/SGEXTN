#include <SGWLongLabel.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <SGWWidget.h>
#include <SGXString.h>
#include <SGWLabel.h>
#include <QQuickItem>
#include <SGWType.h>
#include <SGXColourRGBA.h>
#include <SGWHorizontalAlignment.h>
#include <SGWVerticalAlignment.h>
#include <SGWDefaultFonts.h>
#include <SGXThemeColours.h>
#include <QColor>

namespace {
inline QColor temp_getQColour(SGXColourRGBA x){
    return QColor(x.getRed(), x.getGreen(), x.getBlue(), x.getTransparency());
}
}

SGWLongLabel::SGWLongLabel(SGWWidget *parent, const SGXString &s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, float s1, float s0, float p1, float p0) : SGWLabel(parent, s, x1, x0, y1, y0, w1, w0, h1, h0, f1, f0, SGWHorizontalAlignment::Left, SGWVerticalAlignment::Top, SGWDefaultFonts::textFont){
    (*this).s1 = s1;
    (*this).s0 = s0;
    (*this).p1 = p1;
    (*this).p0 = p0;
    (*this).scrollbarBackgroundThemeColour = 3;
    (*this).scrollbarBackgroundColour = SGXThemeColours::getThemeColour((*this).scrollbarBackgroundThemeColour);
    (*this).scrollbarForegroundThemeColour = 0;
    (*this).scrollbarForegroundColour = SGXThemeColours::getThemeColour((*this).scrollbarForegroundThemeColour);
    (*this).scrollbarBackgroundHoverThemeColour = 4;
    (*this).scrollbarBackgroundHoverColour = SGXThemeColours::getThemeColour((*this).scrollbarBackgroundHoverThemeColour);
    (*this).scrollbarForegroundHoverThemeColour = 1;
    (*this).scrollbarForegroundHoverColour = SGXThemeColours::getThemeColour((*this).scrollbarForegroundHoverThemeColour);
    (*this).scrollbarBackgroundFocusThemeColour = 5;
    (*this).scrollbarBackgroundFocusColour = SGXThemeColours::getThemeColour((*this).scrollbarBackgroundFocusThemeColour);
    (*this).scrollbarForegroundFocusThemeColour = 2;
    (*this).scrollbarForegroundFocusColour = SGXThemeColours::getThemeColour((*this).scrollbarForegroundFocusThemeColour);
    QQuickItem* thisItem = static_cast<QQuickItem*>((*SGXQuickInterface::longLabel).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::LongLabel;
    SGWWidget::syncQuickProperties();
    SGWLabel::syncQuickProperties();
    SGWLongLabel::syncQuickProperties();
}

void SGWLongLabel::syncQuickProperties(){
    (*topObject).setProperty("s1", s1);
    (*topObject).setProperty("s0", s0);
    (*topObject).setProperty("p1", p1);
    (*topObject).setProperty("p0", p0);
    (*topObject).setProperty("bs", scrollbarBackgroundThemeColour);
    (*topObject).setProperty("bsc", temp_getQColour(scrollbarBackgroundColour));
    (*topObject).setProperty("fs", scrollbarForegroundThemeColour);
    (*topObject).setProperty("fsc", temp_getQColour(scrollbarForegroundColour));
    (*topObject).setProperty("bsh", scrollbarBackgroundHoverThemeColour);
    (*topObject).setProperty("bshc", temp_getQColour(scrollbarBackgroundHoverColour));
    (*topObject).setProperty("fsh", scrollbarForegroundHoverThemeColour);
    (*topObject).setProperty("fshc", temp_getQColour(scrollbarForegroundHoverColour));
    (*topObject).setProperty("bsf", scrollbarBackgroundFocusThemeColour);
    (*topObject).setProperty("bsfc", temp_getQColour(scrollbarBackgroundFocusColour));
    (*topObject).setProperty("fsf", scrollbarForegroundFocusThemeColour);
    (*topObject).setProperty("fsfc", temp_getQColour(scrollbarForegroundFocusColour));
}

float SGWLongLabel::getS1() const {
    return s1;
}

void SGWLongLabel::setS1(float s1){
    (*this).s1 = s1;
    (*(*this).topObject).setProperty("s1", (*this).s1);
}

float SGWLongLabel::getS0() const {
    return s0;
}

void SGWLongLabel::setS0(float s0){
    (*this).s0 = s0;
    (*(*this).topObject).setProperty("s0", (*this).s0);
}

float SGWLongLabel::getP1() const {
    return p1;
}

void SGWLongLabel::setP1(float p1){
    (*this).p1 = p1;
    (*(*this).topObject).setProperty("p1", (*this).p1);
}

float SGWLongLabel::getP0() const {
    return p0;
}

void SGWLongLabel::setP0(float p0){
    (*this).p0 = p0;
    (*(*this).topObject).setProperty("p0", (*this).p0);
}

int SGWLongLabel::getScrollbarBackgroundThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarBackgroundThemeColour;
}

void SGWLongLabel::setScrollbarBackgroundThemeColour(int themeColour){
    (*this).scrollbarBackgroundThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bs", (*this).scrollbarBackgroundThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWLongLabel::getScrollbarBackgroundColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarBackgroundColour;
}

void SGWLongLabel::setScrollbarBackgroundColour(SGXColourRGBA colour){
    (*this).scrollbarBackgroundColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bsc", temp_getQColour((*this).scrollbarBackgroundColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWLongLabel::getScrollbarForegroundThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarForegroundThemeColour;
}

void SGWLongLabel::setScrollbarForegroundThemeColour(int themeColour){
    (*this).scrollbarForegroundThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fs", (*this).scrollbarForegroundThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWLongLabel::getScrollbarForegroundColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarForegroundColour;
}

void SGWLongLabel::setScrollbarForegroundColour(SGXColourRGBA colour){
    (*this).scrollbarForegroundColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fsc", temp_getQColour((*this).scrollbarForegroundColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWLongLabel::getScrollbarBackgroundHoverThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarBackgroundHoverThemeColour;
}

void SGWLongLabel::setScrollbarBackgroundHoverThemeColour(int themeColour){
    (*this).scrollbarBackgroundHoverThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bsh", (*this).scrollbarBackgroundHoverThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWLongLabel::getScrollbarBackgroundHoverColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarBackgroundHoverColour;
}

void SGWLongLabel::setScrollbarBackgroundHoverColour(SGXColourRGBA colour){
    (*this).scrollbarBackgroundHoverColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bshc", temp_getQColour((*this).scrollbarBackgroundHoverColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWLongLabel::getScrollbarForegroundHoverThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarForegroundHoverThemeColour;
}

void SGWLongLabel::setScrollbarForegroundHoverThemeColour(int themeColour){
    (*this).scrollbarForegroundHoverThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fsh", (*this).scrollbarForegroundHoverThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWLongLabel::getScrollbarForegroundHoverColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarForegroundHoverColour;
}

void SGWLongLabel::setScrollbarForegroundHoverColour(SGXColourRGBA colour){
    (*this).scrollbarForegroundHoverColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fshc", temp_getQColour((*this).scrollbarForegroundHoverColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWLongLabel::getScrollbarBackgroundFocusThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarBackgroundFocusThemeColour;
}

void SGWLongLabel::setScrollbarBackgroundFocusThemeColour(int themeColour){
    (*this).scrollbarBackgroundFocusThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bsf", (*this).scrollbarBackgroundFocusThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWLongLabel::getScrollbarBackgroundFocusColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarBackgroundFocusColour;
}

void SGWLongLabel::setScrollbarBackgroundFocusColour(SGXColourRGBA colour){
    (*this).scrollbarBackgroundFocusColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bsfc", temp_getQColour((*this).scrollbarBackgroundFocusColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWLongLabel::getScrollbarForegroundFocusThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return scrollbarForegroundFocusThemeColour;
}

void SGWLongLabel::setScrollbarForegroundFocusThemeColour(int themeColour){
    (*this).scrollbarForegroundFocusThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fsf", (*this).scrollbarForegroundFocusThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWLongLabel::getScrollbarForegroundFocusColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return scrollbarForegroundFocusColour;
}

void SGWLongLabel::setScrollbarForegroundFocusColour(SGXColourRGBA colour){
    (*this).scrollbarForegroundFocusColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fsfc", temp_getQColour((*this).scrollbarForegroundFocusColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}
