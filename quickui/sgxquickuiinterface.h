#ifndef SGXQUICKUIINTERFACE_H
#define SGXQUICKUIINTERFACE_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQuickItem>
#include "../quickui/sgxquickresizer.h"
#include "../quickui/sgxthemecoloursetting.h"
#include "../primitives/sgxtouchevent.h"
#include <qcontainerfwd.h>
#include <qtmetamacros.h>
#include <array>

class SGXQuickUIInterface : public QObject
{
    Q_OBJECT
public:
    SGXQuickUIInterface() = delete;
    enum WidgetType{
        Undefined = 0,
        RootWidget = 10,
        ParentWidget = 20,
        Widget = 30,
        Text = 40,
        LongText = 41,
        Icon = 42,
        TextButton = 50,
        IconButton = 51,
        InputField = 60,
        LongInputField = 61,
        ScrollView = 70,
        TouchReceiver = 80,
        CuteVesicles = 90,
    };
    static void testingFunction(const std::array<SGXTouchEvent, 5>& t);
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
    static QQmlComponent* longTextTemplate;
    static QQuickItem* createLongText(QQuickItem* parent, const QString& s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, float s1, float s0);
    static QQmlComponent* iconTemplate;
    static QQuickItem* createIcon(QQuickItem* parent, const QChar& s, float x1, float x0, float y1, float y0, float w1, float w0);
    static QQmlComponent* textButtonTemplate;
    static QQuickItem* createTextButton(QQuickItem* parent, const QString& s, void (*attachedFunction)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    static QQmlComponent* iconButtonTemplate;
    static QQuickItem* createIconButton(QQuickItem* parent, const QChar& s, void (*attachedFunction)(), float x1, float x0, float y1, float y0, float w1, float w0);
    static QQmlComponent* inputFieldTemplate;
    static QQuickItem* createInputField(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    static QQmlComponent* longInputFieldTemplate;
    static QQuickItem* createLongInputField(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, float s1, float s0);
    static QQmlComponent* scrollViewTemplate;
    static QQuickItem* createScrollView(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float ih1, float ih0, float s1, float s0, int bg);
    static QQmlComponent* touchReceiverTemplate;
    static QQuickItem* createTouchReceiver(QQuickItem* parent, void (*attachedFunction)(const std::array<SGXTouchEvent, 5>&), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    static void receiveTouch(const QString& s);
    static QVector<void (*)(const std::array<SGXTouchEvent, 5>&)>* touchEventFunctionsList;
    static QQmlComponent* cuteVesiclesTemplate;
    static QQuickItem* createCuteVesicles(QQuickItem* parent);
    static SGXQuickUIInterface::WidgetType getType(QQuickItem* x);
    static void doNothing(){}
};

#endif // SGXQUICKUIINTERFACE_H
