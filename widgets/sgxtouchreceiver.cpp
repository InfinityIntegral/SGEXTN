#include "sgxtouchreceiver.h"
#include "../misc/sgxcentral.h"
#include <QPainter>
#include <QWidget>
#include "../userDefinedClasses/sgusignalemitter.h"
#include <QList>
#include "../primitives/sgxtouchevent.h"
#include <QtCore/Qt>
#include <QEvent>
#include <QTimer>
#include <QTouchEvent>
#include <utility>

SGXTouchReceiver::SGXTouchReceiver(QWidget *parent, void (SGUSignalEmitter::*resizeSignal)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    (*this).setParent(parent);
    (*this).scheduled = false;
    (*this).x1 = x1;
    (*this).x0 = x0;
    (*this).y1 = y1;
    (*this).y0 = y0;
    (*this).w1 = w1;
    (*this).w0 = w0;
    (*this).h1 = h1;
    (*this).h0 = h0;
    (*this).activeTouches = QList<SGXTouchEvent>();
    (*this).setAttribute(Qt::WA_AcceptTouchEvents);
    (*this).show();
    connect(SGXCentral::signalEmitter, resizeSignal, this, &SGXTouchReceiver::resizeObject);
    (*this).resizeObject();
}

void SGXTouchReceiver::resizeObject(){
    setGeometry(static_cast<int>(x1 * SGXCentral::renderAreaWidth + x0 * SGXCentral::sizeUnit), static_cast<int>(y1 * SGXCentral::renderAreaHeight + y0 * SGXCentral::sizeUnit), static_cast<int>(w1 * SGXCentral::renderAreaWidth + w0 * SGXCentral::sizeUnit), static_cast<int>(h1 * SGXCentral::renderAreaHeight + h0 * SGXCentral::sizeUnit));
}

void SGXTouchReceiver::paintEvent(QPaintEvent *){ // NOLINT(readability-named-parameter)
    QPainter p(this);
    p.fillRect(0, 0, width(), height(), SGXCentral::noColour.getQColour());
}

bool SGXTouchReceiver::event(QEvent *event){
    if((*event).type() == QEvent::TouchBegin || (*event).type() == QEvent::TouchUpdate || (*event).type() == QEvent::TouchEnd){
        QList<SGXTouchEvent> tempList = std::move(activeTouches);
        activeTouches = QList<SGXTouchEvent>();
        QTouchEvent* te = static_cast<QTouchEvent*>(event); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
        for(int i=0; i<(*te).points().length(); i++){
            const int targetID = (*te).points()[i].id();
            int idx = -1;
            for(int j=0; j<tempList.length(); j++){
                if(tempList[j].id == targetID){
                    idx = j;
                    break;
                }
            }
            if(idx == -1){activeTouches.push_back(SGXTouchEvent((*te).points()[i]));}
            else{activeTouches.push_back(SGXTouchEvent((*te).points()[i], tempList[idx]));}
        }
        if(scheduled == false){
            scheduled = true;
            QTimer::singleShot(0, this, &SGXTouchReceiver::processTouches);
        }
        return true;
    }
    if((*event).type() == QEvent::MouseButtonPress || (*event).type() == QEvent::MouseButtonRelease || (*event).type() == QEvent::MouseMove){return false;}
    return QWidget::event(event);
}

void SGXTouchReceiver::processTouches(){
    scheduled = false;
    process();
}
