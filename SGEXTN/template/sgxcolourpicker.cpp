#include "sgxcolourpicker.h"
#include "../quickui/sgxquickuiinterface.h"
#include <QQuickItem>
#include <QQmlComponent>
#include "../primitives/sgxcolourrgba.h"
#include <QObject>
#include "../colourpickerrendering/huechoice/sgxrendercolourpickerhuechoicequickuielement.h"
#include <array>
#include "../primitives/sgxtouchevent.h"
#include "../colourpickerrendering/saturationchoice/sgxrendercolourpickersaturationchoicequickuielement.h"

QQuickItem* SGXColourPicker::instance = nullptr;
QQuickItem* SGXColourPicker::targetInput = nullptr;
QQmlComponent* SGXColourPicker::hueChoiceTemplate = nullptr;
QQuickItem* SGXColourPicker::hueChoice = nullptr;
QQuickItem* SGXColourPicker::hueChoiceTouchReceiver = nullptr;
QQmlComponent* SGXColourPicker::saturationChoiceTemplate = nullptr;
QQuickItem* SGXColourPicker::saturationChoice = nullptr;
QQuickItem* SGXColourPicker::saturationChoiceTouchReceiver = nullptr;

void SGXColourPicker::initialise(){
    SGXColourPicker::hueChoiceTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/colourpickerrendering/huechoice/huechoice.qml");
    SGXColourPicker::saturationChoiceTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/colourpickerrendering/saturationchoice/saturationchoice.qml");
    SGXColourPicker::instance = SGXQuickUIInterface::createWidget(SGXQuickUIInterface::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1);
    QQuickItem* bg = SGXQuickUIInterface::createWidget(SGXColourPicker::instance, 0.5f, -6.25f, 0.5f, -6.5f, 0.0f, 12.5f, 0.0f, 12.0f, 6);
    QQuickItem* realBg = SGXQuickUIInterface::createWidget(bg, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 11.5f, 0.0f, 11.0f, 8);
    SGXColourPicker::hueChoice = SGXColourPicker::createHueChoice(realBg, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 10.5f, 0.0f, 1.25f);
    SGXColourPicker::hueChoiceTouchReceiver = SGXQuickUIInterface::createTouchReceiver(realBg, &SGXColourPicker::changeHue, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 10.5f, 0.0f, 1.25f);
    SGXColourPicker::saturationChoice = SGXColourPicker::createSaturationChoice(realBg, 0.0f, 0.5f, 0.0f, 2.0f, 0.0f, 10.5f, 0.0f, 1.25f);
    SGXColourPicker::saturationChoiceTouchReceiver = SGXQuickUIInterface::createTouchReceiver(realBg, &SGXColourPicker::changeSaturation, 0.0f, 0.5f, 0.0f, 2.0f, 0.0f, 10.5f, 0.0f, 1.25f);
}

void SGXColourPicker::activate(){
    SGXColourPicker::targetInput = SGXQuickUIInterface::getActiveObject();
    if(SGXColourPicker::instance == nullptr){SGXColourPicker::initialise();}
    (*SGXColourPicker::instance).setVisible(true);
    (*SGXColourPicker::targetInput).setProperty("c", SGXColourRGBA(0, 0, 0).getQColour());
}

QQuickItem* SGXColourPicker::createHueChoice(QQuickItem *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXColourPicker::hueChoiceTemplate).create());
    SGXQuickUIInterface::setActualParent(thisItem, parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("h1", h1);
    (*thisItem).setProperty("h0", h0);
    return thisItem;
}

QQuickItem* SGXColourPicker::createSaturationChoice(QQuickItem *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXColourPicker::saturationChoiceTemplate).create());
    SGXQuickUIInterface::setActualParent(thisItem, parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("h1", h1);
    (*thisItem).setProperty("h0", h0);
    return thisItem;
}

void SGXColourPicker::changeHue(const std::array<SGXTouchEvent, 5> &t){
    if(t[0].phase == SGXTouchEvent::TouchEnd){return;}
    float x = 21.0f / 19.0f * static_cast<float>(t[0].x) / static_cast<float>((*SGXColourPicker::hueChoice).width()) - 0.05f;
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
    SGXRenderColourPickerHueChoiceQuickUIElement* displayHue = dynamic_cast<SGXRenderColourPickerHueChoiceQuickUIElement*>(SGXColourPicker::hueChoice);
    (*displayHue).selectedHue = x;
    (*displayHue).update();
    SGXRenderColourPickerSaturationChoiceQuickUIElement* displaySaturation = dynamic_cast<SGXRenderColourPickerSaturationChoiceQuickUIElement*>(SGXColourPicker::saturationChoice);
    (*displaySaturation).selectedHue = x;
    (*displaySaturation).update();
}

void SGXColourPicker::changeSaturation(const std::array<SGXTouchEvent, 5> &t){
    if(t[0].phase == SGXTouchEvent::TouchEnd){return;}
    float x = 21.0f / 19.0f * static_cast<float>(t[0].x) / static_cast<float>((*SGXColourPicker::saturationChoice).width()) - 0.05f;
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
    SGXRenderColourPickerSaturationChoiceQuickUIElement* displaySaturation = dynamic_cast<SGXRenderColourPickerSaturationChoiceQuickUIElement*>(SGXColourPicker::saturationChoice);
    (*displaySaturation).selectedSaturation = x;
    (*displaySaturation).update();
}
