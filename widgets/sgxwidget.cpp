#include "sgxwidget.h"
#include "../misc/sgxcentral.h"
#include <QPainter>
#include "../userDefinedClasses/sgucentralmanagement.h"
#include <QWidget>
#include "../userDefinedClasses/sgusignalemitter.h"
#include "../primitives/sgxcolourrgba.h"
#include <QPaintEvent>
#include <QColor>

SGXWidget::SGXWidget(QWidget* parent, void (SGUSignalEmitter::*resizeSignal)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    (*this).setParent(parent);
    (*this).x1 = x1;
    (*this).x0 = x0;
    (*this).y1 = y1;
    (*this).y0 = y0;
    (*this).w1 = w1;
    (*this).w0 = w0;
    (*this).h1 = h1;
    (*this).h0 = h0;
    (*this).fillColour = SGXCentral::noColour.getQColour();
    (*this).show();
    connect(SGXCentral::signalEmitter, resizeSignal, this, &SGXWidget::resizeObject);
    (*this).resizeObject();
}

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
    if(themeColourIndex == 0){(*this).fillColour = SGUCentralManagement::themeColour0.getQColour();}
    else if(themeColourIndex == 1){(*this).fillColour = SGUCentralManagement::themeColour1.getQColour();}
    else if(themeColourIndex == 2){(*this).fillColour = SGUCentralManagement::themeColour2.getQColour();}
    else if(themeColourIndex == 3){(*this).fillColour = SGUCentralManagement::themeColour3.getQColour();}
    else if(themeColourIndex == 4){(*this).fillColour = SGUCentralManagement::themeColour4.getQColour();}
    else if(themeColourIndex == 5){(*this).fillColour = SGUCentralManagement::themeColour5.getQColour();}
    else if(themeColourIndex == 6){(*this).fillColour = SGUCentralManagement::themeColour6.getQColour();}
    else if(themeColourIndex == 7){(*this).fillColour = SGUCentralManagement::themeColour7.getQColour();}
    else if(themeColourIndex == 8){(*this).fillColour = SGUCentralManagement::themeColour8.getQColour();}
    else{(*this).fillColour = SGXCentral::noColour.getQColour();}
    (*this).show();
    connect(SGXCentral::signalEmitter, resizeSignal, this, &SGXWidget::resizeObject);
    (*this).resizeObject();
}

void SGXWidget::setColour(){
    fillColour = SGXCentral::noColour.getQColour();
    update();
}

void SGXWidget::setColour(int themeColourIndex){
    if(themeColourIndex == 0){fillColour = SGUCentralManagement::themeColour0.getQColour();}
    else if(themeColourIndex == 1){fillColour = SGUCentralManagement::themeColour1.getQColour();}
    else if(themeColourIndex == 2){fillColour = SGUCentralManagement::themeColour2.getQColour();}
    else if(themeColourIndex == 3){fillColour = SGUCentralManagement::themeColour3.getQColour();}
    else if(themeColourIndex == 4){fillColour = SGUCentralManagement::themeColour4.getQColour();}
    else if(themeColourIndex == 5){fillColour = SGUCentralManagement::themeColour5.getQColour();}
    else if(themeColourIndex == 6){fillColour = SGUCentralManagement::themeColour6.getQColour();}
    else if(themeColourIndex == 7){fillColour = SGUCentralManagement::themeColour7.getQColour();}
    else if(themeColourIndex == 8){fillColour = SGUCentralManagement::themeColour8.getQColour();}
    else{fillColour = SGXCentral::noColour.getQColour();}
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
