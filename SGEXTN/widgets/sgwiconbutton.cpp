#include "sgwiconbutton.h"
#include "sgwdefaultfonts.h"
#include "../quickui/sgxquickinterface.h"
#include "sgwwidget.h"
#include <QChar>
#include "sgwbutton.h"
#include <QString>
#include <QQuickItem>
#include <QObject>
#include "sgwtype.h"

SGWIconButton::SGWIconButton(SGWWidget *parent, QChar s, void (*attachedFunction)(SGWButton *), float x1, float x0, float y1, float y0, float w1, float w0) : SGWButton(parent, QString(s), attachedFunction, x1, x0, y1, y0, w1, w0, w1, w0, w1, w0, SGWDefaultFonts::iconsFont){
    (*this).textChar = s;
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickInterface::iconButton).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::IconButton;
    SGWWidget::syncQuickProperties();
    SGWButton::syncQuickProperties();
}

QChar SGWIconButton::getChar() const {
    return textChar;
}

void SGWIconButton::setChar(QChar c){
    (*this).textChar = c;
    (*this).text = QString(c);
    (*(*this).topObject).setProperty("s", QString(c));
}
