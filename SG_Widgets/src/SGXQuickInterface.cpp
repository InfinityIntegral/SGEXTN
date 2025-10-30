#include <private_api_Widgets/SGXQuickInterface.h>
#include <SGWWidget.h>
#include <private_api_Widgets/SGWRoot.h>
#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <private_api_Widgets/SGXQuickResizer.h>
#include <private_api_Widgets/SGXThemeColourSetting.h>
#include <private_api_Widgets/SGWParent.h>
#include <private_api_Widgets/SGWStatusBar.h>
#include <SGLQueue.h>
#include <qcontainerfwd.h>
#include <QQuickItem>

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
QQmlComponent* SGXQuickInterface::multiTouchReceiver = nullptr;
QQmlComponent* SGXQuickInterface::singleTouchReceiver = nullptr;
QQmlComponent* SGXQuickInterface::colourPicker = nullptr;
QQmlComponent* SGXQuickInterface::sequentialScrollView = nullptr;
QQmlComponent* SGXQuickInterface::sequentialLongLabel = nullptr;

void SGXQuickInterface::createTemplates(){
    SGXQuickInterface::root = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/SGWRoot.qml");
    SGXQuickInterface::parentWidget = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/SGWParent.qml");
    SGXQuickInterface::statusBar = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/SGWStatusBar.qml");
    SGXQuickInterface::blankWidget = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/SGWBlankWidget.qml");
    SGXQuickInterface::pageBackground = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/SGWPageBackground.qml");
    SGXQuickInterface::scrollView = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/SGWScrollView.qml");
    SGXQuickInterface::textLabel = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/SGWTextLabel.qml");
    SGXQuickInterface::iconLabel = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/SGWIconLabel.qml");
    SGXQuickInterface::longLabel = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/SGWLongLabel.qml");
    SGXQuickInterface::textButton = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/SGWTextButton.qml");
    SGXQuickInterface::iconButton = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/SGWIconButton.qml");
    SGXQuickInterface::textInput = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/SGWTextInput.qml");
    SGXQuickInterface::longInput = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/SGWLongInput.qml");
    SGXQuickInterface::multiTouchReceiver = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/SGWMultiTouchReceiver.qml");
    SGXQuickInterface::singleTouchReceiver = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/SGWSingleTouchReceiver.qml");
    SGXQuickInterface::colourPicker = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/SGWColourPickerWidget.qml");
    SGXQuickInterface::sequentialScrollView = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/SGWSequentialScrollView.qml");
    SGXQuickInterface::sequentialLongLabel = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/SGWSequentialLongLabel.qml");
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
    delete SGXQuickInterface::multiTouchReceiver;
    delete SGXQuickInterface::singleTouchReceiver;
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
    SGLQueue<QQuickItem*> childrenList = SGLQueue<QQuickItem*>();
    childrenList.push(topObject);
    while(childrenList.length() > 0){
        QQuickItem* i = childrenList.front();
        childrenList.pop();
        if((*i).property("canParent").toBool() == true){return i;}
        const QVector<QQuickItem*> thisChildren = (*i).childItems();
        for(int idx = 0; idx < thisChildren.length(); idx++){
            childrenList.push(thisChildren.at(idx));
        }
    }
    return nullptr;
}
