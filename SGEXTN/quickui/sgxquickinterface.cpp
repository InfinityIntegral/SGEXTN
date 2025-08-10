#include "sgxquickinterface.h"
#include "../widgets/sgwwidget.h"
#include "../widgets/sgwroot.h"
#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include "sgxquickresizer.h"
#include "sgxthemecoloursetting.h"
#include "../widgets/sgwparent.h"
#include "../widgets/sgwstatusbar.h"
#include <QQueue>
#include <qcontainerfwd.h>

QQmlComponent* SGXQuickInterface::root = nullptr;
QQmlApplicationEngine* SGXQuickInterface::e = nullptr;
QQuickItem* SGXQuickInterface::rootWindow = nullptr;
QQuickWindow* SGXQuickInterface::applicationWindow = nullptr;
SGXQuickResizer* SGXQuickInterface::resizerSingleton = nullptr;
SGXThemeColourSetting* SGXQuickInterface::themeColoursSingleton = nullptr;
QQmlComponent* SGXQuickInterface::parentWidget = nullptr;
QQmlComponent* SGXQuickInterface::statusBar = nullptr;
QQmlComponent* SGXQuickInterface::blankWidget = nullptr;
QQmlComponent* SGXQuickInterface::pageBackground = nullptr;
QQmlComponent* SGXQuickInterface::scrollView = nullptr;
QQmlComponent* SGXQuickInterface::textLabel = nullptr;
QQmlComponent* SGXQuickInterface::iconLabel = nullptr;
QQmlComponent* SGXQuickInterface::longLabel = nullptr;
QQmlComponent* SGXQuickInterface::textButton = nullptr;
QQmlComponent* SGXQuickInterface::iconButton = nullptr;
QQmlComponent* SGXQuickInterface::textInput = nullptr;
QQmlComponent* SGXQuickInterface::longInput = nullptr;
QQmlComponent* SGXQuickInterface::touchReceiver = nullptr;
QQmlComponent* SGXQuickInterface::colourPicker = nullptr;
QQmlComponent* SGXQuickInterface::sequentialScrollView = nullptr;
QQmlComponent* SGXQuickInterface::sequentialLongLabel = nullptr;

void SGXQuickInterface::createTemplates(){
    SGXQuickInterface::root = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwroot.qml");
    SGXQuickInterface::parentWidget = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwparent.qml");
    SGXQuickInterface::statusBar = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwstatusbar.qml");
    SGXQuickInterface::blankWidget = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwblankwidget.qml");
    SGXQuickInterface::pageBackground = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwpagebackground.qml");
    SGXQuickInterface::scrollView = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwscrollview.qml");
    SGXQuickInterface::textLabel = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwtextlabel.qml");
    SGXQuickInterface::iconLabel = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwiconlabel.qml");
    SGXQuickInterface::longLabel = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwlonglabel.qml");
    SGXQuickInterface::textButton = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwtextbutton.qml");
    SGXQuickInterface::iconButton = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwiconbutton.qml");
    SGXQuickInterface::textInput = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwtextinput.qml");
    SGXQuickInterface::longInput = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwlonginput.qml");
    SGXQuickInterface::touchReceiver = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwtouchreceiver.qml");
    SGXQuickInterface::colourPicker = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwcolourpickerwidget.qml");
    SGXQuickInterface::sequentialScrollView = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwsequentialscrollview.qml");
    SGXQuickInterface::sequentialLongLabel = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwsequentiallonglabel.qml");
}

void SGXQuickInterface::deleteTemplates(){
    delete SGXQuickInterface::root;
    delete SGXQuickInterface::parentWidget;
    delete SGXQuickInterface::statusBar;
    delete SGXQuickInterface::blankWidget;
    delete SGXQuickInterface::pageBackground;
    delete SGXQuickInterface::scrollView;
    delete SGXQuickInterface::textLabel;
    delete SGXQuickInterface::iconLabel;
    delete SGXQuickInterface::longLabel;
    delete SGXQuickInterface::textButton;
    delete SGXQuickInterface::iconButton;
    delete SGXQuickInterface::textInput;
    delete SGXQuickInterface::longInput;
    delete SGXQuickInterface::touchReceiver;
    delete SGXQuickInterface::colourPicker;
    delete SGXQuickInterface::sequentialScrollView;
    delete SGXQuickInterface::sequentialLongLabel;
}

void SGXQuickInterface::buildBase(){
    SGWWidget::rootWidget = new SGWRoot();
    SGWWidget::parentWidget = new SGWParent();
    SGWStatusBar::instance = new SGWStatusBar();
}

void SGXQuickInterface::deleteSingletons(){
    delete SGXQuickInterface::resizerSingleton;
    delete SGXQuickInterface::themeColoursSingleton;
}

QQuickItem* SGXQuickInterface::getBottomObject(QQuickItem *topObject){
    QQueue<QQuickItem*> childrenList = QQueue<QQuickItem*>();
    childrenList.enqueue(topObject);
    while(childrenList.length() > 0){
        QQuickItem* i = childrenList.dequeue();
        if((*i).property("canParent").toBool() == true){return i;}
        QVector<QQuickItem*> thisChildren = (*i).childItems();
        for(int idx = 0; idx < thisChildren.length(); idx++){
            childrenList.enqueue(thisChildren[idx]);
        }
    }
    return nullptr;
}
