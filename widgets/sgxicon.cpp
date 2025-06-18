#include "sgxicon.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include "../misc/sgxcentral.h"
#include <QPainter>
#include <QWidget>
#include "../userDefinedClasses/sgusignalemitter.h"
#include <QChar>
#include "../primitives/sgxcolourrgba.h"
#include <QPaintEvent>
#include <QColor>
#include <QtCore/Qt>

SGXIcon::SGXIcon(QWidget *parent, void (SGUSignalEmitter::*resizeSignal)(), const QChar &s, float x1, float x0, float y1, float y0, float w1, float w0){
    (*this).setParent(parent);
    (*this).x1 = x1;
    (*this).x0 = x0;
    (*this).y1 = y1;
    (*this).y0 = y0;
    (*this).w1 = w1;
    (*this).w0 = w0;
    (*this).backgroundColour = SGUCentralManagement::textBackgroundColour.getQColour();
    (*this).foregroundColour = SGUCentralManagement::textForegroundColour.getQColour();
    (*this).s = s;
    (*this).font = (*SGXCentral::iconsFont);
    (*this).show();
    connect(SGXCentral::signalEmitter, resizeSignal, this, &SGXIcon::resizeObject);
    (*this).resizeObject();
}

void SGXIcon::setIcon(const QChar &s){
    (*this).s = s;
    (*this).update();
}

void SGXIcon::setBackgroundColour(){
    backgroundColour = SGUCentralManagement::textBackgroundColour.getQColour();
    update();
}

void SGXIcon::setBackgroundColour(int themeColourIndex){
    backgroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::textBackgroundColour);
    update();
}

void SGXIcon::setBackgroundColour(SGXColourRGBA customColour){
    backgroundColour = customColour.getQColour();
    update();
}

void SGXIcon::setForegroundColour(){
    foregroundColour = SGUCentralManagement::textForegroundColour.getQColour();
    update();
}

void SGXIcon::setForegroundColour(int themeColourIndex){
    foregroundColour = SGXCentral::getThemeColourAsQColour(themeColourIndex, SGUCentralManagement::textForegroundColour);
    update();
}

void SGXIcon::setForegroundColour(SGXColourRGBA customColour){
    foregroundColour = customColour.getQColour();
    update();
}

void SGXIcon::resizeObject(){
    font.setPixelSize(static_cast<int>(w1 * SGXCentral::renderAreaHeight + w0 * SGXCentral::sizeUnit));
    setGeometry(static_cast<int>(x1 * SGXCentral::renderAreaWidth + x0 * SGXCentral::sizeUnit), static_cast<int>(y1 * SGXCentral::renderAreaHeight + y0 * SGXCentral::sizeUnit), static_cast<int>(w1 * SGXCentral::renderAreaWidth + w0 * SGXCentral::sizeUnit), static_cast<int>(w1 * SGXCentral::renderAreaHeight + w0 * SGXCentral::sizeUnit));
}

void SGXIcon::paintEvent(QPaintEvent *){ // NOLINT(readability-named-parameter)
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), backgroundColour);
    p.setRenderHint(QPainter::TextAntialiasing);
    p.setFont(font);
    p.setPen(foregroundColour);
    p.drawText(0, 0, width(), height(), Qt::AlignHCenter | Qt::AlignVCenter, s);
}
