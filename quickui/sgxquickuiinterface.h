#ifndef SGXQUICKUIINTERFACE_H
#define SGXQUICKUIINTERFACE_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickItem>
#include "../quickui/sgxquickresizer.h"
#include "../quickui/sgxthemecoloursetting.h"

class SGXQuickUIInterface : public QObject
{
    Q_OBJECT // NOLINT
public:
    SGXQuickUIInterface() = delete;
    static QQmlApplicationEngine* e;
    static SGXQuickResizer* resizerInstance;
    static SGXThemeColourSetting* themeColoursInstance;
    static QQuickItem* rootWindow;
    static QQmlComponent* rootWidgetTemplate;
    static QQuickItem* createRootWidget(QQuickItem* parent);
    static QQuickItem* rootWidget;
    static QQmlComponent* parentWidgetTemplate;
    static QQuickItem* createParentWidget(QQuickItem* parent);
    static QQuickItem* parentWidget;
};

#endif // SGXQUICKUIINTERFACE_H
