#include "sgwbackground.h"
#include "../quickui/sgxquickinterface.h"
#include "../primitives/sgxcolourrgba.h"
#include "sgwwidget.h"

SGWBackground::SGWBackground(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int themeColour) : SGWWidget(parent, x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).usingTheme = true;
    (*this).themeColour = themeColour;
    (*this).colour = (*SGXQuickInterface::themeColoursSingleton).getThemeColour((*this).themeColour);
}

bool SGWBackground::isUsingThemeColour() const {
    return usingTheme;
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
    (*(*this).topObject).setProperty("bgc", colour.getQColour());
}
