#include "sgxrendercolourpickertransparencychoicesgwidget.h"
#include "sgxrendercolourpickertransparencychoicequickuielement.h"
#include "../../widgets/noninstantiable/sgwwidget.h"
#include "../../widgets/instantiable/sgwcustomrenderer.h"
#include <QObject>

SGXRenderColourPickerTransparencyChoiceSGWidget::SGXRenderColourPickerTransparencyChoiceSGWidget(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0) : SGWCustomRenderer(parent, ":/SGEXTN/colourpickerrendering/transparencychoice/transparencychoice.qml", x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).selectedHue = 0.0f;
    (*this).selectedSaturation = 0.0f;
    (*this).selectedLightness = 0.0f;
    (*this).selectedTransparency = 0.0f;
    SGXRenderColourPickerTransparencyChoiceQuickUIElement* thisItem = qobject_cast<SGXRenderColourPickerTransparencyChoiceQuickUIElement*>(topObject);
    (*thisItem).selectedHue = (*this).selectedHue;
    (*thisItem).selectedSaturation = (*this).selectedSaturation;
    (*thisItem).selectedLightness = (*this).selectedLightness;
    (*thisItem).selectedTransparency = (*this).selectedTransparency;
}

float SGXRenderColourPickerTransparencyChoiceSGWidget::getSelectedHue() const {
    return selectedHue;
}

void SGXRenderColourPickerTransparencyChoiceSGWidget::setSelectedHue(float x){
    (*this).selectedHue = x;
    (*qobject_cast<SGXRenderColourPickerTransparencyChoiceQuickUIElement*>(topObject)).selectedHue = (*this).selectedHue;
}

float SGXRenderColourPickerTransparencyChoiceSGWidget::getSelectedSaturation() const {
    return selectedSaturation;
}

void SGXRenderColourPickerTransparencyChoiceSGWidget::setSelectedSaturation(float x){
    (*this).selectedSaturation = x;
    (*qobject_cast<SGXRenderColourPickerTransparencyChoiceQuickUIElement*>(topObject)).selectedSaturation = (*this).selectedSaturation;
}

float SGXRenderColourPickerTransparencyChoiceSGWidget::getSelectedLightness() const {
    return selectedLightness;
}

void SGXRenderColourPickerTransparencyChoiceSGWidget::setSelectedLightness(float x){
    (*this).selectedLightness = x;
    (*qobject_cast<SGXRenderColourPickerTransparencyChoiceQuickUIElement*>(topObject)).selectedLightness = (*this).selectedLightness;
}

float SGXRenderColourPickerTransparencyChoiceSGWidget::getSelectedTransparency() const {
    return selectedTransparency;
}

void SGXRenderColourPickerTransparencyChoiceSGWidget::setSelectedTransparency(float x){
    (*this).selectedTransparency = x;
    (*qobject_cast<SGXRenderColourPickerTransparencyChoiceQuickUIElement*>(topObject)).selectedTransparency = (*this).selectedTransparency;
}
