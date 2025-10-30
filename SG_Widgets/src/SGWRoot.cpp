#include <private_api_Widgets/SGWRoot.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <SGWWidget.h>
#include <QQuickItem>
#include <SGWType.h>

SGWRoot::SGWRoot() : SGWWidget(nullptr, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f){
    QQuickItem* thisItem = static_cast<QQuickItem*>((*SGXQuickInterface::root).create());
    (*thisItem).setParentItem(SGXQuickInterface::rootWindow);
    (*thisItem).setParent(SGXQuickInterface::rootWindow);
    (*this).type = SGWType::Root;
    (*this).topObject = thisItem;
    (*this).bottomObject = thisItem;
}
