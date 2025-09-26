#include "sgwiconlabel.h"
#include "../../quickui/sgxquickinterface.h"
#include "../noninstantiable/sgwwidget.h"
#include "../../primitives/sgxchar.h"
#include "../noninstantiable/sgwlabel.h"
#include <QString>
#include <QQuickItem>
#include "../enums/sgwtype.h"
#include "../enums/sgwhorizontalalignment.h"
#include "../enums/sgwverticalalignment.h"
#include "../enums/sgwdefaultfonts.h"

SGWIconLabel::SGWIconLabel(SGWWidget *parent, SGXChar s, float x1, float x0, float y1, float y0, float w1, float w0) : SGWLabel(parent, QString(QChar(s.data)), x1, x0, y1, y0, w1, w0, w1, w0, w1, w0, SGWHorizontalAlignment::Center, SGWVerticalAlignment::Center, SGWDefaultFonts::iconsFont){
    (*this).textChar = s;
    QQuickItem* thisItem = static_cast<QQuickItem*>((*SGXQuickInterface::iconLabel).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::IconLabel;
    SGWWidget::syncQuickProperties();
    SGWLabel::syncQuickProperties();
}

SGXChar SGWIconLabel::getChar() const {
    return textChar;
}

void SGWIconLabel::setChar(SGXChar c){
    (*this).textChar = c;
    (*this).text = QString(QChar(c.data));
    (*(*this).topObject).setProperty("s", QString(QChar(c.data)));
}
