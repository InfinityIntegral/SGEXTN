#include "sgwparent.h"
#include "../quickui/sgxquickinterface.h"
#include "sgwwidget.h"
#include <QQuickItem>
#include <QObject>
#include "sgwtype.h"

SGWParent::SGWParent() : SGWWidget(SGWWidget::rootWidget, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickInterface::parentWidget).create());
    (*thisItem).setParentItem((*SGWWidget::rootWidget).getBottomObject());
    (*thisItem).setParent((*SGWWidget::rootWidget).getBottomObject());
    (*this).type = SGWType::Parent;
    (*this).topObject = thisItem;
    (*this).bottomObject = thisItem;
}
