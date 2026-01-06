#include <SGWButton.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <SGWWidget.h>
#include <SGXColourRGBA.h>
#include <SGWHorizontalAlignment.h>
#include <SGWVerticalAlignment.h>
#include <QQuickItem>
#include <private_api_Widgets/SGWWidgetQuickInterface.h>
#include <SGXThemeColours.h>
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

SGWButton::SGWButton(SGWWidget *parent, const SGXString &s, void (*attachedFunction)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, const SGXString& font) : SGWWidget(parent, x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).f1 = f1;
    (*this).f0 = f0;
    (*this).text = s;
    (*this).font = font;
    (*this).horizontalAlignment = SGWHorizontalAlignment::Center;
    (*this).verticalAlignment = SGWVerticalAlignment::Center;
    (*this).attachedInt = 0;
    (*this).attachedString = "";
    (*this).clickFunction = attachedFunction;
    (*this).pressFunction = nullptr;
    (*this).releaseFunction = nullptr;
    (*this).clickFunctionWithInt = nullptr;
    (*this).pressFunctionWithInt = nullptr;
    (*this).releaseFunctionWithInt = nullptr;
    (*this).clickFunctionWithString = nullptr;
    (*this).pressFunctionWithString = nullptr;
    (*this).releaseFunctionWithString = nullptr;
    (*this).clickFunctionWithPointer = nullptr;
    (*this).pressFunctionWithPointer = nullptr;
    (*this).releaseFunctionWithPointer = nullptr;
    (*this).selected = false;
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
    (*this).backgroundSelectedThemeColour = 5;
    (*this).backgroundSelectedColour = SGXThemeColours::getThemeColour((*this).backgroundSelectedThemeColour);
    (*this).foregroundSelectedThemeColour = 2;
    (*this).foregroundSelectedColour = SGXThemeColours::getThemeColour((*this).foregroundSelectedThemeColour);
    (*this).backgroundHoverSelectedThemeColour = 4;
    (*this).backgroundHoverSelectedColour = SGXThemeColours::getThemeColour((*this).backgroundHoverSelectedThemeColour);
    (*this).foregroundHoverSelectedThemeColour = 1;
    (*this).foregroundHoverSelectedColour = SGXThemeColours::getThemeColour((*this).foregroundHoverSelectedThemeColour);
    (*this).backgroundFocusSelectedThemeColour = 3;
    (*this).backgroundFocusSelectedColour = SGXThemeColours::getThemeColour((*this).backgroundFocusSelectedThemeColour);
    (*this).foregroundFocusSelectedThemeColour = 0;
    (*this).foregroundFocusSelectedColour = SGXThemeColours::getThemeColour((*this).foregroundFocusSelectedThemeColour);
    (*this).quickInterface = nullptr;
}

void SGWButton::syncQuickProperties(){
    (*topObject).setProperty("f1", f1);
    (*topObject).setProperty("f0", f0);
    (*topObject).setProperty("s", (*text.data));
    (*topObject).setProperty("f", (*font.data));
    (*topObject).setProperty("ha", temp_getQtFlag(horizontalAlignment));
    (*topObject).setProperty("va", temp_getQtFlag(verticalAlignment));
    (*topObject).setProperty("sel", selected);
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
    (*topObject).setProperty("bgs", backgroundSelectedThemeColour);
    (*topObject).setProperty("bgsc", temp_getQColour(backgroundSelectedColour));
    (*topObject).setProperty("fgs", foregroundSelectedThemeColour);
    (*topObject).setProperty("fgsc", temp_getQColour(foregroundSelectedColour));
    (*topObject).setProperty("bghs", backgroundHoverSelectedThemeColour);
    (*topObject).setProperty("bghsc", temp_getQColour(backgroundHoverSelectedColour));
    (*topObject).setProperty("fghs", foregroundHoverSelectedThemeColour);
    (*topObject).setProperty("fghsc", temp_getQColour(foregroundHoverSelectedColour));
    (*topObject).setProperty("bgfs", backgroundFocusSelectedThemeColour);
    (*topObject).setProperty("bgfsc", temp_getQColour(backgroundFocusSelectedColour));
    (*topObject).setProperty("fgfs", foregroundFocusSelectedThemeColour);
    (*topObject).setProperty("fgfsc", temp_getQColour(foregroundFocusSelectedColour));
    quickInterface = new SGWWidgetQuickInterface(this);
}

void SGWButton::eventReceived(const SGXString &s){
    if(s == "click"){
        if(clickFunction != nullptr){clickFunction();}
        if(clickFunctionWithInt != nullptr){clickFunctionWithInt(attachedInt);}
        if(clickFunctionWithString != nullptr){clickFunctionWithString(attachedString);}
        if(clickFunctionWithPointer != nullptr){clickFunctionWithPointer(this);}
    }
    else if(s == "press"){
        if(pressFunction != nullptr){pressFunction();}
        if(pressFunctionWithInt != nullptr){pressFunctionWithInt(attachedInt);}
        if(pressFunctionWithString != nullptr){pressFunctionWithString(attachedString);}
        if(pressFunctionWithPointer != nullptr){pressFunctionWithPointer(this);}
    }
    else if(s == "release"){
        if(releaseFunction != nullptr){releaseFunction();}
        if(releaseFunctionWithInt != nullptr){releaseFunctionWithInt(attachedInt);}
        if(releaseFunctionWithString != nullptr){releaseFunctionWithString(attachedString);}
        if(releaseFunctionWithPointer != nullptr){releaseFunctionWithPointer(this);}
    }
}

float SGWButton::getF1() const {
    return f1;
}

void SGWButton::setF1(float f1){
    (*this).f1 = f1;
    (*(*this).topObject).setProperty("f1", (*this).f1);
}

float SGWButton::getF0() const {
    return f0;
}

void SGWButton::setF0(float f0){
    (*this).f0 = f0;
    (*(*this).topObject).setProperty("f0", (*this).f0);
}

SGXString SGWButton::getTextAsString() const {
    return text;
}

int SGWButton::getTextAsInt(bool *isValid, int minimum, int maximum) const {
    int x = text.parseToInt(isValid);
    if(x < minimum || x > maximum){
        x = 0;
        if(isValid != nullptr){(*isValid) = false;}
    }
    return x;
}

float SGWButton::getTextAsFloat(bool *isValid, float minimum, float maximum) const {
    float x = text.parseToFloat(isValid);
    if(x < minimum || x > maximum){
        x = 0.0f;
        if(isValid != nullptr){(*isValid) = false;}
    }
    return x;
}

void SGWButton::setTextFromString(const SGXString& s){
    (*this).text = s;
    (*(*this).topObject).setProperty("s", (*(*this).text.data));
}

void SGWButton::setTextFromInt(int x){
    (*this).text = SGXString::intToString(x);
    (*(*this).topObject).setProperty("s", (*(*this).text.data));
}

void SGWButton::setTextFromFloat(float x){
    (*this).text = SGXString::floatToString(x);
    (*(*this).topObject).setProperty("s", (*(*this).text.data));
}

SGXString SGWButton::getFont() const {
    return font;
}

void SGWButton::setFont(const SGXString& font){
    (*this).font = font;
    (*(*this).topObject).setProperty("f", (*(*this).font.data));
}

SGWHorizontalAlignment::Flag SGWButton::getHorizontalAlignment() const {
    return horizontalAlignment;
}

void SGWButton::setHorizontalAlignment(SGWHorizontalAlignment::Flag alignment){
    (*this).horizontalAlignment = alignment;
    (*(*this).topObject).setProperty("ha", temp_getQtFlag(horizontalAlignment));
}

SGWVerticalAlignment::Flag SGWButton::getVerticalAlignment() const {
    return verticalAlignment;
}

void SGWButton::setVerticalAlignment(SGWVerticalAlignment::Flag alignment){
    (*this).verticalAlignment = alignment;
    (*(*this).topObject).setProperty("va", temp_getQtFlag(verticalAlignment));
}

bool SGWButton::getSelected() const {
    return selected;
}

void SGWButton::setSelected(bool selected){
    (*this).selected = selected;
    (*topObject).setProperty("sel", (*this).selected);
}

int SGWButton::getBackgroundThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return backgroundThemeColour;
}

void SGWButton::setBackgroundThemeColour(int themeColour){
    (*this).backgroundThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bg", (*this).backgroundThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWButton::getBackgroundColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return backgroundColour;
}

void SGWButton::setBackgroundColour(SGXColourRGBA colour){
    (*this).backgroundColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bgc", temp_getQColour((*this).backgroundColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWButton::getForegroundThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return foregroundThemeColour;
}

void SGWButton::setForegroundThemeColour(int themeColour){
    (*this).foregroundThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fg", (*this).foregroundThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWButton::getForegroundColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return foregroundColour;
}

void SGWButton::setForegroundColour(SGXColourRGBA colour){
    (*this).foregroundColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fgc", temp_getQColour((*this).foregroundColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWButton::getBackgroundHoverThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return backgroundHoverThemeColour;
}

void SGWButton::setBackgroundHoverThemeColour(int themeColour){
    (*this).backgroundHoverThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bgh", (*this).backgroundHoverThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWButton::getBackgroundHoverColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return backgroundHoverColour;
}

void SGWButton::setBackgroundHoverColour(SGXColourRGBA colour){
    (*this).backgroundHoverColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bghc", temp_getQColour((*this).backgroundHoverColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWButton::getForegroundHoverThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return foregroundHoverThemeColour;
}

void SGWButton::setForegroundHoverThemeColour(int themeColour){
    (*this).foregroundHoverThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fgh", (*this).foregroundHoverThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWButton::getForegroundHoverColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return foregroundHoverColour;
}

void SGWButton::setForegroundHoverColour(SGXColourRGBA colour){
    (*this).foregroundHoverColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fghc", temp_getQColour((*this).foregroundHoverColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWButton::getBackgroundFocusThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return backgroundFocusThemeColour;
}

void SGWButton::setBackgroundFocusThemeColour(int themeColour){
    (*this).backgroundFocusThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bgf", (*this).backgroundFocusThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWButton::getBackgroundFocusColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return backgroundFocusColour;
}

void SGWButton::setBackgroundFocusColour(SGXColourRGBA colour){
    (*this).backgroundFocusColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bgfc", temp_getQColour((*this).backgroundFocusColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWButton::getForegroundFocusThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return foregroundFocusThemeColour;
}

void SGWButton::setForegroundFocusThemeColour(int themeColour){
    (*this).foregroundFocusThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fgf", (*this).foregroundFocusThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWButton::getForegroundFocusColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return foregroundFocusColour;
}

void SGWButton::setForegroundFocusColour(SGXColourRGBA colour){
    (*this).foregroundFocusColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fgfc", temp_getQColour((*this).foregroundFocusColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWButton::getBackgroundSelectedThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return backgroundSelectedThemeColour;
}

void SGWButton::setBackgroundSelectedThemeColour(int themeColour){
    (*this).backgroundSelectedThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bgs", (*this).backgroundSelectedThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWButton::getBackgroundSelectedColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return backgroundSelectedColour;
}

void SGWButton::setBackgroundSelectedColour(SGXColourRGBA colour){
    (*this).backgroundSelectedColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bgsc", temp_getQColour((*this).backgroundSelectedColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWButton::getForegroundSelectedThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return foregroundSelectedThemeColour;
}

void SGWButton::setForegroundSelectedThemeColour(int themeColour){
    (*this).foregroundSelectedThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fgs", (*this).foregroundSelectedThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWButton::getForegroundSelectedColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return foregroundSelectedColour;
}

void SGWButton::setForegroundSelectedColour(SGXColourRGBA colour){
    (*this).foregroundSelectedColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fgsc", temp_getQColour((*this).foregroundSelectedColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWButton::getBackgroundHoverSelectedThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return backgroundHoverSelectedThemeColour;
}

void SGWButton::setBackgroundHoverSelectedThemeColour(int themeColour){
    (*this).backgroundHoverSelectedThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bghs", (*this).backgroundHoverSelectedThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWButton::getBackgroundHoverSelectedColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return backgroundHoverSelectedColour;
}

void SGWButton::setBackgroundHoverSelectedColour(SGXColourRGBA colour){
    (*this).backgroundHoverSelectedColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bghsc", temp_getQColour((*this).backgroundHoverSelectedColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWButton::getForegroundHoverSelectedThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return foregroundHoverSelectedThemeColour;
}

void SGWButton::setForegroundHoverSelectedThemeColour(int themeColour){
    (*this).foregroundHoverSelectedThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fghs", (*this).foregroundHoverSelectedThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWButton::getForegroundHoverSelectedColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return foregroundHoverSelectedColour;
}

void SGWButton::setForegroundHoverSelectedColour(SGXColourRGBA colour){
    (*this).foregroundHoverSelectedColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fghsc", temp_getQColour((*this).foregroundHoverSelectedColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWButton::getBackgroundFocusSelectedThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return backgroundFocusSelectedThemeColour;
}

void SGWButton::setBackgroundFocusSelectedThemeColour(int themeColour){
    (*this).backgroundFocusSelectedThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("bgfs", (*this).backgroundFocusSelectedThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWButton::getBackgroundFocusSelectedColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return backgroundFocusSelectedColour;
}

void SGWButton::setBackgroundFocusSelectedColour(SGXColourRGBA colour){
    (*this).backgroundFocusSelectedColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("bgfsc", temp_getQColour((*this).backgroundFocusSelectedColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

int SGWButton::getForegroundFocusSelectedThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return foregroundFocusSelectedThemeColour;
}

void SGWButton::setForegroundFocusSelectedThemeColour(int themeColour){
    (*this).foregroundFocusSelectedThemeColour = themeColour;
    (*this).usingTheme = true;
    (*(*this).topObject).setProperty("fgfs", (*this).foregroundFocusSelectedThemeColour);
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGXColourRGBA SGWButton::getForegroundFocusSelectedColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return foregroundFocusSelectedColour;
}

void SGWButton::setForegroundFocusSelectedColour(SGXColourRGBA colour){
    (*this).foregroundFocusSelectedColour = colour;
    (*this).usingTheme = false;
    (*(*this).topObject).setProperty("fgfsc", temp_getQColour((*this).foregroundFocusSelectedColour));
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
}

SGWButton::~SGWButton(){
    (*quickInterface).deleteLater();
}
