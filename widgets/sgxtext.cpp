#include "sgxtext.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include "../misc/sgxcentral.h"
#include <QPainter>
#include <QWidget>
#include "../userDefinedClasses/sgusignalemitter.h"
#include <QString>
#include "../primitives/sgxcolourrgba.h"
#include <QPaintEvent>
#include <QColor>
#include <QtCore/Qt>

SGXText::SGXText(QWidget *parent, void (SGUSignalEmitter::*resizeSignal)(), const QString& s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    (*this).setParent(parent);
    (*this).x1 = x1;
    (*this).x0 = x0;
    (*this).y1 = y1;
    (*this).y0 = y0;
    (*this).w1 = w1;
    (*this).w0 = w0;
    (*this).h1 = h1;
    (*this).h0 = h0;
    (*this).backgroundColour = SGUCentralManagement::textBackgroundColour.getQColour();
    (*this).foregroundColour = SGUCentralManagement::textForegroundColour.getQColour();
    (*this).s = s;
    (*this).font = (*SGXCentral::standardFont);
    (*this).show();
    connect(SGXCentral::signalEmitter, resizeSignal, this, &SGXText::resizeObject);
    (*this).resizeObject();
}

void SGXText::setText(const QString& s){
    (*this).s = s;
    (*this).update();
}

void SGXText::setBackgroundColour(){
    backgroundColour = SGUCentralManagement::textBackgroundColour.getQColour();
    update();
}

void SGXText::setBackgroundColour(int themeColourIndex){
    if(themeColourIndex == 0){backgroundColour = SGUCentralManagement::themeColour0.getQColour();}
    else if(themeColourIndex == 1){backgroundColour = SGUCentralManagement::themeColour1.getQColour();}
    else if(themeColourIndex == 2){backgroundColour = SGUCentralManagement::themeColour2.getQColour();}
    else if(themeColourIndex == 3){backgroundColour = SGUCentralManagement::themeColour3.getQColour();}
    else if(themeColourIndex == 4){backgroundColour = SGUCentralManagement::themeColour4.getQColour();}
    else if(themeColourIndex == 5){backgroundColour = SGUCentralManagement::themeColour5.getQColour();}
    else if(themeColourIndex == 6){backgroundColour = SGUCentralManagement::themeColour6.getQColour();}
    else if(themeColourIndex == 7){backgroundColour = SGUCentralManagement::themeColour7.getQColour();}
    else if(themeColourIndex == 8){backgroundColour = SGUCentralManagement::themeColour8.getQColour();}
    else{backgroundColour = SGUCentralManagement::textBackgroundColour.getQColour();}
    update();
}

void SGXText::setBackgroundColour(SGXColourRGBA customColour){
    backgroundColour = customColour.getQColour();
    update();
}

void SGXText::setForegroundColour(){
    foregroundColour = SGUCentralManagement::textForegroundColour.getQColour();
    update();
}

void SGXText::setForegroundColour(int themeColourIndex){
    if(themeColourIndex == 0){foregroundColour = SGUCentralManagement::themeColour0.getQColour();}
    else if(themeColourIndex == 1){foregroundColour = SGUCentralManagement::themeColour1.getQColour();}
    else if(themeColourIndex == 2){foregroundColour = SGUCentralManagement::themeColour2.getQColour();}
    else if(themeColourIndex == 3){foregroundColour = SGUCentralManagement::themeColour3.getQColour();}
    else if(themeColourIndex == 4){foregroundColour = SGUCentralManagement::themeColour4.getQColour();}
    else if(themeColourIndex == 5){foregroundColour = SGUCentralManagement::themeColour5.getQColour();}
    else if(themeColourIndex == 6){foregroundColour = SGUCentralManagement::themeColour6.getQColour();}
    else if(themeColourIndex == 7){foregroundColour = SGUCentralManagement::themeColour7.getQColour();}
    else if(themeColourIndex == 8){foregroundColour = SGUCentralManagement::themeColour8.getQColour();}
    else{foregroundColour = SGUCentralManagement::textForegroundColour.getQColour();}
    update();
}

void SGXText::setForegroundColour(SGXColourRGBA customColour){
    foregroundColour = customColour.getQColour();
    update();
}

void SGXText::resizeObject(){
    font.setPixelSize(static_cast<int>(h1 * SGXCentral::renderAreaHeight + h0 * SGXCentral::sizeUnit));
    setGeometry(static_cast<int>(x1 * SGXCentral::renderAreaWidth + x0 * SGXCentral::sizeUnit), static_cast<int>(y1 * SGXCentral::renderAreaHeight + y0 * SGXCentral::sizeUnit), static_cast<int>(w1 * SGXCentral::renderAreaWidth + w0 * SGXCentral::sizeUnit), static_cast<int>(h1 * SGXCentral::renderAreaHeight + h0 * SGXCentral::sizeUnit));
}

void SGXText::paintEvent(QPaintEvent *){ // NOLINT(readability-named-parameter)
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), backgroundColour);
    p.setRenderHint(QPainter::TextAntialiasing);
    p.setFont(font);
    p.setPen(foregroundColour);
    p.drawText(0, 0, width(), height(), Qt::AlignLeft | Qt::AlignVCenter, s);
}
