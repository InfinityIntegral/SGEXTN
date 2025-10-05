#include "sgwbackground.h"
#include "../../quickui/sgxquickinterface.h"
#include "../../primitives/sgxcolourrgba.h"
#include "sgwwidget.h"
#include "../../bypassquickui/sgxthemecolours.h"
#include <QQuickItem>
#include "../../containers/sglstack.h"
#include <stdexcept>

SGLStack<SGWBackground*>* SGWBackground::activePages = nullptr;

SGWBackground::SGWBackground(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int themeColour) : SGWWidget(parent, x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).usingTheme = true;
    (*this).themeColour = themeColour;
    (*this).colour = SGXThemeColours::getThemeColour((*this).themeColour);
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
    if(SGWBackground::activePages == nullptr || (*SGWBackground::activePages).length() == 0 || (*SGWBackground::activePages).top() != thisPointer){throw std::out_of_range("you must disable application pages in the reverse order of when they were enabled");}
    delete thisPointer;
    thisPointer = nullptr;
    (*SGWBackground::activePages).pop();
    if((*SGWBackground::activePages).length() > 0){
        (*(*SGWBackground::activePages).top()).setItemVisibility(true);
    }
}

void SGWBackground::terminate(){
    delete SGWBackground::activePages;
}
