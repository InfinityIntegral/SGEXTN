#ifndef SGXQUICKINTERFACE_H
#define SGXQUICKINTERFACE_H

#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include "sgxquickresizer.h"
#include "sgxthemecoloursetting.h"

class SGXQuickInterface
{
public:
    SGXQuickInterface() = delete;
    static QQmlApplicationEngine* e;
    static void createTemplates();
    static void buildBase();
    static QQmlComponent* root;
    static QQuickWindow* applicationWindow;
    static QQuickItem* rootWindow;
    static void deleteTemplates();
    static void deleteSingletons();
    static SGXQuickResizer* resizerSingleton;
    static SGXThemeColourSetting* themeColoursSingleton;
    static QQmlComponent* parentWidget;
    static QQmlComponent* statusBar;
    static QQuickItem* getBottomObject(QQuickItem* topObject);
    static QQmlComponent* blankWidget;
    static QQmlComponent* pageBackground;
    static QQmlComponent* scrollView;
    static QQmlComponent* textLabel;
    static QQmlComponent* iconLabel;
    static QQmlComponent* longLabel;
    static QQmlComponent* textButton;
    static QQmlComponent* iconButton;
    static QQmlComponent* textInput;
    static QQmlComponent* longInput;
    static QQmlComponent* touchReceiver;
    static QQmlComponent* colourPicker;
    static QQmlComponent* sequentialScrollView;
    static QQmlComponent* sequentialLongLabel;
};

#endif // SGXQUICKINTERFACE_H
