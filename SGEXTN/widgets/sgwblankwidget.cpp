#include "sgwblankwidget.h"
#include "../quickui/sgxquickinterface.h"
#include "sgwwidget.h"
#include "sgwbackground.h"
#include <QQuickItem>
#include <QObject>
#include "sgwtype.h"

SGWBlankWidget::SGWBlankWidget(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int themeColour, bool frequentlyUsed) : SGWBackground(parent, x1, x0, y1, y0, w1, w0, h1, h0, themeColour, frequentlyUsed){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickInterface::blankWidget).create());
    (*thisItem).setParentItem((*parent).getBottomObject());
    (*thisItem).setParent((*parent).getBottomObject());
    (*this).type = SGWType::BlankWidget;
    (*this).topObject = thisItem;
    (*this).bottomObject = SGXQuickInterface::getBottomObject(thisItem);
    SGWWidget::syncQuickProperties();
    SGWBackground::syncQuickProperties();
}
