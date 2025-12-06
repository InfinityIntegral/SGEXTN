#ifndef SGXQUICKINTERFACE_H
#define SGXQUICKINTERFACE_H

#include <private_api_Widgets/SG_Build_Widgets.h>

class QQmlComponent;
class QQmlApplicationEngine;
class QQuickItem;
class SGXQuickResizer;
class SGXThemeColourSetting;
class QQuickWindow;
class SG_WIDGETS_DLL SGXQuickInterface
{
public:
    SGXQuickInterface() = delete;
    static QQmlApplicationEngine* e;
    static void createTemplates();
    static void buildBase();
    static QQmlComponent* root;
    static QQuickWindow* applicationWindow;
    static QQuickItem* rootWindow;
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
    static QQmlComponent* multiTouchReceiver;
    static QQmlComponent* singleTouchReceiver;
    static QQmlComponent* colourPicker;
    static QQmlComponent* sequentialScrollView;
    static QQmlComponent* sequentialLongLabel;
};

#endif // SGXQUICKINTERFACE_H
