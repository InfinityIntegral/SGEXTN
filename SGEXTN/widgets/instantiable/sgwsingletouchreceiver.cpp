#include "sgwsingletouchreceiver.h"
#include "../../quickui/sgxquickinterface.h"
#include "../noninstantiable/sgwwidget.h"
#include "../../primitives/sgxtouchevent.h"
#include <QQuickItem>
#include "../enums/sgwtype.h"
#include "../../primitives/sgxstring.h"
#include "../../quickui/sgwwidgetquickinterface.h"

SGWSingleTouchReceiver::SGWSingleTouchReceiver(SGWWidget *parent, void (*function)(const SGXTouchEvent &), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0) : SGWWidget(parent, x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).attachedInt = 0;
    (*this).attachedString = "";
    (*this).callbackFunction = function;
    (*this).callbackFunctionWithInt = nullptr;
    (*this).callbackFunctionWithString = nullptr;
    (*this).callbackFunctionWithPointer = nullptr;
    QQuickItem* thisItem = static_cast<QQuickItem*>((*SGXQuickInterface::singleTouchReceiver).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::SingleTouchReceiver;
    SGWWidget::syncQuickProperties();
    quickInterface = new SGWWidgetQuickInterface(this);
}

void SGWSingleTouchReceiver::eventReceived(const SGXString &s){
    if(s != "touched"){return;}
    QQuickItem* thisItem = topObject;
    SGLArray<float> data(11);
    SGXTouchEvent eventToPass = SGXTouchEvent();
    
    if((*thisItem).property("e1").toBool() == true){
        data.at(0) = (*thisItem).property("e1x").toFloat();
        data.at(1) = (*thisItem).property("e1y").toFloat();
        data.at(2) = (*thisItem).property("e1px").toFloat();
        data.at(3) = (*thisItem).property("e1py").toFloat();
        data.at(4) = (*thisItem).property("e1sx").toFloat();
        data.at(5) = (*thisItem).property("e1sy").toFloat();
        data.at(6) = (*thisItem).property("e1vx").toFloat();
        data.at(7) = (*thisItem).property("e1vy").toFloat();
        data.at(8) = (*thisItem).property("e1rx").toFloat();
        data.at(9) = (*thisItem).property("e1ry").toFloat();
        data.at(10) = (*thisItem).property("e1f").toFloat();
        eventToPass = SGXTouchEvent(1, data);
    }
    else{eventToPass = SGXTouchEvent(1);}
    
    if(callbackFunction != nullptr){callbackFunction(eventToPass);}
    if(callbackFunctionWithInt != nullptr){callbackFunctionWithInt(attachedInt, eventToPass);}
    if(callbackFunctionWithString != nullptr){callbackFunctionWithString(attachedString, eventToPass);}
    if(callbackFunctionWithPointer != nullptr){callbackFunctionWithPointer(this, eventToPass);}
}

float SGWSingleTouchReceiver::getWidth() const {
    return static_cast<float>((*topObject).width());
}

float SGWSingleTouchReceiver::getHeight() const {
    return static_cast<float>((*topObject).height());
}

SGWSingleTouchReceiver::~SGWSingleTouchReceiver(){
    (*quickInterface).deleteLater();
}
