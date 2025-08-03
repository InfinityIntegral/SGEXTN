#include "sgwpagebackground.h"
#include "../quickui/sgxquickinterface.h"
#include "sgwwidget.h"
#include "sgwbackground.h"
#include <QQuickItem>
#include <QObject>
#include "sgwtype.h"

SGWPageBackground::SGWPageBackground(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int themeColour, bool frequentlyUsed) : SGWBackground(parent, x1, x0, y1, y0, w1, w0, h1, h0, themeColour, frequentlyUsed){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickInterface::pageBackground).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::PageBackground;
    SGWWidget::syncQuickProperties();
    SGWBackground::syncQuickProperties();
}
