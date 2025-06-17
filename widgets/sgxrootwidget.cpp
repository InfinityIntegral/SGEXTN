#include "sgxrootwidget.h"
#include "../misc/sgxcentral.h"
#include <QTimer>
#include <algorithm>
#include <QPainter>
#include "../userDefinedClasses/sgucentralmanagement.h"
#include <QPaintEvent>

SGXRootWidget::SGXRootWidget(){
    (*this).show();
    (*this).t = new QTimer(this); // NOLINT(cppcoreguidelines-owning-memory)
    connect(t, &QTimer::timeout, this, &SGXRootWidget::checkScreenSizeUpdate);
    (*t).start(16);
}

void SGXRootWidget::checkScreenSizeUpdate(){
    const float lw = SGXCentral::applicationWindowWidth;
    const float lh = SGXCentral::applicationWindowHeight;
    SGXCentral::applicationWindowWidth = static_cast<float>((*this).width());
    SGXCentral::applicationWindowHeight = static_cast<float>((*this).height());
    if(lw != SGXCentral::applicationWindowWidth || lh != SGXCentral::applicationWindowHeight){
        if(SGXCentral::applicationWindowWidth > 16.0f / 9.0f * SGXCentral::applicationWindowHeight){
            SGXCentral::renderAreaWidth = 16.0f / 9.0f * SGXCentral::applicationWindowHeight;
            SGXCentral::renderAreaHeight = SGXCentral::applicationWindowHeight;
        }
        else if(SGXCentral::applicationWindowHeight > 16.0f / 9.0f * SGXCentral::applicationWindowWidth){
            SGXCentral::renderAreaWidth = SGXCentral::applicationWindowWidth;
            SGXCentral::renderAreaHeight = 16.0f / 9.0f * SGXCentral::applicationWindowWidth;
        }
        else{
            SGXCentral::renderAreaWidth = SGXCentral::applicationWindowWidth;
            SGXCentral::renderAreaHeight = SGXCentral::applicationWindowHeight;
        }
        (*SGXCentral::signalEmitter).sendSignals();
    }
    SGXCentral::sizeUnit = std::max(SGXCentral::renderAreaWidth, SGXCentral::renderAreaHeight) / 24.0f;
}

void SGXRootWidget::paintEvent(QPaintEvent *){ // NOLINT(readability-named-parameter)
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), SGUCentralManagement::rootWindowColour.getQColour());
}
