#include <SGWBackground.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <SGXColourRGBA.h>
#include <SGWWidget.h>
#include <SGXThemeColours.h>
#include <QQuickItem>
#include <SGLStack.h>
#include <private_api_Containers/SGLCrash.h>

SGLStack<SGWBackground*>* SGWBackground::activePages = nullptr;

SGWBackground::SGWBackground(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0) : SGWWidget(parent, x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).usingTheme = true;
    (*this).themeColour = 3;
    (*this).colour = SGXThemeColours::getThemeColour(3);
}

int SGWBackground::getThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return themeColour;
}

void SGWBackground::setThemeColour(int themeColour){
    (*this).usingTheme = true;
    (*this).themeColour = themeColour;
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
    (*(*this).topObject).setProperty("bg", (*this).themeColour);
}

SGXColourRGBA SGWBackground::getColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return colour;
}

void SGWBackground::setColour(SGXColourRGBA colour){
    (*this).usingTheme = false;
    (*this).colour = colour;
    (*(*this).topObject).setProperty("utc", false);
    (*(*this).topObject).setProperty("bgc", QColor(colour.getRed(), colour.getGreen(), colour.getBlue(), colour.getTransparency()));
}

void SGWBackground::syncQuickProperties(){
    (*topObject).setProperty("utc", usingTheme);
    (*topObject).setProperty("bg", themeColour);
    (*topObject).setProperty("bgc", QColor(colour.getRed(), colour.getGreen(), colour.getBlue(), colour.getTransparency()));
}

void SGWBackground::enable(SGWBackground *&thisPointer, SGWBackground *(*initFunction)(), void (*resetFunction)()){
    if(initFunction == nullptr){SGLCrash::crash("SGWBackground::enable crashed because init function is nullptr");}
    if(thisPointer != nullptr){return;}
    thisPointer = initFunction();
    (*(*thisPointer).getTopObject()).setVisible(true);
    if(resetFunction != nullptr){resetFunction();}
    if(SGWBackground::activePages != nullptr && (*SGWBackground::activePages).length() > 0){
        (*(*SGWBackground::activePages).top()).setItemVisibility(false);
    }
    else if(SGWBackground::activePages == nullptr){SGWBackground::activePages = new SGLStack<SGWBackground*>();}
    (*SGWBackground::activePages).push(thisPointer);
}

void SGWBackground::disable(SGWBackground *&thisPointer){
    if(thisPointer == nullptr){return;}
    if(SGWBackground::activePages == nullptr || (*SGWBackground::activePages).length() == 0 || (*SGWBackground::activePages).top() != thisPointer){SGLCrash::crash("SGWBackground::disable crashed because the UI page specified does not match the topmost UI page, you must disable application pages in the reverse order of when they were enabled");}
    (*thisPointer).deleteWidget();
    thisPointer = nullptr;
    (*SGWBackground::activePages).pop();
    if((*SGWBackground::activePages).length() > 0){
        (*(*SGWBackground::activePages).top()).setItemVisibility(true);
    }
}
