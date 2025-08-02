#include "sgxquickinterface.h"
#include "../widgets/sgwwidget.h"
#include "../widgets/sgwroot.h"
#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include "sgxquickresizer.h"
#include "sgxthemecoloursetting.h"
#include "../widgets/sgwparent.h"

QQmlComponent* SGXQuickInterface::root = nullptr;
QQmlApplicationEngine* SGXQuickInterface::e = nullptr;
QQuickItem* SGXQuickInterface::rootWindow = nullptr;
QQuickWindow* SGXQuickInterface::applicationWindow = nullptr;
SGXQuickResizer* SGXQuickInterface::resizerSingleton = nullptr;
SGXThemeColourSetting* SGXQuickInterface::themeColoursSingleton = nullptr;
QQmlComponent* SGXQuickInterface::parentWidget = nullptr;

void SGXQuickInterface::createTemplates(){
    SGXQuickInterface::root = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwroot.qml");
    SGXQuickInterface::parentWidget = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwparent.qml");
}

void SGXQuickInterface::deleteTemplates(){
    delete SGXQuickInterface::root;
    delete SGXQuickInterface::parentWidget;
}

void SGXQuickInterface::buildBase(){
    SGWWidget::rootWidget = new SGWRoot();
    SGWWidget::parentWidget = new SGWParent();
}

void SGXQuickInterface::deleteSingletons(){
    delete SGXQuickInterface::resizerSingleton;
    delete SGXQuickInterface::themeColoursSingleton;
}
