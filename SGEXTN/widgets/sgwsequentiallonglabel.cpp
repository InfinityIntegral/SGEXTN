#include "sgwsequentiallonglabel.h"
#include "../quickui/sgxquickinterface.h"
#include "sgwwidget.h"
#include <QString>
#include "sgwlabel.h"
#include <QQuickItem>
#include <QObject>
#include "sgwtype.h"
#include "sgwhorizontalalignment.h"
#include "sgwverticalalignment.h"
#include "sgwdefaultfonts.h"

SGWSequentialLongLabel::SGWSequentialLongLabel(SGWWidget *parent, const QString &s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0) : SGWLabel(parent, s, x1, x0, y1, y0, w1, w0, h1, h0, h1, h0, SGWHorizontalAlignment::Left, SGWVerticalAlignment::Top, SGWDefaultFonts::textFont){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickInterface::sequentialLongLabel).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::SequentialLongLabel;
    SGWWidget::syncQuickProperties();
    SGWLabel::syncQuickProperties();
}
