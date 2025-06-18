#include "sgxwidget.h"
#include "../misc/sgxcentral.h"
#include <QPainter>
#include <QWidget>
#include "../userDefinedClasses/sgusignalemitter.h"
#include "../primitives/sgxcolourrgba.h"
#include <QPaintEvent>
#include <QColor>

SGXWidget::SGXWidget(QWidget *parent, void (SGUSignalEmitter::*resizeSignal)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int themeColourIndex){
    (*this).setParent(parent);
    (*this).x1 = x1;
    (*this).x0 = x0;
    (*this).y1 = y1;
    (*this).y0 = y0;
    (*this).w1 = w1;
    (*this).w0 = w0;
    (*this).h1 = h1;
    (*this).h0 = h0;
    (*this).fillColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGXCentral::noColour);
    (*this).show();
    connect(SGXCentral::signalEmitter, resizeSignal, this, &SGXWidget::resizeObject);
    (*this).resizeObject();
}

void SGXWidget::setColour(){
    fillColour = SGXCentral::noColour.getQColour();
    update();
}

void SGXWidget::setColour(int themeColourIndex){
    fillColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGXCentral::noColour);
    update();
}

void SGXWidget::setColour(SGXColourRGBA customColour){
    fillColour = customColour.getQColour();
    update();
}

void SGXWidget::resizeObject(){
    setGeometry(static_cast<int>(x1 * SGXCentral::renderAreaWidth + x0 * SGXCentral::sizeUnit), static_cast<int>(y1 * SGXCentral::renderAreaHeight + y0 * SGXCentral::sizeUnit), static_cast<int>(w1 * SGXCentral::renderAreaWidth + w0 * SGXCentral::sizeUnit), static_cast<int>(h1 * SGXCentral::renderAreaHeight + h0 * SGXCentral::sizeUnit));
}

void SGXWidget::paintEvent(QPaintEvent *){ // NOLINT(readability-named-parameter)
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), fillColour);
}
