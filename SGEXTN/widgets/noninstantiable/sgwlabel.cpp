#include "sgwlabel.h"
#include "../../quickui/sgxquickinterface.h"
#include "../../primitives/sgxstring.h"
#include "sgwwidget.h"
#include "../../primitives/sgxcolourrgba.h"
#include "../enums/sgwhorizontalalignment.h"
#include "../enums/sgwverticalalignment.h"
#include "../../bypassquickui/sgxthemecolours.h"
#include <QQuickItem>

SGWLabel::SGWLabel(SGWWidget *parent, const SGXString &s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, SGWHorizontalAlignment::Flag horizontalAlignment, SGWVerticalAlignment::Flag verticalAlignment, const SGXString &font) : SGWWidget(parent, x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).f1 = f1;
    (*this).f0 = f0;
    (*this).text = s;
    (*this).font = font;
    (*this).horizontalAlignment = horizontalAlignment;
    (*this).verticalAlignment = verticalAlignment;
    (*this).usingTheme = true;
    (*this).backgroundThemeColour = 8;
    (*this).backgroundColour = SGXThemeColours::getThemeColour((*this).backgroundThemeColour);
    (*this).foregroundThemeColour = 4;
    (*this).foregroundColour = SGXThemeColours::getThemeColour((*this).foregroundThemeColour);
}

void SGWLabel::syncQuickProperties(){
    (*topObject).setProperty("f1", f1);
    (*topObject).setProperty("f0", f0);
    (*topObject).setProperty("s", (*text.data));
    (*topObject).setProperty("f", (*font.data));
    (*topObject).setProperty("ha", SGWHorizontalAlignment::getQtFlag(horizontalAlignment));
    (*topObject).setProperty("va", SGWVerticalAlignment::getQtFlag(verticalAlignment));
    (*topObject).setProperty("utc", usingTheme);
    (*topObject).setProperty("bg", backgroundThemeColour);
    (*topObject).setProperty("bgc", backgroundColour.getQColour());
    (*topObject).setProperty("fg", foregroundThemeColour);
    (*topObject).setProperty("fgc", foregroundColour.getQColour());
}

float SGWLabel::getF1() const {
    return f1;
}

void SGWLabel::setF1(float f1){
    (*this).f1 = f1;
    (*(*this).topObject).setProperty("f1", (*this).f1);
}

float SGWLabel::getF0() const {
    return f0;
}

void SGWLabel::setF0(float f0){
    (*this).f0 = f0;
    (*(*this).topObject).setProperty("f0", (*this).f0);
}

SGXString SGWLabel::getTextAsString() const {
    return text;
}

int SGWLabel::getTextAsInt(bool *isValid, int minimum, int maximum) const {
    int x = text.parseToInt(isValid);
    if(x < minimum || x > maximum){
        x = 0;
        if(isValid != nullptr){(*isValid) = false;}
    }
    return x;
}

float SGWLabel::getTextAsFloat(bool *isValid, float minimum, float maximum) const {
    float x = text.parseToFloat(isValid);
    if(x < minimum || x > maximum){
        x = 0.0f;
        if(isValid != nullptr){(*isValid) = false;}
    }
    return x;
}

void SGWLabel::setTextFromString(const SGXString& text){
    (*this).text = text;
    (*(*this).topObject).setProperty("s", (*(*this).text.data));
}

void SGWLabel::setTextFromInt(int x){
    (*this).text = SGXString::intToString(x);
    (*(*this).topObject).setProperty("s", (*(*this).text.data));
}

void SGWLabel::setTextFromFloat(float x){
    (*this).text = SGXString::floatToString(x);
    (*(*this).topObject).setProperty("s", (*(*this).text.data));
}

SGXString SGWLabel::getFont() const {
    return font;
}

void SGWLabel::setFont(const SGXString& font){
    (*this).font = font;
    (*(*this).topObject).setProperty("f", (*(*this).font.data));
}

SGWHorizontalAlignment::Flag SGWLabel::getHorizontalAlignment() const {
    return horizontalAlignment;
}

void SGWLabel::setHorizontalAlignment(SGWHorizontalAlignment::Flag alignment){
    (*this).horizontalAlignment = alignment;
    (*(*this).topObject).setProperty("ha", SGWHorizontalAlignment::getQtFlag(horizontalAlignment));
}

SGWVerticalAlignment::Flag SGWLabel::getVerticalAlignment() const {
    return verticalAlignment;
}

void SGWLabel::setVerticalAlignment(SGWVerticalAlignment::Flag alignment){
    (*this).verticalAlignment = alignment;
    (*(*this).topObject).setProperty("va", SGWVerticalAlignment::getQtFlag(verticalAlignment));
}

int SGWLabel::getBackgroundThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return backgroundThemeColour;
}

void SGWLabel::setBackgroundThemeColour(int themeColour){
    (*this).backgroundThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bg", (*this).backgroundThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWLabel::getBackgroundColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return backgroundColour;
}

void SGWLabel::setBackgroundColour(SGXColourRGBA colour){
    (*this).backgroundColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bgc", (*this).backgroundColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWLabel::getForegroundThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return foregroundThemeColour;
}

void SGWLabel::setForegroundThemeColour(int themeColour){
    (*this).foregroundThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fg", (*this).foregroundThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWLabel::getForegroundColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return foregroundColour;
}

void SGWLabel::setForegroundColour(SGXColourRGBA colour){
    (*this).foregroundColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fgc", (*this).foregroundColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}
