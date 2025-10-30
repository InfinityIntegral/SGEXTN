#include <SGWMultiTouchReceiver.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <SGWWidget.h>
#include <SGXTouchEvent.h>
#include <QQuickItem>
#include <SGWType.h>
#include <SGXString.h>
#include <private_api_Widgets/SGWWidgetQuickInterface.h>
#include <SGLArray.h>

SGWMultiTouchReceiver::SGWMultiTouchReceiver(SGWWidget *parent, void (*function)(const SGLArray<SGXTouchEvent> &), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0) : SGWWidget(parent, x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).attachedInt = 0;
    (*this).attachedString = "";
    (*this).callbackFunction = function;
    (*this).callbackFunctionWithInt = nullptr;
    (*this).callbackFunctionWithString = nullptr;
    (*this).callbackFunctionWithPointer = nullptr;
    QQuickItem* thisItem = static_cast<QQuickItem*>((*SGXQuickInterface::multiTouchReceiver).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::MultiTouchReceiver;
    SGWWidget::syncQuickProperties();
    quickInterface = new SGWWidgetQuickInterface(this);
}

void SGWMultiTouchReceiver::eventReceived(const SGXString &s){
    if(s != "touched"){return;}
    QQuickItem* thisItem = topObject;
    SGLArray<float> data(11);
    SGLArray<SGXTouchEvent> eventsToPass(5);

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
        eventsToPass.at(0) = SGXTouchEvent(1, data);
    }
    else{eventsToPass.at(0) = SGXTouchEvent(1);}

    if((*thisItem).property("e2").toBool() == true){
        data.at(0) = (*thisItem).property("e2x").toFloat();
        data.at(1) = (*thisItem).property("e2y").toFloat();
        data.at(2) = (*thisItem).property("e2px").toFloat();
        data.at(3) = (*thisItem).property("e2py").toFloat();
        data.at(4) = (*thisItem).property("e2sx").toFloat();
        data.at(5) = (*thisItem).property("e2sy").toFloat();
        data.at(6) = (*thisItem).property("e2vx").toFloat();
        data.at(7) = (*thisItem).property("e2vy").toFloat();
        data.at(8) = (*thisItem).property("e2rx").toFloat();
        data.at(9) = (*thisItem).property("e2ry").toFloat();
        data.at(10) = (*thisItem).property("e2f").toFloat();
        eventsToPass.at(1) = SGXTouchEvent(2, data);
    }
    else{eventsToPass.at(1) = SGXTouchEvent(2);}

    if((*thisItem).property("e3").toBool() == true){
        data.at(0) = (*thisItem).property("e3x").toFloat();
        data.at(1) = (*thisItem).property("e3y").toFloat();
        data.at(2) = (*thisItem).property("e3px").toFloat();
        data.at(3) = (*thisItem).property("e3py").toFloat();
        data.at(4) = (*thisItem).property("e3sx").toFloat();
        data.at(5) = (*thisItem).property("e3sy").toFloat();
        data.at(6) = (*thisItem).property("e3vx").toFloat();
        data.at(7) = (*thisItem).property("e3vy").toFloat();
        data.at(8) = (*thisItem).property("e3rx").toFloat();
        data.at(9) = (*thisItem).property("e3ry").toFloat();
        data.at(10) = (*thisItem).property("e3f").toFloat();
        eventsToPass.at(2) = SGXTouchEvent(3, data);
    }
    else{eventsToPass.at(2) = SGXTouchEvent(3);}

    if((*thisItem).property("e4").toBool() == true){
        data.at(0) = (*thisItem).property("e4x").toFloat();
        data.at(1) = (*thisItem).property("e4y").toFloat();
        data.at(2) = (*thisItem).property("e4px").toFloat();
        data.at(3) = (*thisItem).property("e4py").toFloat();
        data.at(4) = (*thisItem).property("e4sx").toFloat();
        data.at(5) = (*thisItem).property("e4sy").toFloat();
        data.at(6) = (*thisItem).property("e4vx").toFloat();
        data.at(7) = (*thisItem).property("e4vy").toFloat();
        data.at(8) = (*thisItem).property("e4rx").toFloat();
        data.at(9) = (*thisItem).property("e4ry").toFloat();
        data.at(10) = (*thisItem).property("e4f").toFloat();
        eventsToPass.at(3) = SGXTouchEvent(4, data);
    }
    else{eventsToPass.at(3) = SGXTouchEvent(4);}

    if((*thisItem).property("e5").toBool() == true){
        data.at(0) = (*thisItem).property("e5x").toFloat();
        data.at(1) = (*thisItem).property("e5y").toFloat();
        data.at(2) = (*thisItem).property("e5px").toFloat();
        data.at(3) = (*thisItem).property("e5py").toFloat();
        data.at(4) = (*thisItem).property("e5sx").toFloat();
        data.at(5) = (*thisItem).property("e5sy").toFloat();
        data.at(6) = (*thisItem).property("e5vx").toFloat();
        data.at(7) = (*thisItem).property("e5vy").toFloat();
        data.at(8) = (*thisItem).property("e5rx").toFloat();
        data.at(9) = (*thisItem).property("e5ry").toFloat();
        data.at(10) = (*thisItem).property("e5f").toFloat();
        eventsToPass.at(4) = SGXTouchEvent(5, data);
    }
    else{eventsToPass.at(4) = SGXTouchEvent(5);}

    if(callbackFunction != nullptr){callbackFunction(eventsToPass);}
    if(callbackFunctionWithInt != nullptr){callbackFunctionWithInt(attachedInt, eventsToPass);}
    if(callbackFunctionWithString != nullptr){callbackFunctionWithString(attachedString, eventsToPass);}
    if(callbackFunctionWithPointer != nullptr){callbackFunctionWithPointer(this, eventsToPass);}
}

float SGWMultiTouchReceiver::getWidth() const {
    return static_cast<float>((*topObject).width());
}

float SGWMultiTouchReceiver::getHeight() const {
    return static_cast<float>((*topObject).height());
}

SGWMultiTouchReceiver::~SGWMultiTouchReceiver(){
    (*quickInterface).deleteLater();
}
