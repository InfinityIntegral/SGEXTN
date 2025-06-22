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
    static void initialise();
    static void buildTemplate();
    static QQuickItem* rootWindow;
    static QQmlComponent* rootWidgetTemplate;
    static QQuickItem* createRootWidget(QQuickItem* parent);
    static QQuickItem* rootWidget;
    static QQmlComponent* parentWidgetTemplate;
    static QQuickItem* createParentWidget(QQuickItem* parent);
    static QQuickItem* parentWidget;
    static QQmlComponent* widgetTemplate;
    static QQuickItem* createWidget(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int bg);
    static QQmlComponent* textTemplate;
    static QQuickItem* createText(QQuickItem* parent, const QString& s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
};

#endif // SGXQUICKUIINTERFACE_H
