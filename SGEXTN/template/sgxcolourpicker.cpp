#include "sgxcolourpicker.h"
#include "../quickui/sgxquickuiinterface.h"
#include <QQuickItem>
#include <QQmlComponent>
#include "../primitives/sgxcolourrgba.h"
#include <QObject>
#include "../colourpickerrendering/huechoice/sgxrendercolourpickerhuechoicequickuielement.h"
#include <array>
#include "../primitives/sgxtouchevent.h"

QQuickItem* SGXColourPicker::instance = nullptr;
QQuickItem* SGXColourPicker::targetInput = nullptr;
QQmlComponent* SGXColourPicker::hueChoiceTemplate = nullptr;
QQuickItem* SGXColourPicker::hueChoice = nullptr;
QQuickItem* SGXColourPicker::hueChoiceTouchReceiver = nullptr;

void SGXColourPicker::initialise(){
    SGXColourPicker::hueChoiceTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/colourpickerrendering/huechoice/huechoice.qml");
    SGXColourPicker::instance = SGXQuickUIInterface::createWidget(SGXQuickUIInterface::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1);
    QQuickItem* bg = SGXQuickUIInterface::createWidget(SGXColourPicker::instance, 0.5f, -6.25f, 0.5f, -6.5f, 0.0f, 12.5f, 0.0f, 12.0f, 6);
    QQuickItem* realBg = SGXQuickUIInterface::createWidget(bg, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 11.5f, 0.0f, 11.0f, 8);
    SGXColourPicker::hueChoice = SGXColourPicker::createHueChoice(realBg, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 10.5f, 0.0f, 1.25f);
    SGXColourPicker::hueChoiceTouchReceiver = SGXQuickUIInterface::createTouchReceiver(realBg, &SGXColourPicker::changeHue, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 10.5f, 0.0f, 1.25f);
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

void SGXColourPicker::changeHue(const std::array<SGXTouchEvent, 5> &t){
    if(t[0].phase == SGXTouchEvent::TouchEnd){return;}
    float x = 21.0f / 19.0f * static_cast<float>(t[0].x) / static_cast<float>((*SGXColourPicker::hueChoice).width()) - 0.05f;
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
    SGXRenderColourPickerHueChoiceQuickUIElement* display = dynamic_cast<SGXRenderColourPickerHueChoiceQuickUIElement*>(SGXColourPicker::hueChoice);
    (*display).selectedHue = x;
    (*display).update();
}
