#include "sgwinput.h"
#include "../../quickui/sgxquickinterface.h"
#include "sgwwidget.h"
#include "../../primitives/sgxcolourrgba.h"
#include "../enums/sgwhorizontalalignment.h"
#include "../enums/sgwverticalalignment.h"
#include <QQuickItem>
#include "../enums/sgwdefaultfonts.h"
#include "../../quickui/sgwwidgetquickinterface.h"
#include "../../bypassquickui/sgxthemecolours.h"
#include "../../primitives/sgxstring.h"

SGWInput::SGWInput(SGWWidget *parent, void (*validationFunction)(SGWInput *), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, SGWHorizontalAlignment::Flag horizontalAlignment, SGWVerticalAlignment::Flag verticalAlignment) : SGWWidget(parent, x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).f1 = f1;
    (*this).f0 = f0;
    (*this).text = "";
    (*this).font = SGWDefaultFonts::textFont;
    (*this).horizontalAlignment = horizontalAlignment;
    (*this).verticalAlignment = verticalAlignment;
    (*this).textChangedFunction = nullptr;
    (*this).focusStartFunction = nullptr;
    (*this).focusEndFunction = validationFunction;
    (*this).invalid = false;
    (*this).usingTheme = true;
    (*this).backgroundThemeColour = 4;
    (*this).backgroundColour = SGXThemeColours::getThemeColour((*this).backgroundThemeColour);
    (*this).foregroundThemeColour = 8;
    (*this).foregroundColour = SGXThemeColours::getThemeColour((*this).foregroundThemeColour);
    (*this).backgroundHoverThemeColour = 3;
    (*this).backgroundHoverColour = SGXThemeColours::getThemeColour((*this).backgroundHoverThemeColour);
    (*this).foregroundHoverThemeColour = 7;
    (*this).foregroundHoverColour = SGXThemeColours::getThemeColour((*this).foregroundHoverThemeColour);
    (*this).backgroundFocusThemeColour = 2;
    (*this).backgroundFocusColour = SGXThemeColours::getThemeColour((*this).backgroundFocusThemeColour);
    (*this).foregroundFocusThemeColour = 6;
    (*this).foregroundFocusColour = SGXThemeColours::getThemeColour((*this).foregroundFocusThemeColour);
    (*this).backgroundInvalidThemeColour = 0;
    (*this).backgroundInvalidColour = SGXThemeColours::getThemeColour((*this).backgroundInvalidThemeColour);
    (*this).foregroundInvalidThemeColour = 4;
    (*this).foregroundInvalidColour = SGXThemeColours::getThemeColour((*this).foregroundInvalidThemeColour);
    (*this).backgroundHoverInvalidThemeColour = 1;
    (*this).backgroundHoverInvalidColour = SGXThemeColours::getThemeColour((*this).backgroundHoverInvalidThemeColour);
    (*this).foregroundHoverInvalidThemeColour = 5;
    (*this).foregroundHoverInvalidColour = SGXThemeColours::getThemeColour((*this).foregroundHoverInvalidThemeColour);
    (*this).quickInterface = nullptr;
}

void SGWInput::syncQuickProperties(){
    (*topObject).setProperty("f1", f1);
    (*topObject).setProperty("f0", f0);
    (*topObject).setProperty("text", (*text.data));
    (*topObject).setProperty("f", (*font.data));
    (*topObject).setProperty("ha", SGWHorizontalAlignment::getQtFlag(horizontalAlignment));
    (*topObject).setProperty("va", SGWVerticalAlignment::getQtFlag(verticalAlignment));
    (*topObject).setProperty("inv", invalid);
    (*topObject).setProperty("utc", usingTheme);
    (*topObject).setProperty("bg", backgroundThemeColour);
    (*topObject).setProperty("bgc", backgroundColour.getQColour());
    (*topObject).setProperty("fg", foregroundThemeColour);
    (*topObject).setProperty("fgc", foregroundColour.getQColour());
    (*topObject).setProperty("bgh", backgroundHoverThemeColour);
    (*topObject).setProperty("bghc", backgroundHoverColour.getQColour());
    (*topObject).setProperty("fgh", foregroundHoverThemeColour);
    (*topObject).setProperty("fghc", foregroundHoverColour.getQColour());
    (*topObject).setProperty("bgf", backgroundFocusThemeColour);
    (*topObject).setProperty("bgfc", backgroundFocusColour.getQColour());
    (*topObject).setProperty("fgf", foregroundFocusThemeColour);
    (*topObject).setProperty("fgfc", foregroundFocusColour.getQColour());
    (*topObject).setProperty("bgi", backgroundInvalidThemeColour);
    (*topObject).setProperty("bgic", backgroundInvalidColour.getQColour());
    (*topObject).setProperty("fgi", foregroundInvalidThemeColour);
    (*topObject).setProperty("fgic", foregroundInvalidColour.getQColour());
    (*topObject).setProperty("bghi", backgroundHoverInvalidThemeColour);
    (*topObject).setProperty("bghic", backgroundHoverInvalidColour.getQColour());
    (*topObject).setProperty("fghi", foregroundHoverInvalidThemeColour);
    (*topObject).setProperty("fghic", foregroundHoverInvalidColour.getQColour());
    quickInterface = new SGWWidgetQuickInterface(this);
}

void SGWInput::eventReceived(const SGXString &s){
    if(s == "textChanged"){(*(*this).text.data) = (*topObject).property("s").toString();}
    if(textChangedFunction != nullptr && s == "textChanged"){textChangedFunction(this);}
    else if(focusStartFunction != nullptr && s == "focusStart"){focusStartFunction(this);}
    else if(focusEndFunction != nullptr && s == "focusEnd"){focusEndFunction(this);}
}

float SGWInput::getF1() const {
    return f1;
}

void SGWInput::setF1(float f1){
    (*this).f1 = f1;
    (*(*this).topObject).setProperty("f1", (*this).f1);
}

float SGWInput::getF0() const {
    return f0;
}

void SGWInput::setF0(float f0){
    (*this).f0 = f0;
    (*(*this).topObject).setProperty("f0", (*this).f0);
}

SGXString SGWInput::getTextAsString() const {
    return text;
}

int SGWInput::getTextAsInt(bool *isValid, int minimum, int maximum) const {
    int x = text.parseToInt(isValid);
    if(x < minimum || x > maximum){
        x = 0;
        if(isValid != nullptr){(*isValid) = false;}
    }
    return x;
}

float SGWInput::getTextAsFloat(bool *isValid, float minimum, float maximum) const {
    float x = text.parseToFloat(isValid);
    if(x < minimum || x > maximum){
        x = 0.0f;
        if(isValid != nullptr){(*isValid) = false;}
    }
    return x;
}

void SGWInput::setTextFromString(const SGXString& s){
    (*this).text = s;
    (*(*this).topObject).setProperty("text", (*(*this).text.data));
}

void SGWInput::setTextFromInt(int x){
    (*this).text = SGXString::intToString(x);
    (*(*this).topObject).setProperty("text", (*(*this).text.data));
}

void SGWInput::setTextFromFloat(float x){
    (*this).text = SGXString::floatToString(x);
    (*(*this).topObject).setProperty("text", (*(*this).text.data));
}

SGXString SGWInput::getFont() const {
    return font;
}

void SGWInput::setFont(const SGXString& font){
    (*this).font = font;
    (*(*this).topObject).setProperty("f", (*(*this).font.data));
}

SGWHorizontalAlignment::Flag SGWInput::getHorizontalAlignment() const {
    return horizontalAlignment;
}

void SGWInput::setHorizontalAlignment(SGWHorizontalAlignment::Flag alignment){
    (*this).horizontalAlignment = alignment;
    (*(*this).topObject).setProperty("ha", SGWHorizontalAlignment::getQtFlag(horizontalAlignment));
}

SGWVerticalAlignment::Flag SGWInput::getVerticalAlignment() const {
    return verticalAlignment;
}

void SGWInput::setVerticalAlignment(SGWVerticalAlignment::Flag alignment){
    (*this).verticalAlignment = alignment;
    (*(*this).topObject).setProperty("va", SGWVerticalAlignment::getQtFlag(verticalAlignment));
}

bool SGWInput::getInvalid() const {
    return invalid;
}

void SGWInput::setInvalid(bool invalid){
    (*this).invalid = invalid;
    (*topObject).setProperty("inv", (*this).invalid);
}

void (*SGWInput::getTextChangedFunction() const)(SGWInput*){
    return textChangedFunction;
}

void SGWInput::setTextChangedFunction(void (*function)(SGWInput *)){
    (*this).textChangedFunction = function;
}

void (*SGWInput::getFocusStartFunction() const)(SGWInput*){
    return focusStartFunction;
}

void SGWInput::setFocusStartFunction(void (*function)(SGWInput *)){
    (*this).focusStartFunction = function;
}

void (*SGWInput::getFocusEndFunction() const)(SGWInput*){
    return focusEndFunction;
}

void SGWInput::setFocusEndFunction(void (*function)(SGWInput *)){
    (*this).focusEndFunction = function;
}

int SGWInput::getBackgroundThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return backgroundThemeColour;
}

void SGWInput::setBackgroundThemeColour(int themeColour){
    (*this).backgroundThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bg", (*this).backgroundThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWInput::getBackgroundColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return backgroundColour;
}

void SGWInput::setBackgroundColour(SGXColourRGBA colour){
    (*this).backgroundColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bgc", (*this).backgroundColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWInput::getForegroundThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return foregroundThemeColour;
}

void SGWInput::setForegroundThemeColour(int themeColour){
    (*this).foregroundThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fg", (*this).foregroundThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWInput::getForegroundColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return foregroundColour;
}

void SGWInput::setForegroundColour(SGXColourRGBA colour){
    (*this).foregroundColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fgc", (*this).foregroundColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWInput::getBackgroundHoverThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return backgroundHoverThemeColour;
}

void SGWInput::setBackgroundHoverThemeColour(int themeColour){
    (*this).backgroundHoverThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bgh", (*this).backgroundHoverThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWInput::getBackgroundHoverColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return backgroundHoverColour;
}

void SGWInput::setBackgroundHoverColour(SGXColourRGBA colour){
    (*this).backgroundHoverColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bghc", (*this).backgroundHoverColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWInput::getForegroundHoverThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return foregroundHoverThemeColour;
}

void SGWInput::setForegroundHoverThemeColour(int themeColour){
    (*this).foregroundHoverThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fgh", (*this).foregroundHoverThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWInput::getForegroundHoverColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return foregroundHoverColour;
}

void SGWInput::setForegroundHoverColour(SGXColourRGBA colour){
    (*this).foregroundHoverColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fghc", (*this).foregroundHoverColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWInput::getBackgroundFocusThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return backgroundFocusThemeColour;
}

void SGWInput::setBackgroundFocusThemeColour(int themeColour){
    (*this).backgroundFocusThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bgf", (*this).backgroundFocusThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWInput::getBackgroundFocusColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return backgroundFocusColour;
}

void SGWInput::setBackgroundFocusColour(SGXColourRGBA colour){
    (*this).backgroundFocusColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bgfc", (*this).backgroundFocusColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWInput::getForegroundFocusThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return foregroundFocusThemeColour;
}

void SGWInput::setForegroundFocusThemeColour(int themeColour){
    (*this).foregroundFocusThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fgf", (*this).foregroundFocusThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWInput::getForegroundFocusColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return foregroundFocusColour;
}

void SGWInput::setForegroundFocusColour(SGXColourRGBA colour){
    (*this).foregroundFocusColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fgfc", (*this).foregroundFocusColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWInput::getBackgroundInvalidThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return backgroundInvalidThemeColour;
}

void SGWInput::setBackgroundInvalidThemeColour(int themeColour){
    (*this).backgroundInvalidThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bgi", (*this).backgroundInvalidThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWInput::getBackgroundInvalidColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return backgroundInvalidColour;
}

void SGWInput::setBackgroundInvalidColour(SGXColourRGBA colour){
    (*this).backgroundInvalidColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bgic", (*this).backgroundInvalidColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWInput::getForegroundInvalidThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return foregroundInvalidThemeColour;
}

void SGWInput::setForegroundInvalidThemeColour(int themeColour){
    (*this).foregroundInvalidThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fgi", (*this).foregroundInvalidThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWInput::getForegroundInvalidColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return foregroundInvalidColour;
}

void SGWInput::setForegroundInvalidColour(SGXColourRGBA colour){
    (*this).foregroundInvalidColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fgic", (*this).foregroundInvalidColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWInput::getBackgroundHoverInvalidThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return backgroundHoverInvalidThemeColour;
}

void SGWInput::setBackgroundHoverInvalidThemeColour(int themeColour){
    (*this).backgroundHoverInvalidThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bghi", (*this).backgroundHoverInvalidThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWInput::getBackgroundHoverInvalidColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return backgroundHoverInvalidColour;
}

void SGWInput::setBackgroundHoverInvalidColour(SGXColourRGBA colour){
    (*this).backgroundHoverInvalidColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bghic", (*this).backgroundHoverInvalidColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWInput::getForegroundHoverInvalidThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return foregroundHoverInvalidThemeColour;
}

void SGWInput::setForegroundHoverInvalidThemeColour(int themeColour){
    (*this).foregroundHoverInvalidThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fghi", (*this).foregroundHoverInvalidThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWInput::getForegroundHoverInvalidColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return foregroundHoverInvalidColour;
}

void SGWInput::setForegroundHoverInvalidColour(SGXColourRGBA colour){
    (*this).foregroundHoverInvalidColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fghic", (*this).foregroundHoverInvalidColour.getQColour());
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGWInput::~SGWInput(){
    (*quickInterface).deleteLater();
}
