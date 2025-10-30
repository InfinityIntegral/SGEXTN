#include <private_api_Widgets/SGWParent.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <SGWWidget.h>
#include <QQuickItem>
#include <SGWType.h>

SGWParent::SGWParent() : SGWWidget(SGWWidget::rootWidget, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f){
    QQuickItem* thisItem = static_cast<QQuickItem*>((*SGXQuickInterface::parentWidget).create());
    (*thisItem).setParentItem((*SGWWidget::rootWidget).getBottomObject());
    (*thisItem).setParent((*SGWWidget::rootWidget).getBottomObject());
    (*this).type = SGWType::Parent;
    (*this).topObject = thisItem;
    (*this).bottomObject = thisItem;
}
