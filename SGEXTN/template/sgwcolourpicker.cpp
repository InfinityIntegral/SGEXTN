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

SGWBackground* SGWColourPicker::instance = nullptr;
SGXColourRGBA SGWColourPicker::colour = SGXColourRGBA(255, 0, 200);
SGXColourHSLA SGWColourPicker::colourHSLA = SGXColourHSLA(SGXColourRGBA(255, 0, 200));
SGXRenderColourPickerHueChoiceSGWidget* SGWColourPicker::hueChoice = nullptr;
SGWTouchReceiver* SGWColourPicker::hueTouchReceiver = nullptr;

SGWBackground* SGWColourPicker::initialise(){
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 6, false);
    SGWWidget* realBg = new SGWBlankWidget(bg, 0.5f, -5.75f, 0.5f, -6.0f, 0.0f, 11.5f, 0.0f, 11.0f, 8);
    SGWColourPicker::hueChoice = new SGXRenderColourPickerHueChoiceSGWidget(realBg, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 0.0f, 1.25f);
    SGWColourPicker::hueTouchReceiver = new SGWTouchReceiver(SGWColourPicker::hueChoice, &SGWColourPicker::updateHue, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    return bg;
}

void SGWColourPicker::reset(){
    
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
}

void SGWColourPicker::updateHue(SGWTouchReceiver * /*unused*/, const std::array<SGXTouchEvent, 5> &t){
    if(t[0].phase == SGXTouchEvent::TouchEnd){return;}
    float x = 21.0f / 19.0f * static_cast<float>(t[0].x) / static_cast<float>((*SGWColourPicker::hueTouchReceiver).getWidth()) - 0.05f;
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
    SGWColourPicker::colourHSLA.h = x * 360.0f;
    SGWColourPicker::updateUsingColourHSLA();
}
