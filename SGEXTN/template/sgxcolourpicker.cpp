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
#include "../primitives/sgxcolourhsla.h"
#include "../colourpickerrendering/lightnesschoice/sgxrendercolourpickerlightnesschoicequickuielement.h"
#include "../colourpickerrendering/transparencychoice/sgxrendercolourpickertransparencychoicequickuielement.h"

QQuickItem* SGXColourPicker::instance = nullptr;
QQuickItem* SGXColourPicker::targetInput = nullptr;
SGXColourRGBA SGXColourPicker::currentColour = SGXColourRGBA(255, 255, 255, 0);
SGXColourHSLA SGXColourPicker::currentColourHSLA = SGXColourHSLA(0.0f, 0.0f, 100.0f, 0.0f);
QQmlComponent* SGXColourPicker::hueChoiceTemplate = nullptr;
QQuickItem* SGXColourPicker::hueChoice = nullptr;
QQuickItem* SGXColourPicker::hueChoiceTouchReceiver = nullptr;
QQmlComponent* SGXColourPicker::saturationChoiceTemplate = nullptr;
QQuickItem* SGXColourPicker::saturationChoice = nullptr;
QQuickItem* SGXColourPicker::saturationChoiceTouchReceiver = nullptr;
QQmlComponent* SGXColourPicker::lightnessChoiceTemplate = nullptr;
QQuickItem* SGXColourPicker::lightnessChoice = nullptr;
QQuickItem* SGXColourPicker::lightnessChoiceTouchReceiver = nullptr;
QQmlComponent* SGXColourPicker::transparencyChoiceTemplate = nullptr;
QQuickItem* SGXColourPicker::transparencyChoice = nullptr;
QQuickItem* SGXColourPicker::transparencyChoiceTouchReceiver = nullptr;
QQuickItem* SGXColourPicker::redInput = nullptr;
QQuickItem* SGXColourPicker::greenInput = nullptr;
QQuickItem* SGXColourPicker::blueInput = nullptr;
QQuickItem* SGXColourPicker::transparencyInput = nullptr;
QQmlComponent* SGXColourPicker::colourBackgroundTemplate = nullptr;
QQuickItem* SGXColourPicker::colourDisplay = nullptr;
QQuickItem* SGXColourPicker::hexCodeInput = nullptr;

void SGXColourPicker::initialise(){
    SGXColourPicker::hueChoiceTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/colourpickerrendering/huechoice/huechoice.qml");
    SGXColourPicker::saturationChoiceTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/colourpickerrendering/saturationchoice/saturationchoice.qml");
    SGXColourPicker::lightnessChoiceTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/colourpickerrendering/lightnesschoice/lightnesschoice.qml");
    SGXColourPicker::transparencyChoiceTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/colourpickerrendering/transparencychoice/transparencychoice.qml");
    SGXColourPicker::colourBackgroundTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/colourbackground/colourbackground.qml");
    SGXColourPicker::instance = SGXQuickUIInterface::createWidget(SGXQuickUIInterface::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 6);
    QQuickItem* realBg = SGXQuickUIInterface::createWidget(SGXColourPicker::instance, 0.5f, -5.75f, 0.5f, -6.0f, 0.0f, 11.5f, 0.0f, 11.0f, 8);
    SGXColourPicker::hueChoice = SGXColourPicker::createHueChoice(realBg, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 10.5f, 0.0f, 1.25f);
    SGXColourPicker::hueChoiceTouchReceiver = SGXQuickUIInterface::createTouchReceiver(realBg, &SGXColourPicker::changeHue, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 10.5f, 0.0f, 1.25f);
    SGXColourPicker::saturationChoice = SGXColourPicker::createSaturationChoice(realBg, 0.0f, 0.5f, 0.0f, 2.0f, 0.0f, 10.5f, 0.0f, 1.25f);
    SGXColourPicker::saturationChoiceTouchReceiver = SGXQuickUIInterface::createTouchReceiver(realBg, &SGXColourPicker::changeSaturation, 0.0f, 0.5f, 0.0f, 2.0f, 0.0f, 10.5f, 0.0f, 1.25f);
    SGXColourPicker::lightnessChoice = SGXColourPicker::createLightnessChoice(realBg, 0.0f, 0.5f, 0.0f, 3.5f, 0.0f, 10.5f, 0.0f, 1.25f);
    SGXColourPicker::lightnessChoiceTouchReceiver = SGXQuickUIInterface::createTouchReceiver(realBg, &SGXColourPicker::changeLightness, 0.0f, 0.5f, 0.0f, 3.5f, 0.0f, 10.5f, 0.0f, 1.25f);
    SGXColourPicker::transparencyChoice = SGXColourPicker::createTransparencyChoice(realBg, 0.0f, 0.5f, 0.0f, 5.0f, 0.0f, 10.5f, 0.0f, 1.25f);
    SGXColourPicker::transparencyChoiceTouchReceiver = SGXQuickUIInterface::createTouchReceiver(realBg, &SGXColourPicker::changeTransparencyBySlider, 0.0f, 0.5f, 0.0f, 5.0f, 0.0f, 10.5f, 0.0f, 1.25f);
    SGXQuickUIInterface::createText(realBg, "red:", 0.0f, 0.5f, 0.0f, 6.5f, 0.0f, 1.5f, 0.0f, 1.0f);
    SGXColourPicker::redInput = SGXQuickUIInterface::createInputField(realBg, 0.0f, 2.0f, 0.0f, 6.5f, 0.0f, 2.0f, 0.0f, 1.0f);
    connect(SGXColourPicker::redInput, &QQuickItem::objectNameChanged, &SGXColourPicker::changeRed);
    SGXQuickUIInterface::createText(realBg, "green:", 0.0f, 4.5f, 0.0f, 6.5f, 0.0f, 2.0f, 0.0f, 1.0f);
    SGXColourPicker::greenInput = SGXQuickUIInterface::createInputField(realBg, 0.0f, 6.5f, 0.0f, 6.5f, 0.0f, 2.0f, 0.0f, 1.0f);
    connect(SGXColourPicker::greenInput, &QQuickItem::objectNameChanged, &SGXColourPicker::changeGreen);
    SGXQuickUIInterface::createText(realBg, "blue:", 0.0f, 0.5f, 0.0f, 8.0f, 0.0f, 1.5f, 0.0f, 1.0f);
    SGXColourPicker::blueInput = SGXQuickUIInterface::createInputField(realBg, 0.0f, 2.0f, 0.0f, 8.0f, 0.0f, 2.0f, 0.0f, 1.0f);
    connect(SGXColourPicker::blueInput, &QQuickItem::objectNameChanged, &SGXColourPicker::changeBlue);
    SGXQuickUIInterface::createText(realBg, "transparency:", 0.0f, 4.5f, 0.0f, 8.0f, 0.0f, 4.5f, 0.0f, 1.0f);
    SGXColourPicker::transparencyInput = SGXQuickUIInterface::createInputField(realBg, 0.0f, 8.5f, 0.0f, 8.0f, 0.0f, 2.0f, 0.0f, 1.0f);
    connect(SGXColourPicker::transparencyInput, &QQuickItem::objectNameChanged, &SGXColourPicker::changeTransparency);
    SGXColourPicker::colourDisplay = SGXColourPicker::createColourBackground(realBg, 0.0f, 9.0f, 0.0f, 6.5f, 0.0f, 2.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createText(realBg, "hex code:", 0.0f, 0.5f, 0.0f, 9.5f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGXColourPicker::hexCodeInput = SGXQuickUIInterface::createInputField(realBg, 0.0f, 3.5f, 0.0f, 9.5f, 0.0f, 5.0f, 0.0f, 1.0f);
    connect(SGXColourPicker::hexCodeInput, &QQuickItem::objectNameChanged, &SGXColourPicker::changeHexCode);
}

void SGXColourPicker::activate(){
    SGXColourPicker::targetInput = SGXQuickUIInterface::getActiveObject();
    if(SGXColourPicker::instance == nullptr){SGXColourPicker::initialise();}
    bool ignore = false;
    SGXColourPicker::currentColour = SGXQuickUIInterface::getColourPickerColour(SGXColourPicker::targetInput, ignore);
    SGXColourPicker::currentColourHSLA = SGXColourHSLA(SGXColourPicker::currentColour);
    (*SGXColourPicker::instance).setVisible(true);
    SGXColourPicker::refresh();
}

void SGXColourPicker::refresh(){
    (*SGXColourPicker::targetInput).setProperty("c", SGXColourPicker::currentColour.getQColour());
    (*SGXColourPicker::colourDisplay).setProperty("c", SGXColourPicker::currentColour.getQColour());
    SGXRenderColourPickerHueChoiceQuickUIElement* displayHue = qobject_cast<SGXRenderColourPickerHueChoiceQuickUIElement*>(SGXColourPicker::hueChoice);
    (*displayHue).selectedHue = SGXColourPicker::currentColourHSLA.h / 360.0f;
    (*displayHue).update();
    SGXRenderColourPickerSaturationChoiceQuickUIElement* displaySaturation = qobject_cast<SGXRenderColourPickerSaturationChoiceQuickUIElement*>(SGXColourPicker::saturationChoice);
    (*displaySaturation).selectedHue = SGXColourPicker::currentColourHSLA.h / 360.0f;
    (*displaySaturation).selectedSaturation = SGXColourPicker::currentColourHSLA.s / 100.0f;
    (*displaySaturation).update();
    SGXRenderColourPickerLightnessChoiceQuickUIElement* displayLightness = qobject_cast<SGXRenderColourPickerLightnessChoiceQuickUIElement*>(SGXColourPicker::lightnessChoice);
    (*displayLightness).selectedHue = SGXColourPicker::currentColourHSLA.h / 360.0f;
    (*displayLightness).selectedSaturation = SGXColourPicker::currentColourHSLA.s / 100.0f;
    (*displayLightness).selectedLightness = SGXColourPicker::currentColourHSLA.l / 100.0f;
    (*displayLightness).update();
    SGXRenderColourPickerTransparencyChoiceQuickUIElement* displayTransparency = qobject_cast<SGXRenderColourPickerTransparencyChoiceQuickUIElement*>(SGXColourPicker::transparencyChoice);
    (*displayTransparency).selectedHue = SGXColourPicker::currentColourHSLA.h / 360.0f;
    (*displayTransparency).selectedSaturation = SGXColourPicker::currentColourHSLA.s / 100.0f;
    (*displayTransparency).selectedLightness = SGXColourPicker::currentColourHSLA.l / 100.0f;
    (*displayTransparency).selectedTransparency = SGXColourPicker::currentColourHSLA.a / 100.0f;
    (*displayTransparency).update();
    (*SGXColourPicker::redInput).setProperty("noSendSignal", true);
    (*SGXColourPicker::greenInput).setProperty("noSendSignal", true);
    (*SGXColourPicker::blueInput).setProperty("noSendSignal", true);
    (*SGXColourPicker::transparencyInput).setProperty("noSendSignal", true);
    (*SGXColourPicker::redInput).setProperty("text", QString::number(SGXColourPicker::currentColour.getRed()));
    (*SGXColourPicker::greenInput).setProperty("text", QString::number(SGXColourPicker::currentColour.getGreen()));
    (*SGXColourPicker::blueInput).setProperty("text", QString::number(SGXColourPicker::currentColour.getBlue()));
    (*SGXColourPicker::transparencyInput).setProperty("text", QString::number(SGXColourPicker::currentColour.getTransparency()));
    (*SGXColourPicker::redInput).setProperty("noSendSignal", false);
    (*SGXColourPicker::greenInput).setProperty("noSendSignal", false);
    (*SGXColourPicker::blueInput).setProperty("noSendSignal", false);
    (*SGXColourPicker::transparencyInput).setProperty("noSendSignal", false);
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

QQuickItem* SGXColourPicker::createLightnessChoice(QQuickItem *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXColourPicker::lightnessChoiceTemplate).create());
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

QQuickItem* SGXColourPicker::createTransparencyChoice(QQuickItem *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXColourPicker::transparencyChoiceTemplate).create());
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

QQuickItem* SGXColourPicker::createColourBackground(QQuickItem *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXColourPicker::colourBackgroundTemplate).create());
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
    SGXColourPicker::currentColourHSLA.h = x * 360.0f;
    SGXColourPicker::currentColour = SGXColourPicker::currentColourHSLA.toRGBA();
    SGXColourPicker::refresh();
}

void SGXColourPicker::changeSaturation(const std::array<SGXTouchEvent, 5> &t){
    if(t[0].phase == SGXTouchEvent::TouchEnd){return;}
    float x = 21.0f / 19.0f * static_cast<float>(t[0].x) / static_cast<float>((*SGXColourPicker::saturationChoice).width()) - 0.05f;
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
    SGXColourPicker::currentColourHSLA.s = x * 100.0f;
    SGXColourPicker::currentColour = SGXColourPicker::currentColourHSLA.toRGBA();
    SGXColourPicker::refresh();
}

void SGXColourPicker::changeLightness(const std::array<SGXTouchEvent, 5> &t){
    if(t[0].phase == SGXTouchEvent::TouchEnd){return;}
    float x = 21.0f / 19.0f * static_cast<float>(t[0].x) / static_cast<float>((*SGXColourPicker::lightnessChoice).width()) - 0.05f;
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
    SGXColourPicker::currentColourHSLA.l = x * 100.0f;
    SGXColourPicker::currentColour = SGXColourPicker::currentColourHSLA.toRGBA();
    SGXColourPicker::refresh();
}

void SGXColourPicker::changeTransparencyBySlider(const std::array<SGXTouchEvent, 5> &t){
    if(t[0].phase == SGXTouchEvent::TouchEnd){return;}
    float x = 21.0f / 19.0f * static_cast<float>(t[0].x) / static_cast<float>((*SGXColourPicker::lightnessChoice).width()) - 0.05f;
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
    SGXColourPicker::currentColourHSLA.a = x * 100.0f;
    SGXColourPicker::currentColour = SGXColourPicker::currentColourHSLA.toRGBA();
    SGXColourPicker::refresh();
}

void SGXColourPicker::changeRed(){
    bool isValid = false;
    const int r = SGXQuickUIInterface::getInputFieldDataAsInt(SGXColourPicker::redInput, isValid);
    if(isValid == false){return;}
    if(r < 0 || r > 255){return;}
    SGXColourPicker::currentColour.setRed(r);
    SGXColourPicker::currentColourHSLA = SGXColourHSLA(SGXColourPicker::currentColour);
    SGXColourPicker::refresh();
}

void SGXColourPicker::changeGreen(){
    bool isValid = false;
    const int g = SGXQuickUIInterface::getInputFieldDataAsInt(SGXColourPicker::greenInput, isValid);
    if(isValid == false){return;}
    if(g < 0 || g > 255){return;}
    SGXColourPicker::currentColour.setGreen(g);
    SGXColourPicker::currentColourHSLA = SGXColourHSLA(SGXColourPicker::currentColour);
    SGXColourPicker::refresh();
}

void SGXColourPicker::changeBlue(){
    bool isValid = false;
    const int b = SGXQuickUIInterface::getInputFieldDataAsInt(SGXColourPicker::blueInput, isValid);
    if(isValid == false){return;}
    if(b < 0 || b > 255){return;}
    SGXColourPicker::currentColour.setBlue(b);
    SGXColourPicker::currentColourHSLA = SGXColourHSLA(SGXColourPicker::currentColour);
    SGXColourPicker::refresh();
}

void SGXColourPicker::changeTransparency(){
    bool isValid = false;
    const int a = SGXQuickUIInterface::getInputFieldDataAsInt(SGXColourPicker::transparencyInput, isValid);
    if(isValid == false){return;}
    if(a < 0 || a > 255){return;}
    SGXColourPicker::currentColour.setTransparency(a);
    SGXColourPicker::currentColourHSLA = SGXColourHSLA(SGXColourPicker::currentColour);
    SGXColourPicker::refresh();
}

void SGXColourPicker::changeHexCode(){
    
}
