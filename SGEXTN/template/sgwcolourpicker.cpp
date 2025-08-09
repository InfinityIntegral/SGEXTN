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
#include "../widgets/sgwtextinput.h"
#include "../widgets/sgwtextlabel.h"
#include "../widgets/sgwinput.h"
#include "../widgets/sgwhorizontalalignment.h"
#include <QString>
#include "../colourbackground/sgxrendercolourbackgroundsgwidget.h"
#include "../widgets/sgwcolourpickerwidget.h"
#include "../widgets/sgwtextbutton.h"
#include "../widgets/sgwbutton.h"

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
SGWInput* SGWColourPicker::redInput = nullptr;
SGWInput* SGWColourPicker::greenInput = nullptr;
SGWInput* SGWColourPicker::blueInput = nullptr;
SGWInput* SGWColourPicker::transparencyInput = nullptr;
SGWInput* SGWColourPicker::hexCodeInput = nullptr;
SGXRenderColourBackgroundSGWidget* SGWColourPicker::colourDisplay = nullptr;
bool SGWColourPicker::ignoreInputChanges = false;
SGWColourPickerWidget* SGWColourPicker::colourReceiver = nullptr;
SGWButton* SGWColourPicker::completeButton = nullptr;

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
    new SGWTextLabel(realBg, "red:", 0.0f, 0.5f, 0.0f, 6.5f, 0.0f, 1.4f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWColourPicker::redInput = new SGWTextInput(realBg, nullptr, 0.0f, 2.0f, 0.0f, 6.5f, 0.0f, 2.0f, 0.0f, 1.0f);
    (*SGWColourPicker::redInput).setTextChangedFunction(&SGWColourPicker::updateRed);
    new SGWTextLabel(realBg, "green:", 0.0f, 4.5f, 0.0f, 6.5f, 0.0f, 1.9f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWColourPicker::greenInput = new SGWTextInput(realBg, nullptr, 0.0f, 6.5f, 0.0f, 6.5f, 0.0f, 2.0f, 0.0f, 1.0f);
    (*SGWColourPicker::greenInput).setTextChangedFunction(&SGWColourPicker::updateGreen);
    new SGWTextLabel(realBg, "blue:", 0.0f, 0.5f, 0.0f, 8.0f, 0.0f, 1.4f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWColourPicker::blueInput = new SGWTextInput(realBg, nullptr, 0.0f, 2.0f, 0.0f, 8.0f, 0.0f, 2.0f, 0.0f, 1.0f);
    (*SGWColourPicker::blueInput).setTextChangedFunction(&SGWColourPicker::updateBlue);
    new SGWTextLabel(realBg, "transparency:", 0.0f, 4.4f, 0.0f, 8.0f, 0.0f, 4.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWColourPicker::transparencyInput = new SGWTextInput(realBg, nullptr, 0.0f, 8.5f, 0.0f, 8.0f, 0.0f, 2.0f, 0.0f, 1.0f);
    (*SGWColourPicker::transparencyInput).setTextChangedFunction(&SGWColourPicker::updateTransparencyFromInput);
    new SGWTextLabel(realBg, "hex code:", 0.0f, 0.5f, 0.0f, 9.5f, 0.0f, 2.9f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWColourPicker::hexCodeInput = new SGWTextInput(realBg, nullptr, 0.0f, 3.5f, 0.0f, 9.5f, 0.0f, 5.0f, 0.0f, 1.0f);
    (*SGWColourPicker::hexCodeInput).setTextChangedFunction(&SGWColourPicker::updateHexCode);
    SGWColourPicker::colourDisplay = new SGXRenderColourBackgroundSGWidget(realBg, 0.0f, 9.0f, 0.0f, 6.5f, 0.0f, 2.0f, 0.0f, 1.0f, SGWColourPicker::colour);
    SGWColourPicker::completeButton = new SGWTextButton(realBg, "ok", &SGWColourPicker::completeColourSelection, 0.0f, 9.0f, 0.0f, 9.5f, 0.0f, 1.5f, 0.0f, 1.0f);
    return bg;
}

void SGWColourPicker::reset(){
    SGWColourPicker::updateInputs();
}

void SGWColourPicker::activate(){
    SGWBackground::enable(SGWColourPicker::instance, &SGWColourPicker::initialise, &SGWColourPicker::reset);
}

void SGWColourPicker::updateUsingColour(){
    if(SGWColourPicker::ignoreInputChanges == true){return;}
    SGWColourPicker::colourHSLA = SGXColourHSLA(SGWColourPicker::colour);
    SGWColourPicker::updateInputs();
}

void SGWColourPicker::updateUsingColourHSLA(){
    if(SGWColourPicker::ignoreInputChanges == true){return;}
    SGWColourPicker::colour = SGWColourPicker::colourHSLA.toRGBA();
    SGWColourPicker::updateInputs();
}

void SGWColourPicker::updateInputs(){
    SGWColourPicker::ignoreInputChanges = true;
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
    (*SGWColourPicker::redInput).setTextFromInt(SGWColourPicker::colour.getRed());
    (*SGWColourPicker::greenInput).setTextFromInt(SGWColourPicker::colour.getGreen());
    (*SGWColourPicker::blueInput).setTextFromInt(SGWColourPicker::colour.getBlue());
    (*SGWColourPicker::transparencyInput).setTextFromInt(SGWColourPicker::colour.getTransparency());
    QString hexCode = QString::number(SGWColourPicker::colour.x, 16).toUpper().rightJustified(8, '0');
    if(hexCode.mid(6, 2) == "FF"){hexCode = hexCode.mid(0, 6);}
    (*SGWColourPicker::hexCodeInput).setTextFromString(hexCode);
    (*SGWColourPicker::colourDisplay).setColour(SGWColourPicker::colour);
    SGWColourPicker::ignoreInputChanges = false;
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

void SGWColourPicker::updateRed(SGWInput */*unused*/){
    bool isValid = false;
    const int r = (*SGWColourPicker::redInput).getTextAsInt(&isValid, 0, 255);
    if(isValid == false){return;}
    SGWColourPicker::colour.setRed(r);
    SGWColourPicker::updateUsingColour();
}

void SGWColourPicker::updateGreen(SGWInput */*unused*/){
    bool isValid = false;
    const int g = (*SGWColourPicker::greenInput).getTextAsInt(&isValid, 0, 255);
    if(isValid == false){return;}
    SGWColourPicker::colour.setGreen(g);
    SGWColourPicker::updateUsingColour();
}

void SGWColourPicker::updateBlue(SGWInput */*unused*/){
    bool isValid = false;
    const int b = (*SGWColourPicker::blueInput).getTextAsInt(&isValid, 0, 255);
    if(isValid == false){return;}
    SGWColourPicker::colour.setBlue(b);
    SGWColourPicker::updateUsingColour();
}

void SGWColourPicker::updateTransparencyFromInput(SGWInput */*unused*/){
    bool isValid = false;
    const int a = (*SGWColourPicker::transparencyInput).getTextAsInt(&isValid, 0, 255);
    if(isValid == false){return;}
    SGWColourPicker::colour.setTransparency(a);
    SGWColourPicker::updateUsingColour();
}

void SGWColourPicker::updateHexCode(SGWInput */*unused*/){
    QString correctedInput = "";
    QString rawInput = (*SGWColourPicker::hexCodeInput).getTextAsString().toUpper();
    for(int i=0; i<rawInput.length(); i++){
        if((rawInput[i] >= '0' && rawInput[i] <= '9') || (rawInput[i] >= 'A' && rawInput[i] <= 'F')){correctedInput += rawInput[i];}
    }
    if(correctedInput.length() == 6){correctedInput += "FF";}
    if(correctedInput.length() != 8){return;}
    SGWColourPicker::colour.setRed(correctedInput.mid(0, 2).toInt(nullptr, 16));
    SGWColourPicker::colour.setGreen(correctedInput.mid(2, 2).toInt(nullptr, 16));
    SGWColourPicker::colour.setBlue(correctedInput.mid(4, 2).toInt(nullptr, 16));
    SGWColourPicker::colour.setTransparency(correctedInput.mid(6, 2).toInt(nullptr, 16));
    SGWColourPicker::updateUsingColour();
}

void SGWColourPicker::activateColourPicker(SGWColourPickerWidget *x){
    SGWColourPicker::colourReceiver = x;
    SGWColourPicker::colour = (*x).getColour();
    SGWColourPicker::colourHSLA = SGXColourHSLA(SGWColourPicker::colour);
    SGWColourPicker::activate();
}

void SGWColourPicker::completeColourSelection(SGWButton */*unused*/){
    (*SGWColourPicker::colourReceiver).setColour(SGWColourPicker::colour);
    SGWColourPicker::colourReceiver = nullptr;
    SGWBackground::disable(SGWColourPicker::instance);
}
