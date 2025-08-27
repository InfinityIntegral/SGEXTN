#include "sgwtouchreceiver.h"
#include "../../quickui/sgxquickinterface.h"
#include "../noninstantiable/sgwwidget.h"
#include <array>
#include "../../primitives/sgxtouchevent.h"
#include <QQuickItem>
#include <QObject>
#include "../enums/sgwtype.h"
#include <QString>
#include "../../quickui/sgwwidgetquickinterface.h"

SGWTouchReceiver::SGWTouchReceiver(SGWWidget *parent, void (*function)(SGWTouchReceiver *, const std::array<SGXTouchEvent, 5> &), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0) : SGWWidget(parent, x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).function = function;
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickInterface::touchReceiver).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::TouchReceiver;
    SGWWidget::syncQuickProperties();
    quickInterface = new SGWWidgetQuickInterface(this);
}

void SGWTouchReceiver::eventReceived(const QString &s){
    if(s != "touched"){return;}
    QQuickItem* thisItem = topObject;
    std::array<float, 11> data = std::array<float, 11>();
    std::array<SGXTouchEvent, 5> eventsToPass = std::array<SGXTouchEvent, 5>();

    if((*thisItem).property("e1").toBool() == true){
        data[0] = (*thisItem).property("e1x").toFloat();
        data[1] = (*thisItem).property("e1y").toFloat();
        data[2] = (*thisItem).property("e1px").toFloat();
        data[3] = (*thisItem).property("e1py").toFloat();
        data[4] = (*thisItem).property("e1sx").toFloat();
        data[5] = (*thisItem).property("e1sy").toFloat();
        data[6] = (*thisItem).property("e1vx").toFloat();
        data[7] = (*thisItem).property("e1vy").toFloat();
        data[8] = (*thisItem).property("e1rx").toFloat();
        data[9] = (*thisItem).property("e1ry").toFloat();
        data[10] = (*thisItem).property("e1f").toFloat();
        eventsToPass[0] = SGXTouchEvent(1, data);
    }
    else{eventsToPass[0] = SGXTouchEvent(1);}

    if((*thisItem).property("e2").toBool() == true){
        data[0] = (*thisItem).property("e2x").toFloat();
        data[1] = (*thisItem).property("e2y").toFloat();
        data[2] = (*thisItem).property("e2px").toFloat();
        data[3] = (*thisItem).property("e2py").toFloat();
        data[4] = (*thisItem).property("e2sx").toFloat();
        data[5] = (*thisItem).property("e2sy").toFloat();
        data[6] = (*thisItem).property("e2vx").toFloat();
        data[7] = (*thisItem).property("e2vy").toFloat();
        data[8] = (*thisItem).property("e2rx").toFloat();
        data[9] = (*thisItem).property("e2ry").toFloat();
        data[10] = (*thisItem).property("e2f").toFloat();
        eventsToPass[1] = SGXTouchEvent(2, data);
    }
    else{eventsToPass[1] = SGXTouchEvent(2);}

    if((*thisItem).property("e3").toBool() == true){
        data[0] = (*thisItem).property("e3x").toFloat();
        data[1] = (*thisItem).property("e3y").toFloat();
        data[2] = (*thisItem).property("e3px").toFloat();
        data[3] = (*thisItem).property("e3py").toFloat();
        data[4] = (*thisItem).property("e3sx").toFloat();
        data[5] = (*thisItem).property("e3sy").toFloat();
        data[6] = (*thisItem).property("e3vx").toFloat();
        data[7] = (*thisItem).property("e3vy").toFloat();
        data[8] = (*thisItem).property("e3rx").toFloat();
        data[9] = (*thisItem).property("e3ry").toFloat();
        data[10] = (*thisItem).property("e3f").toFloat();
        eventsToPass[2] = SGXTouchEvent(3, data);
    }
    else{eventsToPass[2] = SGXTouchEvent(3);}

    if((*thisItem).property("e4").toBool() == true){
        data[0] = (*thisItem).property("e4x").toFloat();
        data[1] = (*thisItem).property("e4y").toFloat();
        data[2] = (*thisItem).property("e4px").toFloat();
        data[3] = (*thisItem).property("e4py").toFloat();
        data[4] = (*thisItem).property("e4sx").toFloat();
        data[5] = (*thisItem).property("e4sy").toFloat();
        data[6] = (*thisItem).property("e4vx").toFloat();
        data[7] = (*thisItem).property("e4vy").toFloat();
        data[8] = (*thisItem).property("e4rx").toFloat();
        data[9] = (*thisItem).property("e4ry").toFloat();
        data[10] = (*thisItem).property("e4f").toFloat();
        eventsToPass[3] = SGXTouchEvent(4, data);
    }
    else{eventsToPass[3] = SGXTouchEvent(4);}

    if((*thisItem).property("e5").toBool() == true){
        data[0] = (*thisItem).property("e5x").toFloat();
        data[1] = (*thisItem).property("e5y").toFloat();
        data[2] = (*thisItem).property("e5px").toFloat();
        data[3] = (*thisItem).property("e5py").toFloat();
        data[4] = (*thisItem).property("e5sx").toFloat();
        data[5] = (*thisItem).property("e5sy").toFloat();
        data[6] = (*thisItem).property("e5vx").toFloat();
        data[7] = (*thisItem).property("e5vy").toFloat();
        data[8] = (*thisItem).property("e5rx").toFloat();
        data[9] = (*thisItem).property("e5ry").toFloat();
        data[10] = (*thisItem).property("e5f").toFloat();
        eventsToPass[4] = SGXTouchEvent(5, data);
    }
    else{eventsToPass[4] = SGXTouchEvent(5);}

    (*this).function(this, eventsToPass);
}

float SGWTouchReceiver::getWidth() const {
    return static_cast<float>((*topObject).width());
}

float SGWTouchReceiver::getHeight() const {
    return static_cast<float>((*topObject).height());
}

SGWTouchReceiver::~SGWTouchReceiver(){
    (*quickInterface).deleteLater();
}
