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

QQuickItem* SGXQuickUIInterface::createRootWidget(QQuickItem *parent){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickUIInterface::rootWidgetTemplate).create());
    (*thisItem).setParentItem(parent);
    return thisItem;
}
