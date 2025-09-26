#include "sgxrendercolourbackgroundsgwidget.h"
#include "../primitives/sgxcolourrgba.h"
#include "../widgets/noninstantiable/sgwwidget.h"
#include "../widgets/instantiable/sgwcustomrenderer.h"
#include <QQuickItem>
#include "../primitives/sgxstring.h"

SGXRenderColourBackgroundSGWidget::SGXRenderColourBackgroundSGWidget(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGXColourRGBA c) : SGWCustomRenderer(parent, ":/SGEXTN/colourbackground/colourbackground.qml", x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).colour = c;
    (*topObject).setProperty("c", (*this).colour.getQColour());
}

SGXColourRGBA SGXRenderColourBackgroundSGWidget::getColour() const {
    return colour;
}

void SGXRenderColourBackgroundSGWidget::setColour(SGXColourRGBA c){
    (*this).colour = c;
    (*topObject).setProperty("c", (*this).colour.getQColour());
}
