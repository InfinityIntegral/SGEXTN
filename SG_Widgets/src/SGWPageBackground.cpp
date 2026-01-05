#include <SGWPageBackground.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <SGWWidget.h>
#include <SGWBackground.h>
#include <QQuickItem>
#include <SGWType.h>

SGWPageBackground::SGWPageBackground(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0) : SGWBackground(parent, x1, x0, y1, y0, w1, w0, h1, h0){
    QQuickItem* thisItem = static_cast<QQuickItem*>((*SGXQuickInterface::pageBackground).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::PageBackground;
    SGWWidget::syncQuickProperties();
    SGWBackground::syncQuickProperties();
}
