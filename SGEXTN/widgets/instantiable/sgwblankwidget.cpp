#include "sgwblankwidget.h"
#include "../../quickui/sgxquickinterface.h"
#include "../noninstantiable/sgwwidget.h"
#include "../../primitives/sgxcolourrgba.h"
#include <QQuickItem>
#include "../enums/sgwtype.h"
#include "../../bypassquickui/sgxthemecolours.h"
#include <QColor>

SGWBlankWidget::SGWBlankWidget(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int themeColour) : SGWWidget(parent, x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).usingTheme = true;
    (*this).themeColour = themeColour;
    (*this).colour = SGXThemeColours::getThemeColour((*this).themeColour);
    QQuickItem* thisItem = static_cast<QQuickItem*>((*SGXQuickInterface::blankWidget).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::BlankWidget;
    SGWWidget::syncQuickProperties();
    SGWBlankWidget::syncQuickProperties();
}

int SGWBlankWidget::getThemeColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = true;}
        else{(*isUsing) = false;}
    }
    return themeColour;
}

void SGWBlankWidget::setThemeColour(int themeColour){
    (*this).usingTheme = true;
    (*this).themeColour = themeColour;
    (*(*this).topObject).setProperty("utc", (*this).usingTheme);
    (*(*this).topObject).setProperty("bg", (*this).themeColour);
}

SGXColourRGBA SGWBlankWidget::getColour(bool *isUsing) const {
    if(isUsing != nullptr){
        if(usingTheme == true){(*isUsing) = false;}
        else{(*isUsing) = true;}
    }
    return colour;
}

void SGWBlankWidget::setColour(SGXColourRGBA colour){
    (*this).usingTheme = false;
    (*this).colour = colour;
    (*(*this).topObject).setProperty("utc", false);
    (*(*this).topObject).setProperty("bgc", QColor(colour.getRed(), colour.getGreen(), colour.getBlue(), colour.getTransparency()));
}

void SGWBlankWidget::syncQuickProperties(){
    (*topObject).setProperty("utc", usingTheme);
    (*topObject).setProperty("bg", themeColour);
    (*topObject).setProperty("bgc", QColor(colour.getRed(), colour.getGreen(), colour.getBlue(), colour.getTransparency()));
}
