#include "sgxquickuiinterface.h"
#include <QQuickItem>
#include <QQmlApplicationEngine>
#include "../quickui/sgxthemecoloursetting.h"
#include "../quickui/sgxquickresizer.h"
#include <QQmlComponent>
#include <QObject>

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
QVector<void (*)(int, SGXTouchEvent*)>* SGXQuickUIInterface::touchEventFunctionsList = nullptr;

void SGXQuickUIInterface::testingFunction(int n, SGXTouchEvent *t){
    qDebug() << n;
    for(int i=0; i<n; i++){qDebug() << t[i];}
}

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
    qDebug() << (*SGXQuickUIInterface::touchReceiverTemplate).errors();
}

void SGXQuickUIInterface::buildTemplate(){
    SGXQuickUIInterface::rootWidget = SGXQuickUIInterface::createRootWidget(SGXQuickUIInterface::rootWindow);
    SGXQuickUIInterface::parentWidget = SGXQuickUIInterface::createParentWidget(SGXQuickUIInterface::rootWidget);
    SGXQuickUIInterface::createTouchReceiver(SGXQuickUIInterface::parentWidget, &SGXQuickUIInterface::testingFunction, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 1.0f, -1.0f);
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
    bool ignoreOkOrNot = false;
    unsigned long long iop = (s.mid(1)).toULongLong(&ignoreOkOrNot);
    QQuickItem* thisItem = std::bit_cast<QQuickItem*>(iop);
    int fpi = (*thisItem).property("functionPointer").toInt();
    void (*functionToRun)(int, SGXTouchEvent*) = (*SGXQuickUIInterface::touchEventFunctionsList)[fpi];
    functionToRun(0, nullptr);
}

QQuickItem* SGXQuickUIInterface::createTouchReceiver(QQuickItem *parent, void (*attachedFunction)(int, SGXTouchEvent *), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0){
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
        SGXQuickUIInterface::touchEventFunctionsList = new QVector<void (*)(int, SGXTouchEvent*)>();
    }
    (*SGXQuickUIInterface::touchEventFunctionsList).append(attachedFunction);
    (*thisItem).setProperty("functionPointer", (*SGXQuickUIInterface::touchEventFunctionsList).length() - 1);
    connect(thisItem, &QQuickItem::stateChanged, &SGXQuickUIInterface::receiveTouch);
    return thisItem;
}
