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

void SGXQuickUIInterface::initialise(){
    SGXQuickUIInterface::rootWidgetTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/rootwidget.qml");
    SGXQuickUIInterface::parentWidgetTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/parentwidget.qml");
    SGXQuickUIInterface::widgetTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/widget.qml");
    SGXQuickUIInterface::textTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/text.qml");
    SGXQuickUIInterface::longTextTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/longtext.qml");
    SGXQuickUIInterface::iconTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/icon.qml");
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
