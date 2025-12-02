#include <private_api_Widgets/SGWStatusBar.h>
#include <SGWWidget.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <SGXTimeStamp.h>
#include <SGXTimer.h>
#include <QQuickItem>
#include <SGWType.h>
#include <SGXString.h>

SGWStatusBar* SGWStatusBar::instance = nullptr;
SGXTimer* SGWStatusBar::timer = nullptr;

SGWStatusBar::SGWStatusBar() : SGWWidget(SGWWidget::rootWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f){
    QQuickItem* thisItem = static_cast<QQuickItem*>((*SGXQuickInterface::statusBar).create());
    (*thisItem).setParentItem((*SGWWidget::rootWidget).getBottomObject());
    (*thisItem).setParent((*SGWWidget::rootWidget).getBottomObject());
    (*this).type = SGWType::StatusBar;
    (*this).topObject = thisItem;
    (*this).bottomObject = SGXQuickInterface::getBottomObject(thisItem);
    SGWStatusBar::timer = new SGXTimer(1.0f, &SGWStatusBar::updateTime);
    SGXTimer::singleCall(0.0f, &SGWStatusBar::updateTime);
}

void SGWStatusBar::terminate(){
    (*SGWStatusBar::timer).deleteTimer();
    SGWStatusBar::timer = nullptr;
}

void SGWStatusBar::updateTime(){
    (*(*SGWStatusBar::instance).getTopObject()).setProperty("s", (*SGXString::doubleToStringSignificantFigures(SGXTimeStamp::now().getYearsFrom(SGXTimeStamp::zero), 9).fillRightToLength(10, '0').data));
}
