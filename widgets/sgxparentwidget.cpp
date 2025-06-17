#include "sgxparentwidget.h"
#include <QPainter>
#include "../misc/sgxcentral.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include "../userDefinedClasses/sgusignalemitter.h"
#include <cmath>
#include <QPaintEvent>

SGXParentWidget::SGXParentWidget(){
    (*this).setParent(SGXCentral::rootWindow);
    (*this).show();
    connect(SGXCentral::signalEmitter, &SGUSignalEmitter::updateScreen, this, &SGXParentWidget::resizeObject);
    (*this).resizeObject();
}

void SGXParentWidget::resizeObject(){
    if(SGXCentral::applicationWindowWidth > 16.0f / 9.0f * SGXCentral::applicationWindowHeight){
        setGeometry(static_cast<int>(std::roundf(0.5f * (SGXCentral::applicationWindowWidth - SGXCentral::renderAreaWidth))), 0, static_cast<int>(std::roundf(SGXCentral::renderAreaWidth)), static_cast<int>(std::roundf(SGXCentral::renderAreaHeight)));
    }
    else if(SGXCentral::applicationWindowHeight > 16.0f / 9.0f * SGXCentral::applicationWindowWidth){
        setGeometry(0, static_cast<int>(std::roundf(0.5f * (SGXCentral::applicationWindowHeight - SGXCentral::renderAreaHeight))), static_cast<int>(std::roundf(SGXCentral::renderAreaWidth)), static_cast<int>(std::roundf(SGXCentral::renderAreaHeight)));
    }
    else{
        setGeometry(0, 0, static_cast<int>(std::roundf(SGXCentral::renderAreaWidth)), static_cast<int>(std::roundf(SGXCentral::renderAreaHeight)));
    }
}

void SGXParentWidget::paintEvent(QPaintEvent *){ // NOLINT(readability-named-parameter)
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), SGUCentralManagement::renderSpaceColour.getQColour());
}
