#include "sgwcolourpicker.h"
#include "../widgets/sgwpagebackground.h"
#include "../widgets/sgwblankwidget.h"
#include "../widgets/sgwbackground.h"
#include "../primitives/sgxcolourhsla.h"
#include "../primitives/sgxcolourrgba.h"
#include "../widgets/sgwwidget.h"
#include "../colourpickerrendering/huechoice/sgxrendercolourpickerhuechoicesgwidget.h"
#include "../widgets/sgwtouchreceiver.h"
#include <array>
#include "../primitives/sgxtouchevent.h"
#include "../colourpickerrendering/saturationchoice/sgxrendercolourpickersaturationchoicesgwidget.h"
#include "../colourpickerrendering/lightnesschoice/sgxrendercolourpickerlightnesschoicesgwidget.h"
#include "../colourpickerrendering/transparencychoice/sgxrendercolourpickertransparencychoicesgwidget.h"

SGWBackground* SGWColourPicker::instance = nullptr;
SGXColourRGBA SGWColourPicker::colour = SGXColourRGBA(255, 0, 200);
SGXColourHSLA SGWColourPicker::colourHSLA = SGXColourHSLA(SGXColourRGBA(255, 0, 200));
SGXRenderColourPickerHueChoiceSGWidget* SGWColourPicker::hueChoice = nullptr;
SGWTouchReceiver* SGWColourPicker::hueTouchReceiver = nullptr;
SGXRenderColourPickerSaturationChoiceSGWidget* SGWColourPicker::saturationChoice = nullptr;
SGWTouchReceiver* SGWColourPicker::saturationTouchReceiver = nullptr;
SGXRenderColourPickerLightnessChoiceSGWidget* SGWColourPicker::lightnessChoice = nullptr;
SGWTouchReceiver* SGWColourPicker::lightnessTouchReceiver = nullptr;
SGXRenderColourPickerTransparencyChoiceSGWidget* SGWColourPicker::transparencyChoice = nullptr;
SGWTouchReceiver* SGWColourPicker::transparencyTouchReceiver = nullptr;

SGWBackground* SGWColourPicker::initialise(){
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 6, false);
    SGWWidget* realBg = new SGWBlankWidget(bg, 0.5f, -5.75f, 0.5f, -6.0f, 0.0f, 11.5f, 0.0f, 11.0f, 8);
    SGWColourPicker::hueChoice = new SGXRenderColourPickerHueChoiceSGWidget(realBg, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 0.0f, 1.25f);
    SGWColourPicker::hueTouchReceiver = new SGWTouchReceiver(SGWColourPicker::hueChoice, &SGWColourPicker::updateHue, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    SGWColourPicker::saturationChoice = new SGXRenderColourPickerSaturationChoiceSGWidget(realBg, 0.0f, 0.5f, 0.0f, 2.0f, 1.0f, -1.0f, 0.0f, 1.25f);
    SGWColourPicker::saturationTouchReceiver = new SGWTouchReceiver(SGWColourPicker::saturationChoice, &SGWColourPicker::updateSaturation, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    SGWColourPicker::lightnessChoice = new SGXRenderColourPickerLightnessChoiceSGWidget(realBg, 0.0f, 0.5f, 0.0f, 3.5f, 1.0f, -1.0f, 0.0f, 1.25f);
    SGWColourPicker::lightnessTouchReceiver = new SGWTouchReceiver(SGWColourPicker::lightnessChoice, &SGWColourPicker::updateLightness, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    SGWColourPicker::transparencyChoice = new SGXRenderColourPickerTransparencyChoiceSGWidget(realBg, 0.0f, 0.5f, 0.0f, 5.0f, 1.0f, -1.0f, 0.0f, 1.25f);
    SGWColourPicker::transparencyTouchReceiver = new SGWTouchReceiver(SGWColourPicker::transparencyChoice, &SGWColourPicker::updateTransparency, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    return bg;
}

void SGWColourPicker::reset(){
    SGWColourPicker::updateInputs();
}

void SGWColourPicker::activate(){
    SGWBackground::enable(SGWColourPicker::instance, &SGWColourPicker::initialise, &SGWColourPicker::reset);
}

void SGWColourPicker::updateUsingColour(){
    SGWColourPicker::colourHSLA = SGXColourHSLA(SGWColourPicker::colour);
    SGWColourPicker::updateInputs();
}

void SGWColourPicker::updateUsingColourHSLA(){
    SGWColourPicker::colour = SGWColourPicker::colourHSLA.toRGBA();
    SGWColourPicker::updateInputs();
}

void SGWColourPicker::updateInputs(){
    (*SGWColourPicker::hueChoice).setSelectedHue(SGWColourPicker::colourHSLA.h / 360.0f);
    (*SGWColourPicker::hueChoice).redraw();
    (*SGWColourPicker::saturationChoice).setSelectedHue(SGWColourPicker::colourHSLA.h / 360.0f);
    (*SGWColourPicker::saturationChoice).setSelectedSaturation(SGWColourPicker::colourHSLA.s / 100.0f);
    (*SGWColourPicker::saturationChoice).redraw();
    (*SGWColourPicker::lightnessChoice).setSelectedHue(SGWColourPicker::colourHSLA.h / 360.0f);
    (*SGWColourPicker::lightnessChoice).setSelectedSaturation(SGWColourPicker::colourHSLA.s / 100.0f);
    (*SGWColourPicker::lightnessChoice).setSelectedLightness(SGWColourPicker::colourHSLA.l / 100.0f);
    (*SGWColourPicker::lightnessChoice).redraw();
    (*SGWColourPicker::transparencyChoice).setSelectedHue(SGWColourPicker::colourHSLA.h / 360.0f);
    (*SGWColourPicker::transparencyChoice).setSelectedSaturation(SGWColourPicker::colourHSLA.s / 100.0f);
    (*SGWColourPicker::transparencyChoice).setSelectedLightness(SGWColourPicker::colourHSLA.l / 100.0f);
    (*SGWColourPicker::transparencyChoice).setSelectedTransparency(SGWColourPicker::colourHSLA.a / 100.0f);
    (*SGWColourPicker::transparencyChoice).redraw();
}

void SGWColourPicker::updateHue(SGWTouchReceiver * /*unused*/, const std::array<SGXTouchEvent, 5> &t){
    if(t[0].phase == SGXTouchEvent::TouchEnd){return;}
    float x = 21.0f / 19.0f * static_cast<float>(t[0].x) / static_cast<float>((*SGWColourPicker::hueTouchReceiver).getWidth()) - 0.05f;
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
    SGWColourPicker::colourHSLA.h = x * 360.0f;
    SGWColourPicker::updateUsingColourHSLA();
}

void SGWColourPicker::updateSaturation(SGWTouchReceiver */*unused*/, const std::array<SGXTouchEvent, 5> &t){
    if(t[0].phase == SGXTouchEvent::TouchEnd){return;}
    float x = 21.0f / 19.0f * static_cast<float>(t[0].x) / static_cast<float>((*SGWColourPicker::saturationTouchReceiver).getWidth()) - 0.05f;
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
    SGWColourPicker::colourHSLA.s = x * 100.0f;
    SGWColourPicker::updateUsingColourHSLA();
}

void SGWColourPicker::updateLightness(SGWTouchReceiver */*unused*/, const std::array<SGXTouchEvent, 5> &t){
    if(t[0].phase == SGXTouchEvent::TouchEnd){return;}
    float x = 21.0f / 19.0f * static_cast<float>(t[0].x) / static_cast<float>((*SGWColourPicker::lightnessTouchReceiver).getWidth()) - 0.05f;
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
    SGWColourPicker::colourHSLA.l = x * 100.0f;
    SGWColourPicker::updateUsingColourHSLA();
}

void SGWColourPicker::updateTransparency(SGWTouchReceiver */*unused*/, const std::array<SGXTouchEvent, 5> &t){
    if(t[0].phase == SGXTouchEvent::TouchEnd){return;}
    float x = 21.0f / 19.0f * static_cast<float>(t[0].x) / static_cast<float>((*SGWColourPicker::transparencyTouchReceiver).getWidth()) - 0.05f;
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
    SGWColourPicker::colourHSLA.a = x * 100.0f;
    SGWColourPicker::updateUsingColourHSLA();
}
