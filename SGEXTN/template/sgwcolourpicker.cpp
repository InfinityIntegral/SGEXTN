#include "sgwcolourpicker.h"
#include "../widgets/sgwpagebackground.h"
#include "../widgets/sgwblankwidget.h"
#include "../widgets/sgwbackground.h"
#include "../primitives/sgxcolourhsla.h"
#include "../primitives/sgxcolourrgba.h"
#include "../widgets/sgwwidget.h"
#include "../colourpickerrendering/huechoice/sgxrendercolourpickerhuechoicesgwidget.h"

SGWBackground* SGWColourPicker::instance = nullptr;
SGXColourRGBA SGWColourPicker::colour = SGXColourRGBA(255, 0, 200);
SGXColourHSLA SGWColourPicker::colourHSLA = SGXColourHSLA(SGXColourRGBA(255, 0, 200));
SGXRenderColourPickerHueChoiceSGWidget* SGWColourPicker::hueChoice = nullptr;

SGWBackground* SGWColourPicker::initialise(){
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 6, false);
    SGWWidget* realBg = new SGWBlankWidget(bg, 0.5f, -5.75f, 0.5f, -6.0f, 0.0f, 11.5f, 0.0f, 11.0f, 8);
    SGWColourPicker::hueChoice = new SGXRenderColourPickerHueChoiceSGWidget(realBg, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 0.0f, 1.25f);
    return bg;
}

void SGWColourPicker::reset(){
    
}

void SGWColourPicker::activate(){
    SGWBackground::enable(SGWColourPicker::instance, &SGWColourPicker::initialise, &SGWColourPicker::reset);
}
