#include "sgxrendercolourpickersaturationchoicesgwidget.h"
#include "sgxrendercolourpickersaturationchoicequickuielement.h"
#include "../../widgets/noninstantiable/sgwwidget.h"
#include "../../widgets/instantiable/sgwcustomrenderer.h"
#include "../../primitives/sgxstring.h"

SGXRenderColourPickerSaturationChoiceSGWidget::SGXRenderColourPickerSaturationChoiceSGWidget(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0) : SGWCustomRenderer(parent, ":/SGEXTN/colourpickerrendering/saturationchoice/saturationchoice.qml", x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).selectedHue = 0.0f;
    (*this).selectedSaturation = 0.0f;
    SGXRenderColourPickerSaturationChoiceQuickUIElement* thisItem = static_cast<SGXRenderColourPickerSaturationChoiceQuickUIElement*>(topObject);
    (*thisItem).selectedHue = (*this).selectedHue;
    (*thisItem).selectedSaturation = (*this).selectedSaturation;
}

float SGXRenderColourPickerSaturationChoiceSGWidget::getSelectedHue() const {
    return selectedHue;
}

void SGXRenderColourPickerSaturationChoiceSGWidget::setSelectedHue(float x){
    (*this).selectedHue = x;
    (*static_cast<SGXRenderColourPickerSaturationChoiceQuickUIElement*>(topObject)).selectedHue = (*this).selectedHue;
}

float SGXRenderColourPickerSaturationChoiceSGWidget::getSelectedSaturation() const {
    return selectedSaturation;
}

void SGXRenderColourPickerSaturationChoiceSGWidget::setSelectedSaturation(float x){
    (*this).selectedSaturation = x;
    (*static_cast<SGXRenderColourPickerSaturationChoiceQuickUIElement*>(topObject)).selectedSaturation = (*this).selectedSaturation;
}
