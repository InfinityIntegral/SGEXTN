#include "sgxrendercolourpickerhuechoicesgwidget.h"
#include "sgxrendercolourpickerhuechoicequickuielement.h"
#include "../../widgets/sgwwidget.h"
#include "../../widgets/sgwcustomrenderer.h"
#include <QObject>

SGXRenderColourPickerHueChoiceSGWidget::SGXRenderColourPickerHueChoiceSGWidget(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0) : SGWCustomRenderer(parent, ":/SGEXTN/colourpickerrendering/huechoice/huechoice.qml", x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).selectedHue = 0.0f;
    SGXRenderColourPickerHueChoiceQuickUIElement* thisItem = qobject_cast<SGXRenderColourPickerHueChoiceQuickUIElement*>(topObject);
    (*thisItem).selectedHue = 0.0f;
}

float SGXRenderColourPickerHueChoiceSGWidget::getSelectedHue() const {
    return selectedHue;
}

void SGXRenderColourPickerHueChoiceSGWidget::setSelectedHue(float x){
    (*this).selectedHue = x;
    (*qobject_cast<SGXRenderColourPickerHueChoiceQuickUIElement*>(topObject)).selectedHue = (*this).selectedHue;
}
