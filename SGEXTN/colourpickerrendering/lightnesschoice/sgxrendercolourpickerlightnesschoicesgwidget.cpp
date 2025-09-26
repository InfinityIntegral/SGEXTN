#include "sgxrendercolourpickerlightnesschoicesgwidget.h"
#include "sgxrendercolourpickerlightnesschoicequickuielement.h"
#include "../../widgets/noninstantiable/sgwwidget.h"
#include "../../widgets/instantiable/sgwcustomrenderer.h"
#include "../../primitives/sgxstring.h"

SGXRenderColourPickerLightnessChoiceSGWidget::SGXRenderColourPickerLightnessChoiceSGWidget(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0) : SGWCustomRenderer(parent, ":/SGEXTN/colourpickerrendering/lightnesschoice/lightnesschoice.qml", x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).selectedHue = 0.0f;
    (*this).selectedSaturation = 0.0f;
    (*this).selectedLightness = 0.0f;
    SGXRenderColourPickerLightnessChoiceQuickUIElement* thisItem = static_cast<SGXRenderColourPickerLightnessChoiceQuickUIElement*>(topObject);
    (*thisItem).selectedHue = (*this).selectedHue;
    (*thisItem).selectedSaturation = (*this).selectedSaturation;
    (*thisItem).selectedLightness = (*this).selectedLightness;
}

float SGXRenderColourPickerLightnessChoiceSGWidget::getSelectedHue() const {
    return selectedHue;
}

void SGXRenderColourPickerLightnessChoiceSGWidget::setSelectedHue(float x){
    (*this).selectedHue = x;
    (*static_cast<SGXRenderColourPickerLightnessChoiceQuickUIElement*>(topObject)).selectedHue = (*this).selectedHue;
}

float SGXRenderColourPickerLightnessChoiceSGWidget::getSelectedSaturation() const {
    return selectedSaturation;
}

void SGXRenderColourPickerLightnessChoiceSGWidget::setSelectedSaturation(float x){
    (*this).selectedSaturation = x;
    (*static_cast<SGXRenderColourPickerLightnessChoiceQuickUIElement*>(topObject)).selectedSaturation = (*this).selectedSaturation;
}

float SGXRenderColourPickerLightnessChoiceSGWidget::getSelectedLightness() const {
    return selectedLightness;
}

void SGXRenderColourPickerLightnessChoiceSGWidget::setSelectedLightness(float x){
    (*this).selectedLightness = x;
    (*static_cast<SGXRenderColourPickerLightnessChoiceQuickUIElement*>(topObject)).selectedLightness = (*this).selectedLightness;
}
