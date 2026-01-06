#include <SGWInput.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <SGWWidget.h>
#include <SGXColourRGBA.h>
#include <SGWHorizontalAlignment.h>
#include <SGWVerticalAlignment.h>
#include <QQuickItem>
#include <SGWDefaultFonts.h>
#include <private_api_Widgets/SGWWidgetQuickInterface.h>
#include <SGXThemeColours.h>
#include <SGXString.h>
#include <QColor>
#include <qnamespace.h>

namespace {
inline QColor temp_getQColour(SGXColourRGBA x){
    return QColor(x.getRed(), x.getGreen(), x.getBlue(), x.getTransparency());
}

inline Qt::AlignmentFlag temp_getQtFlag(SGWHorizontalAlignment::Flag x){
    if(x == SGWHorizontalAlignment::Left){return Qt::AlignLeft;}
    if(x == SGWHorizontalAlignment::Right){return Qt::AlignRight;}
    return Qt::AlignHCenter;
}

inline Qt::AlignmentFlag temp_getQtFlag(SGWVerticalAlignment::Flag x){
    if(x == SGWVerticalAlignment::Top){return Qt::AlignTop;}
    if(x == SGWVerticalAlignment::Bottom){return Qt::AlignBottom;}
    return Qt::AlignVCenter;
}
}

SGWInput::SGWInput(SGWWidget *parent, const SGXString &placeholder, void (*validationFunction)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, SGWHorizontalAlignment::Flag horizontalAlignment, SGWVerticalAlignment::Flag verticalAlignment) : SGWWidget(parent, x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).f1 = f1;
    (*this).f0 = f0;
    (*this).text = "";
    (*this).placeholderText = placeholder;
    (*this).font = SGWDefaultFonts::textFont;
    (*this).horizontalAlignment = horizontalAlignment;
    (*this).verticalAlignment = verticalAlignment;
    (*this).attachedInt = 0;
    (*this).attachedString = "";
    (*this).textChangedFunction = nullptr;
    (*this).focusStartFunction = nullptr;
    (*this).focusEndFunction = validationFunction;
    (*this).textChangedFunctionWithInt = nullptr;
    (*this).focusStartFunctionWithInt = nullptr;
    (*this).focusEndFunctionWithInt = nullptr;
    (*this).textChangedFunctionWithString = nullptr;
    (*this).focusStartFunctionWithString = nullptr;
    (*this).focusEndFunctionWithString = nullptr;
    (*this).textChangedFunctionWithPointer = nullptr;
    (*this).focusStartFunctionWithPointer= nullptr;
    (*this).focusEndFunctionWithPointer = nullptr;
    (*this).invalid = false;
    (*this).usingTheme = true;
    (*this).backgroundThemeColour = 3;
    (*this).backgroundColour = SGXThemeColours::getThemeColour((*this).backgroundThemeColour);
    (*this).foregroundThemeColour = 0;
    (*this).foregroundColour = SGXThemeColours::getThemeColour((*this).foregroundThemeColour);
    (*this).backgroundHoverThemeColour = 4;
    (*this).backgroundHoverColour = SGXThemeColours::getThemeColour((*this).backgroundHoverThemeColour);
    (*this).foregroundHoverThemeColour = 1;
    (*this).foregroundHoverColour = SGXThemeColours::getThemeColour((*this).foregroundHoverThemeColour);
    (*this).backgroundFocusThemeColour = 5;
    (*this).backgroundFocusColour = SGXThemeColours::getThemeColour((*this).backgroundFocusThemeColour);
    (*this).foregroundFocusThemeColour = 2;
    (*this).foregroundFocusColour = SGXThemeColours::getThemeColour((*this).foregroundFocusThemeColour);
    (*this).backgroundInvalidThemeColour = 0;
    (*this).backgroundInvalidColour = SGXThemeColours::getThemeColour((*this).backgroundInvalidThemeColour);
    (*this).foregroundInvalidThemeColour = 3;
    (*this).foregroundInvalidColour = SGXThemeColours::getThemeColour((*this).foregroundInvalidThemeColour);
    (*this).backgroundHoverInvalidThemeColour = 1;
    (*this).backgroundHoverInvalidColour = SGXThemeColours::getThemeColour((*this).backgroundHoverInvalidThemeColour);
    (*this).foregroundHoverInvalidThemeColour = 4;
    (*this).foregroundHoverInvalidColour = SGXThemeColours::getThemeColour((*this).foregroundHoverInvalidThemeColour);
    (*this).quickInterface = nullptr;
}

void SGWInput::syncQuickProperties(){
    (*topObject).setProperty("f1", f1);
    (*topObject).setProperty("f0", f0);
    (*topObject).setProperty("text", (*text.data));
    (*topObject).setProperty("p", (*placeholderText.data));
    (*topObject).setProperty("f", (*font.data));
    (*topObject).setProperty("ha", temp_getQtFlag(horizontalAlignment));
    (*topObject).setProperty("va", temp_getQtFlag(verticalAlignment));
    (*topObject).setProperty("inv", invalid);
    (*topObject).setProperty("utc", usingTheme);
    (*topObject).setProperty("bg", backgroundThemeColour);
    (*topObject).setProperty("bgc", temp_getQColour(backgroundColour));
    (*topObject).setProperty("fg", foregroundThemeColour);
    (*topObject).setProperty("fgc", temp_getQColour(foregroundColour));
    (*topObject).setProperty("bgh", backgroundHoverThemeColour);
    (*topObject).setProperty("bghc", temp_getQColour(backgroundHoverColour));
    (*topObject).setProperty("fgh", foregroundHoverThemeColour);
    (*topObject).setProperty("fghc", temp_getQColour(foregroundHoverColour));
    (*topObject).setProperty("bgf", backgroundFocusThemeColour);
    (*topObject).setProperty("bgfc", temp_getQColour(backgroundFocusColour));
    (*topObject).setProperty("fgf", foregroundFocusThemeColour);
    (*topObject).setProperty("fgfc", temp_getQColour(foregroundFocusColour));
    (*topObject).setProperty("bgi", backgroundInvalidThemeColour);
    (*topObject).setProperty("bgic", temp_getQColour(backgroundInvalidColour));
    (*topObject).setProperty("fgi", foregroundInvalidThemeColour);
    (*topObject).setProperty("fgic", temp_getQColour(foregroundInvalidColour));
    (*topObject).setProperty("bghi", backgroundHoverInvalidThemeColour);
    (*topObject).setProperty("bghic", temp_getQColour(backgroundHoverInvalidColour));
    (*topObject).setProperty("fghi", foregroundHoverInvalidThemeColour);
    (*topObject).setProperty("fghic", temp_getQColour(foregroundHoverInvalidColour));
    quickInterface = new SGWWidgetQuickInterface(this);
}

void SGWInput::eventReceived(const SGXString &s){
    if(s == "textChanged"){(*(*this).text.data) = (*topObject).property("s").toString();}
    if(s == "textChanged"){
        if(textChangedFunction != nullptr){textChangedFunction();}
        if(textChangedFunctionWithInt != nullptr){textChangedFunctionWithInt(attachedInt);}
        if(textChangedFunctionWithString != nullptr){textChangedFunctionWithString(attachedString);}
        if(textChangedFunctionWithPointer != nullptr){textChangedFunctionWithPointer(this);}
    }
    else if(s == "focusStart"){
        if(focusStartFunction != nullptr){focusStartFunction();}
        if(focusStartFunctionWithInt != nullptr){focusStartFunctionWithInt(attachedInt);}
        if(focusStartFunctionWithString != nullptr){focusStartFunctionWithString(attachedString);}
        if(focusStartFunctionWithPointer != nullptr){focusStartFunctionWithPointer(this);}
    }
    else if(s == "focusEnd"){
        if(focusEndFunction != nullptr){focusEndFunction();}
        if(focusEndFunctionWithInt != nullptr){focusEndFunctionWithInt(attachedInt);}
        if(focusEndFunctionWithString != nullptr){focusEndFunctionWithString(attachedString);}
        if(focusEndFunctionWithPointer != nullptr){focusEndFunctionWithPointer(this);}
    }
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

SGXString SGWInput::getPlaceholderText() const {
    return placeholderText;
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

void SGWInput::setPlaceholderText(const SGXString &s){
    (*this).text = s;
    (*(*this).topObject).setProperty("p", (*(*this).placeholderText.data));
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
    (*(*this).topObject).setProperty("ha", temp_getQtFlag(horizontalAlignment));
}

SGWVerticalAlignment::Flag SGWInput::getVerticalAlignment() const {
    return verticalAlignment;
}

void SGWInput::setVerticalAlignment(SGWVerticalAlignment::Flag alignment){
    (*this).verticalAlignment = alignment;
    (*(*this).topObject).setProperty("va", temp_getQtFlag(verticalAlignment));
}

bool SGWInput::getInvalid() const {
    return invalid;
}

void SGWInput::setInvalid(bool invalid){
    (*this).invalid = invalid;
    (*topObject).setProperty("inv", (*this).invalid);
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
    (*(*this).topObject).setProperty("bgc", temp_getQColour((*this).backgroundColour));
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
    (*(*this).topObject).setProperty("fgc", temp_getQColour((*this).foregroundColour));
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
    (*(*this).topObject).setProperty("bghc", temp_getQColour((*this).backgroundHoverColour));
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
    (*(*this).topObject).setProperty("fghc", temp_getQColour((*this).foregroundHoverColour));
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
    (*(*this).topObject).setProperty("bgfc", temp_getQColour((*this).backgroundFocusColour));
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
    (*(*this).topObject).setProperty("fgfc", temp_getQColour((*this).foregroundFocusColour));
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
    (*(*this).topObject).setProperty("bgic", temp_getQColour((*this).backgroundInvalidColour));
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
    (*(*this).topObject).setProperty("fgic", temp_getQColour((*this).foregroundInvalidColour));
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
    (*(*this).topObject).setProperty("bghic", temp_getQColour((*this).backgroundHoverInvalidColour));
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
    (*(*this).topObject).setProperty("fghic", temp_getQColour((*this).foregroundHoverInvalidColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGWInput::~SGWInput(){
    (*quickInterface).deleteLater();
}
