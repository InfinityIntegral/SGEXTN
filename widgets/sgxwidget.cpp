#include "sgxwidget.h"
#include "../misc/sgxcentral.h"
#include <QPainter>
#include "../userDefinedClasses/sgucentralmanagement.h"

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
    (*this).colourMode = 0;
    (*this).themeColourIndex = 0;
    (*this).customColour = SGXCentral::noColour;
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
    (*this).colourMode = 1;
    (*this).themeColourIndex = themeColourIndex;
    (*this).customColour = SGXCentral::noColour;
    (*this).show();
    connect(SGXCentral::signalEmitter, resizeSignal, this, &SGXWidget::resizeObject);
    (*this).resizeObject();
}

SGXWidget::SGXWidget(QWidget *parent, void (SGUSignalEmitter::*resizeSignal)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGXColourRGBA customColour){
    (*this).setParent(parent);
    (*this).x1 = x1;
    (*this).x0 = x0;
    (*this).y1 = y1;
    (*this).y0 = y0;
    (*this).w1 = w1;
    (*this).w0 = w0;
    (*this).h1 = h1;
    (*this).h0 = h0;
    (*this).colourMode = -1;
    (*this).themeColourIndex = 0;
    (*this).customColour = customColour;
    (*this).show();
    connect(SGXCentral::signalEmitter, resizeSignal, this, &SGXWidget::resizeObject);
    (*this).resizeObject();
}

void SGXWidget::resizeObject(){
    setGeometry(x1 * SGXCentral::renderAreaWidth + x0 * SGXCentral::sizeUnit, y1 * SGXCentral::renderAreaHeight + y0 * SGXCentral::sizeUnit, w1 * SGXCentral::renderAreaWidth + w0 * SGXCentral::sizeUnit, h1 + SGXCentral::renderAreaHeight + h0 * SGXCentral::sizeUnit);
}

void SGXWidget::paintEvent(QPaintEvent *){
    QPainter p(this);
    QColor fillColour;
    if(colourMode == 0){fillColour = SGXCentral::noColour.getQColour();}
    else if(colourMode == 1){
        if(themeColourIndex == 0){fillColour = SGUCentralManagement::themeColour0.getQColour();}
        else if(themeColourIndex == 1){fillColour = SGUCentralManagement::themeColour1.getQColour();}
        else if(themeColourIndex == 2){fillColour = SGUCentralManagement::themeColour2.getQColour();}
        else if(themeColourIndex == 3){fillColour = SGUCentralManagement::themeColour3.getQColour();}
        else if(themeColourIndex == 4){fillColour = SGUCentralManagement::themeColour4.getQColour();}
        else if(themeColourIndex == 5){fillColour = SGUCentralManagement::themeColour5.getQColour();}
        else if(themeColourIndex == 6){fillColour = SGUCentralManagement::themeColour6.getQColour();}
        else if(themeColourIndex == 7){fillColour = SGUCentralManagement::themeColour7.getQColour();}
        else{fillColour = SGUCentralManagement::themeColour8.getQColour();}
    }
    else{fillColour = customColour.getQColour();}
    p.fillRect(0, 0, width(), height(), fillColour);
}
