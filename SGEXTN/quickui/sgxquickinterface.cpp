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

void SGXQuickInterface::createTemplates(){
    SGXQuickInterface::root = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwroot.qml");
    SGXQuickInterface::parentWidget = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwparent.qml");
    SGXQuickInterface::statusBar = new QQmlComponent(SGXQuickInterface::e, ":/SGEXTN/QML/sgwstatusbar.qml");
}

void SGXQuickInterface::deleteTemplates(){
    delete SGXQuickInterface::root;
    delete SGXQuickInterface::parentWidget;
    delete SGXQuickInterface::statusBar;
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
