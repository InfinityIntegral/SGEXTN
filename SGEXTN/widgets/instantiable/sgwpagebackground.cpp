#include "sgwpagebackground.h"
#include "../../quickui/sgxquickinterface.h"
#include "../noninstantiable/sgwwidget.h"
#include "../noninstantiable/sgwbackground.h"
#include <QQuickItem>
#include "../enums/sgwtype.h"

SGWPageBackground::SGWPageBackground(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int themeColour) : SGWBackground(parent, x1, x0, y1, y0, w1, w0, h1, h0, themeColour){
    QQuickItem* thisItem = static_cast<QQuickItem*>((*SGXQuickInterface::pageBackground).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::PageBackground;
    SGWWidget::syncQuickProperties();
    SGWBackground::syncQuickProperties();
}
