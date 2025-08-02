#include "sgwroot.h"
#include "../quickui/sgxquickinterface.h"
#include "sgwwidget.h"
#include <QQuickItem>
#include <QObject>
#include "sgwtype.h"

SGWRoot::SGWRoot() : SGWWidget(nullptr, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickInterface::root).create());
    (*thisItem).setParentItem(SGXQuickInterface::rootWindow);
    (*thisItem).setParent(SGXQuickInterface::rootWindow);
    (*this).type = SGWType::Root;
    (*this).topObject = thisItem;
    (*this).bottomObject = thisItem;
}
