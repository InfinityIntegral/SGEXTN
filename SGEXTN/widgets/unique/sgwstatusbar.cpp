#include "sgwstatusbar.h"
#include "../noninstantiable/sgwwidget.h"
#include "../../quickui/sgxquickinterface.h"
#include "../../primitives/sgxtimestamp.h"
#include "../../timer/sgxtimer.h"
#include <QObject>
#include <QQuickItem>
#include "../enums/sgwtype.h"
#include <QString>
#include "../../template/sgwcutevesicles.h"

int SGWStatusBar::notificationTime = 3;
SGWStatusBar* SGWStatusBar::instance = nullptr;
SGXTimer* SGWStatusBar::timer = nullptr;
int SGWStatusBar::timeLeft = 0;
bool SGWStatusBar::isNotifying = false;

SGWStatusBar::SGWStatusBar() : SGWWidget(SGWWidget::rootWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickInterface::statusBar).create());
    (*thisItem).setParentItem((*SGWWidget::rootWidget).getBottomObject());
    (*thisItem).setParent((*SGWWidget::rootWidget).getBottomObject());
    (*this).type = SGWType::StatusBar;
    (*this).topObject = thisItem;
    (*this).bottomObject = SGXQuickInterface::getBottomObject(thisItem);
    SGWStatusBar::timer = new SGXTimer(1.0f, &SGWStatusBar::updateTime);
    SGXTimer::singleCall(0.0f, &SGWStatusBar::updateTime);
    connect(thisItem, &QQuickItem::objectNameChanged, this, &SGWStatusBar::eventReceived);
}

void SGWStatusBar::terminate(){
    delete SGWStatusBar::timer;
}

void SGWStatusBar::updateTime(){
    if(SGWStatusBar::timeLeft == 0){
        (*(*SGWStatusBar::instance).getTopObject()).setProperty("s", SGXTimeStamp::now().getString());
        if(SGWStatusBar::isNotifying == true){
            SGWStatusBar::isNotifying = false;
            (*(*SGWStatusBar::instance).getTopObject()).setProperty("notify", false);
        }
    }
    else{SGWStatusBar::timeLeft--;}
}

void SGWStatusBar::eventReceived(const QString& s){
    if(s == "clicked"){SGWStatusBar::toggleVesicles();}
}

void SGWStatusBar::notify(const QString &s){
    SGWStatusBar::timeLeft = SGWStatusBar::notificationTime;
    SGWStatusBar::isNotifying = true;
    (*(*SGWStatusBar::instance).getTopObject()).setProperty("s", s);
    (*(*SGWStatusBar::instance).getTopObject()).setProperty("notify", true);
}

void SGWStatusBar::toggleVesicles(){
    SGWCuteVesicles::toggleAnimation();
}
