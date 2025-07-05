#include "sgxcolourpicker.h"
#include "../quickui/sgxquickuiinterface.h"

QQuickItem* SGXColourPicker::instance = nullptr;
QQuickItem* SGXColourPicker::targetInput = nullptr;

void SGXColourPicker::initialise(){
    SGXColourPicker::instance = SGXQuickUIInterface::createWidget(SGXQuickUIInterface::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1);
    QQuickItem* bg = SGXQuickUIInterface::createWidget(SGXColourPicker::instance, 0.5f, -6.25f, 0.5f, -6.5f, 0.0f, 12.5f, 0.0f, 12.0f, 6);
    SGXQuickUIInterface::createWidget(bg, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 11.5f, 0.0f, 11.0f, 8);
}

void SGXColourPicker::activate(){
    SGXColourPicker::targetInput = SGXQuickUIInterface::getActiveObject();
    if(SGXColourPicker::instance == nullptr){SGXColourPicker::initialise();}
    (*SGXColourPicker::instance).setVisible(true);
    (*SGXColourPicker::targetInput).setProperty("c", SGXColourRGBA(0, 0, 0).getQColour());
}
