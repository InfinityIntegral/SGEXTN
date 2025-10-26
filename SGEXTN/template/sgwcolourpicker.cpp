#include "sgwcolourpicker.h"
#include "../widgets/instantiable/sgwpagebackground.h"
#include "../widgets/instantiable/sgwblankwidget.h"
#include "../widgets/noninstantiable/sgwbackground.h"
#include "../primitives/sgxcolourhsla.h"
#include "../primitives/sgxcolourrgba.h"
#include "../widgets/noninstantiable/sgwwidget.h"
#include "../colourpickerrendering/huechoice/sgxrendercolourpickerhuechoicesgwidget.h"
#include "../primitives/sgxtouchevent.h"
#include "../colourpickerrendering/saturationchoice/sgxrendercolourpickersaturationchoicesgwidget.h"
#include "../colourpickerrendering/lightnesschoice/sgxrendercolourpickerlightnesschoicesgwidget.h"
#include "../colourpickerrendering/transparencychoice/sgxrendercolourpickertransparencychoicesgwidget.h"
#include "../widgets/instantiable/sgwtextinput.h"
#include "../widgets/instantiable/sgwtextlabel.h"
#include "../widgets/noninstantiable/sgwinput.h"
#include "../widgets/enums/sgwhorizontalalignment.h"
#include "../widgets/instantiable/sgwcolourpickerwidget.h"
#include "../widgets/instantiable/sgwtextbutton.h"
#include "../widgets/noninstantiable/sgwbutton.h"
#include "../widgets/instantiable/sgwsingletouchreceiver.h"
#include "../RendererInterface/transparencyindicator/sgrtransparencyindicatorrenderer.h"
#include "../RendererInterface/sgrrenderergenerator.h"

SGWBackground* SGWColourPicker::instance = nullptr;
SGXColourRGBA SGWColourPicker::colour = SGXColourRGBA(255, 0, 200);
SGXColourHSLA SGWColourPicker::colourHSLA = SGXColourHSLA(SGXColourRGBA(255, 0, 200));
SGXRenderColourPickerHueChoiceSGWidget* SGWColourPicker::hueChoice = nullptr;
SGWSingleTouchReceiver* SGWColourPicker::hueTouchReceiver = nullptr;
SGXRenderColourPickerSaturationChoiceSGWidget* SGWColourPicker::saturationChoice = nullptr;
SGWSingleTouchReceiver* SGWColourPicker::saturationTouchReceiver = nullptr;
SGXRenderColourPickerLightnessChoiceSGWidget* SGWColourPicker::lightnessChoice = nullptr;
SGWSingleTouchReceiver* SGWColourPicker::lightnessTouchReceiver = nullptr;
SGXRenderColourPickerTransparencyChoiceSGWidget* SGWColourPicker::transparencyChoice = nullptr;
SGWSingleTouchReceiver* SGWColourPicker::transparencyTouchReceiver = nullptr;
SGWInput* SGWColourPicker::redInput = nullptr;
SGWInput* SGWColourPicker::greenInput = nullptr;
SGWInput* SGWColourPicker::blueInput = nullptr;
SGWInput* SGWColourPicker::transparencyInput = nullptr;
SGWInput* SGWColourPicker::hexCodeInput = nullptr;
SGWBlankWidget* SGWColourPicker::transparencyGrid = nullptr;
SGWBlankWidget* SGWColourPicker::colourDisplay = nullptr;
bool SGWColourPicker::ignoreInputChanges = false;
SGWColourPickerWidget* SGWColourPicker::colourReceiver = nullptr;
SGWButton* SGWColourPicker::completeButton = nullptr;

SGWBackground* SGWColourPicker::initialise(){
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 6);
    SGWWidget* realBg = new SGWBlankWidget(bg, 0.5f, -5.75f, 0.5f, -6.0f, 0.0f, 11.5f, 0.0f, 11.0f, 8);
    //SGWColourPicker::hueChoice = new SGXRenderColourPickerHueChoiceSGWidget(realBg, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 0.0f, 1.25f);
    SGWBlankWidget* tempVal = nullptr;
    tempVal = new SGWBlankWidget(realBg, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 0.0f, 1.25f, 6);
    SGWColourPicker::hueTouchReceiver = new SGWSingleTouchReceiver(tempVal, &SGWColourPicker::updateHue, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    //SGWColourPicker::saturationChoice = new SGXRenderColourPickerSaturationChoiceSGWidget(realBg, 0.0f, 0.5f, 0.0f, 2.0f, 1.0f, -1.0f, 0.0f, 1.25f);
    tempVal = new SGWBlankWidget(realBg, 0.0f, 0.5f, 0.0f, 2.0f, 1.0f, -1.0f, 0.0f, 1.25f, 6);
    SGWColourPicker::saturationTouchReceiver = new SGWSingleTouchReceiver(tempVal, &SGWColourPicker::updateSaturation, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    //SGWColourPicker::lightnessChoice = new SGXRenderColourPickerLightnessChoiceSGWidget(realBg, 0.0f, 0.5f, 0.0f, 3.5f, 1.0f, -1.0f, 0.0f, 1.25f);
    tempVal = new SGWBlankWidget(realBg, 0.0f, 0.5f, 0.0f, 3.5f, 1.0f, -1.0f, 0.0f, 1.25f, 6);
    SGWColourPicker::lightnessTouchReceiver = new SGWSingleTouchReceiver(tempVal, &SGWColourPicker::updateLightness, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    //SGWColourPicker::transparencyChoice = new SGXRenderColourPickerTransparencyChoiceSGWidget(realBg, 0.0f, 0.5f, 0.0f, 5.0f, 1.0f, -1.0f, 0.0f, 1.25f);
    tempVal = new SGWBlankWidget(realBg, 0.0f, 0.5f, 0.0f, 5.0f, 1.0f, -1.0f, 0.0f, 1.25f, 6);
    SGWColourPicker::transparencyTouchReceiver = new SGWSingleTouchReceiver(tempVal, &SGWColourPicker::updateTransparency, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    new SGWTextLabel(realBg, "red:", 0.0f, 0.5f, 0.0f, 6.5f, 0.0f, 1.4f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWColourPicker::redInput = new SGWTextInput(realBg, nullptr, 0.0f, 2.0f, 0.0f, 6.5f, 0.0f, 2.0f, 0.0f, 1.0f);
    (*SGWColourPicker::redInput).textChangedFunction = (&SGWColourPicker::updateRed);
    new SGWTextLabel(realBg, "green:", 0.0f, 4.5f, 0.0f, 6.5f, 0.0f, 1.9f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWColourPicker::greenInput = new SGWTextInput(realBg, nullptr, 0.0f, 6.5f, 0.0f, 6.5f, 0.0f, 2.0f, 0.0f, 1.0f);
    (*SGWColourPicker::greenInput).textChangedFunction = (&SGWColourPicker::updateGreen);
    new SGWTextLabel(realBg, "blue:", 0.0f, 0.5f, 0.0f, 8.0f, 0.0f, 1.4f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWColourPicker::blueInput = new SGWTextInput(realBg, nullptr, 0.0f, 2.0f, 0.0f, 8.0f, 0.0f, 2.0f, 0.0f, 1.0f);
    (*SGWColourPicker::blueInput).textChangedFunction = (&SGWColourPicker::updateBlue);
    new SGWTextLabel(realBg, "transparency:", 0.0f, 4.4f, 0.0f, 8.0f, 0.0f, 4.4f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWColourPicker::transparencyInput = new SGWTextInput(realBg, nullptr, 0.0f, 9.0f, 0.0f, 8.0f, 0.0f, 2.0f, 0.0f, 1.0f);
    (*SGWColourPicker::transparencyInput).textChangedFunction = (&SGWColourPicker::updateTransparencyFromInput);
    new SGWTextLabel(realBg, "hex code:", 0.0f, 0.5f, 0.0f, 9.5f, 0.0f, 2.9f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWColourPicker::hexCodeInput = new SGWTextInput(realBg, nullptr, 0.0f, 3.5f, 0.0f, 9.5f, 0.0f, 5.0f, 0.0f, 1.0f);
    (*SGWColourPicker::hexCodeInput).textChangedFunction = (&SGWColourPicker::updateHexCode);
    SGWColourPicker::transparencyGrid = new SGWBlankWidget(realBg, 0.0f, 9.0f, 0.0f, 6.5f, 0.0f, 2.0f, 0.0f, 1.0f, -1);
    SGWColourPicker::colourDisplay = new SGWBlankWidget(realBg, 0.0f, 9.0f, 0.0f, 6.5f, 0.0f, 2.0f, 0.0f, 1.0f, -1);
    SGRBaseRenderer* renderControl = new SGRTransparencyIndicatorRenderer();
    new SGRRendererGenerator(renderControl, nullptr, (*SGWColourPicker::transparencyGrid).getBottomObject());
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
    /*
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
    */
    (*SGWColourPicker::redInput).setTextFromInt(SGWColourPicker::colour.getRed());
    (*SGWColourPicker::greenInput).setTextFromInt(SGWColourPicker::colour.getGreen());
    (*SGWColourPicker::blueInput).setTextFromInt(SGWColourPicker::colour.getBlue());
    (*SGWColourPicker::transparencyInput).setTextFromInt(SGWColourPicker::colour.getTransparency());
    SGXString hexCode = SGXString::unsignedIntToStringBase16(SGWColourPicker::colour.x).fillLeftToLength(8, '0');
    if(hexCode.substring(6, 2) == "FF"){hexCode = hexCode.substringLeft(6);}
    (*SGWColourPicker::hexCodeInput).setTextFromString(hexCode);
    (*SGWColourPicker::colourDisplay).setColour(SGWColourPicker::colour);
    SGWColourPicker::ignoreInputChanges = false;
}

void SGWColourPicker::updateHue(const SGXTouchEvent &t){
    if(t.phase == SGXTouchEvent::TouchEnd){return;}
    float x = 21.0f / 19.0f * static_cast<float>(t.x) / (*SGWColourPicker::hueTouchReceiver).getWidth() - 0.05f;
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
    SGWColourPicker::colourHSLA.h = x * 360.0f;
    SGWColourPicker::updateUsingColourHSLA();
}

void SGWColourPicker::updateSaturation(const SGXTouchEvent &t){
    if(t.phase == SGXTouchEvent::TouchEnd){return;}
    float x = 21.0f / 19.0f * static_cast<float>(t.x) / (*SGWColourPicker::saturationTouchReceiver).getWidth() - 0.05f;
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
    SGWColourPicker::colourHSLA.s = x * 100.0f;
    SGWColourPicker::updateUsingColourHSLA();
}

void SGWColourPicker::updateLightness(const SGXTouchEvent &t){
    if(t.phase == SGXTouchEvent::TouchEnd){return;}
    float x = 21.0f / 19.0f * static_cast<float>(t.x) / (*SGWColourPicker::lightnessTouchReceiver).getWidth() - 0.05f;
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
    SGWColourPicker::colourHSLA.l = x * 100.0f;
    SGWColourPicker::updateUsingColourHSLA();
}

void SGWColourPicker::updateTransparency(const SGXTouchEvent &t){
    if(t.phase == SGXTouchEvent::TouchEnd){return;}
    float x = 21.0f / 19.0f * static_cast<float>(t.x) / (*SGWColourPicker::transparencyTouchReceiver).getWidth() - 0.05f;
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
    SGWColourPicker::colourHSLA.a = x * 100.0f;
    SGWColourPicker::updateUsingColourHSLA();
}

void SGWColourPicker::updateRed(){
    bool isValid = false;
    const int r = (*SGWColourPicker::redInput).getTextAsInt(&isValid, 0, 255);
    if(isValid == false){return;}
    SGWColourPicker::colour.setRed(r);
    SGWColourPicker::updateUsingColour();
}

void SGWColourPicker::updateGreen(){
    bool isValid = false;
    const int g = (*SGWColourPicker::greenInput).getTextAsInt(&isValid, 0, 255);
    if(isValid == false){return;}
    SGWColourPicker::colour.setGreen(g);
    SGWColourPicker::updateUsingColour();
}

void SGWColourPicker::updateBlue(){
    bool isValid = false;
    const int b = (*SGWColourPicker::blueInput).getTextAsInt(&isValid, 0, 255);
    if(isValid == false){return;}
    SGWColourPicker::colour.setBlue(b);
    SGWColourPicker::updateUsingColour();
}

void SGWColourPicker::updateTransparencyFromInput(){
    bool isValid = false;
    const int a = (*SGWColourPicker::transparencyInput).getTextAsInt(&isValid, 0, 255);
    if(isValid == false){return;}
    SGWColourPicker::colour.setTransparency(a);
    SGWColourPicker::updateUsingColour();
}

void SGWColourPicker::updateHexCode(){
    SGXString correctedInput = "";
    const SGXString rawInput = (*SGWColourPicker::hexCodeInput).getTextAsString().getUpperLanguageAware();
    for(int i=0; i<rawInput.length(); i++){
        if(rawInput.at(i).isDigitBase16() == true){correctedInput += rawInput.at(i);}
    }
    if(correctedInput.length() == 6){correctedInput += "FF";}
    if(correctedInput.length() != 8){return;}
    SGWColourPicker::colour.setRed(correctedInput.substring(0, 2).parseToIntBase16(nullptr));
    SGWColourPicker::colour.setGreen(correctedInput.substring(2, 2).parseToIntBase16(nullptr));
    SGWColourPicker::colour.setBlue(correctedInput.substring(4, 2).parseToIntBase16(nullptr));
    SGWColourPicker::colour.setTransparency(correctedInput.substring(6, 2).parseToIntBase16(nullptr));
    SGWColourPicker::updateUsingColour();
}

void SGWColourPicker::activateColourPicker(SGWColourPickerWidget *x){
    SGWColourPicker::colourReceiver = x;
    SGWColourPicker::colour = (*x).getColour();
    SGWColourPicker::colourHSLA = SGXColourHSLA(SGWColourPicker::colour);
    SGWColourPicker::activate();
}

void SGWColourPicker::completeColourSelection(){
    (*SGWColourPicker::colourReceiver).setColour(SGWColourPicker::colour);
    SGWColourPicker::colourReceiver = nullptr;
    SGWBackground::disable(SGWColourPicker::instance);
}
