#include "sgwiconlabel.h"
#include "../quickui/sgxquickinterface.h"
#include "sgwwidget.h"
#include <QChar>
#include "sgwlabel.h"
#include <QString>
#include <QQuickItem>
#include <QObject>
#include "sgwtype.h"

SGWIconLabel::SGWIconLabel(SGWWidget *parent, const QChar &s, float x1, float x0, float y1, float y0, float w1, float w0) : SGWLabel(parent, QString(s), x1, x0, y1, y0, w1, w0, w1, w0, w1, w0, SGWLabel::AlignHCenter, SGWLabel::AlignVCenter, SGWLabel::iconsFont){
    (*this).textChar = s;
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickInterface::iconLabel).create());
    (*thisItem).setParentItem((*parent).getBottomObject());
    (*thisItem).setParent((*parent).getBottomObject());
    (*this).type = SGWType::IconLabel;
    (*this).topObject = thisItem;
    (*this).bottomObject = SGXQuickInterface::getBottomObject(thisItem);
    SGWWidget::syncQuickProperties();
    SGWLabel::syncQuickProperties();
}

QChar SGWIconLabel::getChar() const {
    return textChar;
}

void SGWIconLabel::setChar(QChar c){
    (*this).textChar = c;
    (*this).text = QString(c);
    (*(*this).topObject).setProperty("s", QString(c));
}
