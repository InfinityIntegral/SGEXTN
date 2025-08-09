#include "sgwcolourpickerwidget.h"
#include "../quickui/sgxquickinterface.h"
#include "../template/sgwcolourpicker.h"
#include "../widgets/sgwwidget.h"
#include "../primitives/sgxcolourrgba.h"
#include <QQuickItem>
#include <QObject>
#include "../widgets/sgwtype.h"
#include <QString>

SGWColourPickerWidget::SGWColourPickerWidget(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGXColourRGBA defaultColour) : SGWWidget(parent, x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).colour = defaultColour;
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickInterface::colourPicker).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::ColourPicker;
    SGWWidget::syncQuickProperties();
    SGWColourPickerWidget::syncQuickProperties();
}

SGXColourRGBA SGWColourPickerWidget::getColour() const {
    return colour;
}

void SGWColourPickerWidget::setColour(SGXColourRGBA colour){
    (*this).colour = colour;
    (*(*this).topObject).setProperty("c", (*this).colour.getQColour());
}

void SGWColourPickerWidget::syncQuickProperties(){
    (*topObject).setProperty("c", colour.getQColour());
    connect(topObject, &QQuickItem::objectNameChanged, this, &SGWColourPickerWidget::eventReceived);
}

void SGWColourPickerWidget::eventReceived(const QString &s){
    if(s == "click"){SGWColourPicker::activateColourPicker(this);}
}
