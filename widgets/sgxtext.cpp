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
    (*this).bgColourMode = 0;
    (*this).bgThemeColourIndex = 0;
    (*this).bgCustomColour = SGUCentralManagement::textBackgroundColour;
    (*this).fgColourMode = 0;
    (*this).fgThemeColourIndex = 0;
    (*this).fgCustomColour = SGUCentralManagement::textForegroundColour;
    (*this).s = s;
    (*this).font = (*SGXCentral::standardFont);
    (*this).show();
    connect(SGXCentral::signalEmitter, resizeSignal, this, &SGXText::resizeObject);
    (*this).resizeObject();
}

SGXText::SGXText(QWidget *parent, void (SGUSignalEmitter::*resizeSignal)(), const QString& s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int bgThemeColourIndex, int fgThemeColourIndex){
    (*this).setParent(parent);
    (*this).x1 = x1;
    (*this).x0 = x0;
    (*this).y1 = y1;
    (*this).y0 = y0;
    (*this).w1 = w1;
    (*this).w0 = w0;
    (*this).h1 = h1;
    (*this).h0 = h0;
    (*this).bgColourMode = 1;
    (*this).bgThemeColourIndex = bgThemeColourIndex;
    (*this).bgCustomColour = SGUCentralManagement::textBackgroundColour;
    (*this).fgColourMode = 1;
    (*this).fgThemeColourIndex = fgThemeColourIndex;
    (*this).fgCustomColour = SGUCentralManagement::textForegroundColour;
    (*this).s = s;
    (*this).show();
    connect(SGXCentral::signalEmitter, resizeSignal, this, &SGXText::resizeObject);
    (*this).resizeObject();
}

SGXText::SGXText(QWidget *parent, void (SGUSignalEmitter::*resizeSignal)(), const QString& s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGXColourRGBA bgCustomColour, SGXColourRGBA fgCustomColour){
    (*this).setParent(parent);
    (*this).x1 = x1;
    (*this).x0 = x0;
    (*this).y1 = y1;
    (*this).y0 = y0;
    (*this).w1 = w1;
    (*this).w0 = w0;
    (*this).h1 = h1;
    (*this).h0 = h0;
    (*this).bgColourMode = -1;
    (*this).bgThemeColourIndex = 0;
    (*this).bgCustomColour = bgCustomColour;
    (*this).fgColourMode = -1;
    (*this).fgThemeColourIndex = 0;
    (*this).fgCustomColour = fgCustomColour;
    (*this).s = s;
    (*this).show();
    connect(SGXCentral::signalEmitter, resizeSignal, this, &SGXText::resizeObject);
    (*this).resizeObject();
}

void SGXText::setText(const QString& s){
    (*this).s = s;
    (*this).update();
}

void SGXText::resizeObject(){
    font.setPixelSize(static_cast<int>(h1 * SGXCentral::renderAreaHeight + h0 * SGXCentral::sizeUnit));
    setGeometry(static_cast<int>(x1 * SGXCentral::renderAreaWidth + x0 * SGXCentral::sizeUnit), static_cast<int>(y1 * SGXCentral::renderAreaHeight + y0 * SGXCentral::sizeUnit), static_cast<int>(w1 * SGXCentral::renderAreaWidth + w0 * SGXCentral::sizeUnit), static_cast<int>(h1 * SGXCentral::renderAreaHeight + h0 * SGXCentral::sizeUnit));
}

void SGXText::paintEvent(QPaintEvent *){ // NOLINT(readability-named-parameter)
    QPainter p(this);
    QColor bgFillColour;
    QColor fgFillColour;
    if(bgColourMode == 0){bgFillColour = SGUCentralManagement::textBackgroundColour.getQColour();}
    else if(bgColourMode == 1){
        if(bgThemeColourIndex == 0){bgFillColour = SGUCentralManagement::themeColour0.getQColour();}
        else if(bgThemeColourIndex == 1){bgFillColour = SGUCentralManagement::themeColour1.getQColour();}
        else if(bgThemeColourIndex == 2){bgFillColour = SGUCentralManagement::themeColour2.getQColour();}
        else if(bgThemeColourIndex == 3){bgFillColour = SGUCentralManagement::themeColour3.getQColour();}
        else if(bgThemeColourIndex == 4){bgFillColour = SGUCentralManagement::themeColour4.getQColour();}
        else if(bgThemeColourIndex == 5){bgFillColour = SGUCentralManagement::themeColour5.getQColour();}
        else if(bgThemeColourIndex == 6){bgFillColour = SGUCentralManagement::themeColour6.getQColour();}
        else if(bgThemeColourIndex == 7){bgFillColour = SGUCentralManagement::themeColour7.getQColour();}
        else{bgFillColour = SGUCentralManagement::themeColour8.getQColour();}
    }
    else{bgFillColour = bgCustomColour.getQColour();}
    if(fgColourMode == 0){fgFillColour = SGUCentralManagement::textForegroundColour.getQColour();}
    else if(fgColourMode == 1){
        if(fgThemeColourIndex == 0){fgFillColour = SGUCentralManagement::themeColour0.getQColour();}
        else if(fgThemeColourIndex == 1){fgFillColour = SGUCentralManagement::themeColour1.getQColour();}
        else if(fgThemeColourIndex == 2){fgFillColour = SGUCentralManagement::themeColour2.getQColour();}
        else if(fgThemeColourIndex == 3){fgFillColour = SGUCentralManagement::themeColour3.getQColour();}
        else if(fgThemeColourIndex == 4){fgFillColour = SGUCentralManagement::themeColour4.getQColour();}
        else if(fgThemeColourIndex == 5){fgFillColour = SGUCentralManagement::themeColour5.getQColour();}
        else if(fgThemeColourIndex == 6){fgFillColour = SGUCentralManagement::themeColour6.getQColour();}
        else if(fgThemeColourIndex == 7){fgFillColour = SGUCentralManagement::themeColour7.getQColour();}
        else{fgFillColour = SGUCentralManagement::themeColour8.getQColour();}
    }
    else{fgFillColour = fgCustomColour.getQColour();}
    p.fillRect(0, 0, width(), height(), bgFillColour);
    p.setRenderHint(QPainter::TextAntialiasing);
    p.setFont(font);
    p.setPen(fgFillColour);
    p.drawText(0, 0, width(), height(), Qt::AlignLeft | Qt::AlignVCenter, s);
}
