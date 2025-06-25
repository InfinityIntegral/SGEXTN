#include "sgxquickuiinterface.h"
#include <QQuickItem>
#include <QQmlApplicationEngine>
#include "../quickui/sgxthemecoloursetting.h"
#include "../quickui/sgxquickresizer.h"
#include <QQmlComponent>
#include <QObject>
#include "../primitives/sgxtouchevent.h"
#include <bit>
#include <array>
#include <qcontainerfwd.h>

QQuickItem* SGXQuickUIInterface::rootWindow = nullptr;
QQmlApplicationEngine* SGXQuickUIInterface::e = nullptr;
SGXThemeColourSetting* SGXQuickUIInterface::themeColoursInstance = nullptr;
SGXQuickResizer* SGXQuickUIInterface::resizerInstance = nullptr;
QQmlComponent* SGXQuickUIInterface::rootWidgetTemplate = nullptr;
QQuickItem* SGXQuickUIInterface::rootWidget = nullptr;
QQmlComponent* SGXQuickUIInterface::parentWidgetTemplate = nullptr;
QQuickItem* SGXQuickUIInterface::parentWidget = nullptr;
QQmlComponent* SGXQuickUIInterface::widgetTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::textTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::longTextTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::iconTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::textButtonTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::iconButtonTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::inputFieldTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::longInputFieldTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::scrollViewTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::touchReceiverTemplate = nullptr;
QVector<void (*)(SGXTouchEvent*)>* SGXQuickUIInterface::touchEventFunctionsList = nullptr;

void SGXQuickUIInterface::initialise(){
    SGXQuickUIInterface::rootWidgetTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/rootwidget.qml");
    SGXQuickUIInterface::parentWidgetTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/parentwidget.qml");
    SGXQuickUIInterface::widgetTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/widget.qml");
    SGXQuickUIInterface::textTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/text.qml");
    SGXQuickUIInterface::longTextTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/longtext.qml");
    SGXQuickUIInterface::iconTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/icon.qml");
    SGXQuickUIInterface::textButtonTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/textbutton.qml");
    SGXQuickUIInterface::iconButtonTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/iconbutton.qml");
    SGXQuickUIInterface::inputFieldTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/inputfield.qml");
    SGXQuickUIInterface::longInputFieldTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/longinputfield.qml");
    SGXQuickUIInterface::scrollViewTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/scrollview.qml");
    SGXQuickUIInterface::touchReceiverTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/touchreceiver.qml");
}

void SGXQuickUIInterface::buildTemplate(){
    SGXQuickUIInterface::rootWidget = SGXQuickUIInterface::createRootWidget(SGXQuickUIInterface::rootWindow);
    SGXQuickUIInterface::parentWidget = SGXQuickUIInterface::createParentWidget(SGXQuickUIInterface::rootWidget);
}

QQuickItem* SGXQuickUIInterface::createRootWidget(QQuickItem *parent){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::rootWidgetTemplate).create());
    (*thisItem).setParentItem(parent);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createParentWidget(QQuickItem *parent){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::parentWidgetTemplate).create());
    (*thisItem).setParentItem(parent);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createWidget(QQuickItem *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int bg){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::widgetTemplate).create());
    (*thisItem).setParentItem(parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("h1", h1);
    (*thisItem).setProperty("h0", h0);
    (*thisItem).setProperty("bg", bg);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createText(QQuickItem *parent, const QString &s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::textTemplate).create());
    (*thisItem).setParentItem(parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("h1", h1);
    (*thisItem).setProperty("h0", h0);
    (*thisItem).setProperty("s", s);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createLongText(QQuickItem *parent, const QString &s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, float s1, float s0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::longTextTemplate).create());
    (*thisItem).setParentItem(parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("h1", h1);
    (*thisItem).setProperty("h0", h0);
    (*thisItem).setProperty("f1", f1);
    (*thisItem).setProperty("f0", f0);
    (*thisItem).setProperty("s1", s1);
    (*thisItem).setProperty("s0", s0);
    (*thisItem).setProperty("s", s);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createIcon(QQuickItem *parent, const QChar &s, float x1, float x0, float y1, float y0, float w1, float w0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::iconTemplate).create());
    (*thisItem).setParentItem(parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("s", s);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createTextButton(QQuickItem *parent, const QString &s, void (*attachedFunction)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::textButtonTemplate).create());
    (*thisItem).setParentItem(parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("h1", h1);
    (*thisItem).setProperty("h0", h0);
    (*thisItem).setProperty("s", s);
    connect(thisItem, &QQuickItem::objectNameChanged, attachedFunction);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createIconButton(QQuickItem *parent, const QChar &s, void (*attachedFunction)(), float x1, float x0, float y1, float y0, float w1, float w0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::iconButtonTemplate).create());
    (*thisItem).setParentItem(parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("s", s);
    connect(thisItem, &QQuickItem::objectNameChanged, attachedFunction);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createInputField(QQuickItem *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::inputFieldTemplate).create());
    (*thisItem).setParentItem(parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("h1", h1);
    (*thisItem).setProperty("h0", h0);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createLongInputField(QQuickItem *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, float s1, float s0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::longInputFieldTemplate).create());
    (*thisItem).setParentItem(parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("h1", h1);
    (*thisItem).setProperty("h0", h0);
    (*thisItem).setProperty("f1", f1);
    (*thisItem).setProperty("f0", f0);
    (*thisItem).setProperty("s1", s1);
    (*thisItem).setProperty("s0", s0);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createScrollView(QQuickItem *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float ih1, float ih0, float s1, float s0, int bg){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::scrollViewTemplate).create());
    (*thisItem).setParentItem(parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("h1", h1);
    (*thisItem).setProperty("h0", h0);
    (*thisItem).setProperty("ih1", ih1);
    (*thisItem).setProperty("ih0", ih0);
    (*thisItem).setProperty("s1", s1);
    (*thisItem).setProperty("s0", s0);
    (*thisItem).setProperty("bg", bg);
    return thisItem;
}

void SGXQuickUIInterface::receiveTouch(const QString &s){
    const unsigned long long iop = (s.mid(1)).toULongLong();
    QQuickItem* thisItem = std::bit_cast<QQuickItem*>(iop);
    
    std::array<float, 11> data = std::array<float, 11>();
    // [x, y, px, py, sx, sy, vx, vy, rx, ry, f]
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
        eventsToPass[0] = SGXTouchEvent(1, data.data());
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
        eventsToPass[1] = SGXTouchEvent(2, data.data());
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
        eventsToPass[2] = SGXTouchEvent(3, data.data());
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
        eventsToPass[3] = SGXTouchEvent(4, data.data());
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
        eventsToPass[4] = SGXTouchEvent(5, data.data());
    }
    else{eventsToPass[4] = SGXTouchEvent(5);}
    
    const int fpi = (*thisItem).property("functionPointer").toInt();
    void (*functionToRun)(SGXTouchEvent*) = (*SGXQuickUIInterface::touchEventFunctionsList)[fpi];
    functionToRun(eventsToPass.data());
}

QQuickItem* SGXQuickUIInterface::createTouchReceiver(QQuickItem *parent, void (*attachedFunction)(SGXTouchEvent *), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::touchReceiverTemplate).create());
    (*thisItem).setParentItem(parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("h1", h1);
    (*thisItem).setProperty("h0", h0);
    (*thisItem).setProperty("thisPointer", QString::number(std::bit_cast<unsigned long long>(thisItem)));
    if(SGXQuickUIInterface::touchEventFunctionsList == nullptr){
        SGXQuickUIInterface::touchEventFunctionsList = new QVector<void (*)(SGXTouchEvent*)>();
    }
    (*SGXQuickUIInterface::touchEventFunctionsList).append(attachedFunction);
    (*thisItem).setProperty("functionPointer", (*SGXQuickUIInterface::touchEventFunctionsList).length() - 1);
    connect(thisItem, &QQuickItem::stateChanged, &SGXQuickUIInterface::receiveTouch);
    return thisItem;
}
