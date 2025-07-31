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
#include <QQueue>
#include <utility>
#include <QQuickWindow>
#include "../template/sgxstatusbar.h"
#include <QTimer>
#include "../template/sgxcutevesicles.h"
#include "../template/sgxcolourpicker.h"
#include "../primitives/sgxcolourrgba.h"

QQuickWindow* SGXQuickUIInterface::applicationWindow = nullptr;
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
QQmlComponent* SGXQuickUIInterface::titleTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::rightTextTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::longTextTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::iconTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::textButtonTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::iconButtonTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::inputFieldTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::longInputFieldTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::scrollViewTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::touchReceiverTemplate = nullptr;
QVector<void (*)(const std::array<SGXTouchEvent, 5>&)>* SGXQuickUIInterface::touchEventFunctionsList = nullptr;
QQmlComponent* SGXQuickUIInterface::cuteVesiclesTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::statusBarTemplate = nullptr;
QQmlComponent* SGXQuickUIInterface::colourPickerTemplate = nullptr;

void SGXQuickUIInterface::initialise(){
    SGXQuickUIInterface::rootWidgetTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/QML/rootwidget.qml");
    SGXQuickUIInterface::parentWidgetTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/QML/parentwidget.qml");
    SGXQuickUIInterface::widgetTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/QML/widget.qml");
    SGXQuickUIInterface::textTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/QML/text.qml");
    SGXQuickUIInterface::titleTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/QML/title.qml");
    SGXQuickUIInterface::rightTextTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/QML/righttext.qml");
    SGXQuickUIInterface::longTextTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/QML/longtext.qml");
    SGXQuickUIInterface::iconTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/QML/icon.qml");
    SGXQuickUIInterface::textButtonTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/QML/textbutton.qml");
    SGXQuickUIInterface::iconButtonTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/QML/iconbutton.qml");
    SGXQuickUIInterface::inputFieldTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/QML/inputfield.qml");
    SGXQuickUIInterface::longInputFieldTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/QML/longinputfield.qml");
    SGXQuickUIInterface::scrollViewTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/QML/scrollview.qml");
    SGXQuickUIInterface::touchReceiverTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/QML/touchreceiver.qml");
    SGXQuickUIInterface::cuteVesiclesTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/cutevesicles/cutevesicles.qml");
    SGXQuickUIInterface::statusBarTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/QML/statusbar.qml");
    SGXQuickUIInterface::colourPickerTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/SGEXTN/QML/colourpicker.qml");
}

void SGXQuickUIInterface::terminate(){
    delete SGXQuickUIInterface::resizerInstance;
    delete SGXQuickUIInterface::themeColoursInstance;
    delete SGXQuickUIInterface::touchEventFunctionsList;
    delete SGXQuickUIInterface::rootWidgetTemplate;
    delete SGXQuickUIInterface::parentWidgetTemplate;
    delete SGXQuickUIInterface::widgetTemplate;
    delete SGXQuickUIInterface::textTemplate;
    delete SGXQuickUIInterface::titleTemplate;
    delete SGXQuickUIInterface::rightTextTemplate;
    delete SGXQuickUIInterface::longTextTemplate;
    delete SGXQuickUIInterface::iconTemplate;
    delete SGXQuickUIInterface::textButtonTemplate;
    delete SGXQuickUIInterface::iconButtonTemplate;
    delete SGXQuickUIInterface::inputFieldTemplate;
    delete SGXQuickUIInterface::longInputFieldTemplate;
    delete SGXQuickUIInterface::scrollViewTemplate;
    delete SGXQuickUIInterface::touchReceiverTemplate;
    delete SGXQuickUIInterface::cuteVesiclesTemplate;
    delete SGXQuickUIInterface::statusBarTemplate;
    delete SGXQuickUIInterface::colourPickerTemplate;
}

void SGXQuickUIInterface::buildTemplate(){
    SGXQuickUIInterface::rootWidget = SGXQuickUIInterface::createRootWidget(SGXQuickUIInterface::rootWindow);
    SGXQuickUIInterface::parentWidget = SGXQuickUIInterface::createParentWidget(SGXQuickUIInterface::rootWidget);
    SGXStatusBar::instance = SGXQuickUIInterface::createStatusBar(SGXQuickUIInterface::rootWidget);
    connect(SGXStatusBar::instance, &QQuickItem::objectNameChanged, &SGXCuteVesicles::toggleAnimation);
    SGXStatusBar::timer = new QTimer(SGXStatusBar::instance);
    connect(SGXStatusBar::timer, &QTimer::timeout, &SGXStatusBar::updateTime);
    (*SGXStatusBar::timer).start(1000);
    SGXStatusBar::updateTime();
}

QQuickItem* SGXQuickUIInterface::createRootWidget(QQuickItem *parent){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::rootWidgetTemplate).create());
    (*thisItem).setParentItem(parent);
    (*thisItem).setParent(parent);
    (*thisItem).setProperty("widgetType", SGXQuickUIInterface::RootWidget);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createParentWidget(QQuickItem *parent){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::parentWidgetTemplate).create());
    (*thisItem).setParentItem(parent);
    (*thisItem).setParent(parent);
    (*thisItem).setProperty("widgetType", SGXQuickUIInterface::ParentWidget);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createWidget(QQuickItem *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int bg, bool frequentlyUsed){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::widgetTemplate).create());
    SGXQuickUIInterface::setActualParent(thisItem, parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("h1", h1);
    (*thisItem).setProperty("h0", h0);
    (*thisItem).setProperty("bg", bg);
    (*thisItem).setProperty("widgetType", SGXQuickUIInterface::Widget);
    (*thisItem).setProperty("frequentlyUsed", frequentlyUsed);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createText(QQuickItem *parent, const QString &s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::textTemplate).create());
    SGXQuickUIInterface::setActualParent(thisItem, parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("h1", h1);
    (*thisItem).setProperty("h0", h0);
    (*thisItem).setProperty("s", s);
    (*thisItem).setProperty("widgetType", SGXQuickUIInterface::Text);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createTitle(QQuickItem *parent, const QString &s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::titleTemplate).create());
    SGXQuickUIInterface::setActualParent(thisItem, parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("h1", h1);
    (*thisItem).setProperty("h0", h0);
    (*thisItem).setProperty("s", s);
    (*thisItem).setProperty("widgetType", SGXQuickUIInterface::Title);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createRightText(QQuickItem *parent, const QString &s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::rightTextTemplate).create());
    SGXQuickUIInterface::setActualParent(thisItem, parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("h1", h1);
    (*thisItem).setProperty("h0", h0);
    (*thisItem).setProperty("s", s);
    (*thisItem).setProperty("widgetType", SGXQuickUIInterface::RightText);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createLongText(QQuickItem *parent, const QString &s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, float s1, float s0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::longTextTemplate).create());
    SGXQuickUIInterface::setActualParent(thisItem, parent);
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
    (*thisItem).setProperty("widgetType", SGXQuickUIInterface::LongText);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createIcon(QQuickItem *parent, const QChar &s, float x1, float x0, float y1, float y0, float w1, float w0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::iconTemplate).create());
    SGXQuickUIInterface::setActualParent(thisItem, parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("s", s);
    (*thisItem).setProperty("widgetType", SGXQuickUIInterface::Icon);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createTextButton(QQuickItem *parent, const QString &s, void (*attachedFunction)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::textButtonTemplate).create());
    SGXQuickUIInterface::setActualParent(thisItem, parent);
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
    (*thisItem).setProperty("widgetType", SGXQuickUIInterface::TextButton);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createIconButton(QQuickItem *parent, const QChar &s, void (*attachedFunction)(), float x1, float x0, float y1, float y0, float w1, float w0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::iconButtonTemplate).create());
    SGXQuickUIInterface::setActualParent(thisItem, parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("s", s);
    connect(thisItem, &QQuickItem::objectNameChanged, attachedFunction);
    (*thisItem).setProperty("widgetType", SGXQuickUIInterface::IconButton);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createInputField(QQuickItem *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::inputFieldTemplate).create());
    SGXQuickUIInterface::setActualParent(thisItem, parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("h1", h1);
    (*thisItem).setProperty("h0", h0);
    (*thisItem).setProperty("widgetType", SGXQuickUIInterface::InputField);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createLongInputField(QQuickItem *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, float s1, float s0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::longInputFieldTemplate).create());
    SGXQuickUIInterface::setActualParent(thisItem, parent);
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
    (*thisItem).setProperty("widgetType", SGXQuickUIInterface::LongInputField);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createScrollView(QQuickItem *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float ih1, float ih0, float s1, float s0, int bg, bool frequentlyUsed){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::scrollViewTemplate).create());
    SGXQuickUIInterface::setActualParent(thisItem, parent);
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
    (*thisItem).setProperty("widgetType", SGXQuickUIInterface::ScrollView);
    (*thisItem).setProperty("frequentlyUsed", frequentlyUsed);
    return thisItem;
}

void SGXQuickUIInterface::receiveTouch(){
    QQuickItem* thisItem = SGXQuickUIInterface::getActiveObject();
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
    
    const int fpi = (*thisItem).property("functionPointer").toInt();
    void (*functionToRun)(const std::array<SGXTouchEvent, 5>&) = (*SGXQuickUIInterface::touchEventFunctionsList)[fpi];
    functionToRun(eventsToPass);
}

QQuickItem* SGXQuickUIInterface::createTouchReceiver(QQuickItem *parent, void (*attachedFunction)(const std::array<SGXTouchEvent, 5> &), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::touchReceiverTemplate).create());
    SGXQuickUIInterface::setActualParent(thisItem, parent);
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
        SGXQuickUIInterface::touchEventFunctionsList = new QVector<void (*)(const std::array<SGXTouchEvent, 5>&)>();
    }
    (*SGXQuickUIInterface::touchEventFunctionsList).append(attachedFunction);
    (*thisItem).setProperty("functionPointer", (*SGXQuickUIInterface::touchEventFunctionsList).length() - 1);
    connect(thisItem, &QQuickItem::objectNameChanged, &SGXQuickUIInterface::receiveTouch);
    (*thisItem).setProperty("widgetType", SGXQuickUIInterface::TouchReceiver);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createCuteVesicles(QQuickItem *parent){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::cuteVesiclesTemplate).create());
    (*thisItem).setParentItem(parent);
    (*thisItem).setParent(parent);
    (*thisItem).setProperty("widgetType", SGXQuickUIInterface::CuteVesicles);
    return thisItem;
}

SGXQuickUIInterface::WidgetType SGXQuickUIInterface::getType(QQuickItem *x){
    const int v = (*x).property("widgetType").toInt();
    if(v == SGXQuickUIInterface::Undefined){return SGXQuickUIInterface::Undefined;}
    if(v == SGXQuickUIInterface::RootWidget){return SGXQuickUIInterface::RootWidget;}
    if(v == SGXQuickUIInterface::ParentWidget){return SGXQuickUIInterface::ParentWidget;}
    if(v == SGXQuickUIInterface::Widget){return SGXQuickUIInterface::Widget;}
    if(v == SGXQuickUIInterface::Text){return SGXQuickUIInterface::Text;}
    if(v == SGXQuickUIInterface::Title){return SGXQuickUIInterface::Title;}
    if(v == SGXQuickUIInterface::RightText){return SGXQuickUIInterface::RightText;}
    if(v == SGXQuickUIInterface::LongText){return SGXQuickUIInterface::LongText;}
    if(v == SGXQuickUIInterface::Icon){return SGXQuickUIInterface::Icon;}
    if(v == SGXQuickUIInterface::TextButton){return SGXQuickUIInterface::TextButton;}
    if(v == SGXQuickUIInterface::IconButton){return SGXQuickUIInterface::IconButton;}
    if(v == SGXQuickUIInterface::InputField){return SGXQuickUIInterface::InputField;}
    if(v == SGXQuickUIInterface::LongInputField){return SGXQuickUIInterface::LongInputField;}
    if(v == SGXQuickUIInterface::ScrollView){return SGXQuickUIInterface::ScrollView;}
    if(v == SGXQuickUIInterface::TouchReceiver){return SGXQuickUIInterface::TouchReceiver;}
    if(v == SGXQuickUIInterface::CuteVesicles){return SGXQuickUIInterface::CuteVesicles;}
    if(v == SGXQuickUIInterface::StatusBar){return SGXQuickUIInterface::StatusBar;}
    if(v == SGXQuickUIInterface::ColourPicker){return SGXQuickUIInterface::ColourPicker;}
    return SGXQuickUIInterface::Undefined;
}

QQuickItem* SGXQuickUIInterface::getActualParentableObject(QQuickItem *x){
    if(SGXQuickUIInterface::getType(x) == SGXQuickUIInterface::RootWidget || SGXQuickUIInterface::getType(x) == SGXQuickUIInterface::ParentWidget || SGXQuickUIInterface::getType(x) == SGXQuickUIInterface::Widget){return x;}
    if(SGXQuickUIInterface::getType(x) != SGXQuickUIInterface::ScrollView){return nullptr;}
    QQueue<QQuickItem*> childrenList = QQueue<QQuickItem*>();
    childrenList.enqueue(x);
    while(childrenList.length() > 0){
        QQuickItem* i = childrenList.dequeue();
        if((*i).property("canParent").toBool() == true){return i;}
        QList<QQuickItem*> thisChildren = (*i).childItems();
        for(int idx = 0; idx < thisChildren.length(); idx++){
            childrenList.enqueue(thisChildren[idx]);
        }
    }
    return nullptr;
}

void SGXQuickUIInterface::setActualParent(QQuickItem *obj, QQuickItem *x){
    QQuickItem* actualParent = SGXQuickUIInterface::getActualParentableObject(x);
    if(actualParent == nullptr){std::abort();}
    // crashes the app if the parent is not set properly to avoid memory leaks
    // if your intention is to make another window, SGEXTN does not support it, try using native Qt stuff or making changes to main.cpp and SGXCentral::initialise() or write your own code to make another native window
    // only widgets and scroll views can take children, it simply does not make sense for anything else
    // if you really want to get the overlap effect as if a text has a child widget, place them side by side in a shared parent widget with background set to -1
    (*obj).setParentItem(actualParent);
    (*obj).setParent(actualParent);
}

QString SGXQuickUIInterface::getInputFieldDataAsString(QQuickItem *x, bool &isValid){
    if(SGXQuickUIInterface::getType(x) != SGXQuickUIInterface::InputField && SGXQuickUIInterface::getType(x) != SGXQuickUIInterface::LongInputField){
        isValid = false;
        return "";
    }
    QQueue<QQuickItem*> childrenList = QQueue<QQuickItem*>();
    childrenList.enqueue(x);
    while(childrenList.length() > 0){
        QQuickItem* i = childrenList.dequeue();
        if((*i).property("isInputField").toBool() == true){
            isValid = true;
            return (*i).property("text").toString();
        }
        QList<QQuickItem*> thisChildren = (*i).childItems();
        for(int idx = 0; idx < thisChildren.length(); idx++){
            childrenList.enqueue(thisChildren[idx]);
        }
    }
    isValid = false;
    return "";
}

int SGXQuickUIInterface::getInputFieldDataAsInt(QQuickItem *x, bool &isValid){
    const QString s = SGXQuickUIInterface::getInputFieldDataAsString(x, isValid);
    if(isValid == false){return 0;}
    const int i = s.toInt(&isValid);
    if(isValid == false){return 0;}
    return i;
}

float SGXQuickUIInterface::getInputFieldDataAsFloat(QQuickItem *x, bool &isValid){
    const QString s = SGXQuickUIInterface::getInputFieldDataAsString(x, isValid);
    if(isValid == false){return 0;}
    const float i = s.toFloat(&isValid);
    if(isValid == false){return 0;}
    return i;
}

QQuickItem* SGXQuickUIInterface::getActiveObject(){
    QQuickItem* x = (*SGXQuickUIInterface::applicationWindow).activeFocusItem();
    while(x != nullptr && SGXQuickUIInterface::getType(x) == SGXQuickUIInterface::Undefined){x = (*x).parentItem();}
    return x;
}

QQuickItem* SGXQuickUIInterface::createStatusBar(QQuickItem *parent){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::statusBarTemplate).create());
    (*thisItem).setParentItem(parent);
    (*thisItem).setParent(parent);
    (*thisItem).setProperty("widgetType", SGXQuickUIInterface::StatusBar);
    return thisItem;
}

QQuickItem* SGXQuickUIInterface::createColourPicker(QQuickItem *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGXColourRGBA defaultColour){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::colourPickerTemplate).create());
    SGXQuickUIInterface::setActualParent(thisItem, parent);
    (*thisItem).setProperty("x1", x1);
    (*thisItem).setProperty("x0", x0);
    (*thisItem).setProperty("y1", y1);
    (*thisItem).setProperty("y0", y0);
    (*thisItem).setProperty("w1", w1);
    (*thisItem).setProperty("w0", w0);
    (*thisItem).setProperty("h1", h1);
    (*thisItem).setProperty("h0", h0);
    (*thisItem).setProperty("c", defaultColour.getQColour());
    (*thisItem).setProperty("widgetType", SGXQuickUIInterface::ColourPicker);
    connect(thisItem, &QQuickItem::objectNameChanged, &SGXColourPicker::activate);
    return thisItem;
}

SGXColourRGBA SGXQuickUIInterface::getColourPickerColour(QQuickItem *x, bool &isValid){
    if(SGXQuickUIInterface::getType(x) != SGXQuickUIInterface::ColourPicker){
        isValid = false;
        return SGXColourRGBA(255, 255, 255, 0);
    }
    return SGXColourRGBA((*x).property("c").value<QColor>());
}

bool SGXQuickUIInterface::setInputFieldDataUsingString(QQuickItem *x, const QString &s){
    if(SGXQuickUIInterface::getType(x) != SGXQuickUIInterface::InputField && SGXQuickUIInterface::getType(x) != SGXQuickUIInterface::LongInputField){return false;}
    QQueue<QQuickItem*> childrenList = QQueue<QQuickItem*>();
    childrenList.enqueue(x);
    while(childrenList.length() > 0){
        QQuickItem* i = childrenList.dequeue();
        if((*i).property("isInputField").toBool() == true){
            (*i).setProperty("text", s);
            return true;
        }
        QList<QQuickItem*> thisChildren = (*i).childItems();
        for(int idx = 0; idx < thisChildren.length(); idx++){
            childrenList.enqueue(thisChildren[idx]);
        }
    }
    return false;
}

bool SGXQuickUIInterface::setInputFieldDataUsingInt(QQuickItem *x, int s){
    return SGXQuickUIInterface::setInputFieldDataUsingString(x, QString::number(s));
}

bool SGXQuickUIInterface::setInputFieldDataUsingFloat(QQuickItem *x, float s){
    return SGXQuickUIInterface::setInputFieldDataUsingString(x, QString::number(s));
}

bool SGXQuickUIInterface::setColourPickerColour(QQuickItem *x, SGXColourRGBA c){
    if(SGXQuickUIInterface::getType(x) != SGXQuickUIInterface::ColourPicker){return false;}
    (*x).setProperty("c", c.getQColour());
    return true;
}

bool SGXQuickUIInterface::showPage(QQuickItem *&x, QQuickItem *(*initialisationFunction)(), void (*resetFunction)()){
    if(x == nullptr){x = initialisationFunction();}
    if(SGXQuickUIInterface::getType(x) != SGXQuickUIInterface::Widget && SGXQuickUIInterface::getType(x) != SGXQuickUIInterface::ScrollView){
        (*x).deleteLater();
        x = nullptr;
        return false;
    }
    (*x).setVisible(true);
    resetFunction();
    return true;
}

bool SGXQuickUIInterface::hidePage(QQuickItem *&x){
    if(SGXQuickUIInterface::getType(x) != SGXQuickUIInterface::Widget && SGXQuickUIInterface::getType(x) != SGXQuickUIInterface::ScrollView){return false;}
    bool frequentlyUsed = (*x).property("frequentlyUsed").toBool();
    if(frequentlyUsed == true){(*x).setVisible(false);}
    else{
        (*x).deleteLater();
        x = nullptr;
    }
    return true;
}


void SGXQuickUIInterface::doNothing(){
    
}
