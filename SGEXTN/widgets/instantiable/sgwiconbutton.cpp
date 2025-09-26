#include "sgwiconbutton.h"
#include "../enums/sgwdefaultfonts.h"
#include "../../quickui/sgxquickinterface.h"
#include "../noninstantiable/sgwwidget.h"
#include "../../primitives/sgxchar.h"
#include "../noninstantiable/sgwbutton.h"
#include <QQuickItem>
#include "../enums/sgwtype.h"

SGWIconButton::SGWIconButton(SGWWidget *parent, SGXChar s, void (*attachedFunction)(SGWButton *), float x1, float x0, float y1, float y0, float w1, float w0) : SGWButton(parent, s, attachedFunction, x1, x0, y1, y0, w1, w0, w1, w0, w1, w0, SGWDefaultFonts::iconsFont){
    (*this).textChar = s;
    QQuickItem* thisItem = static_cast<QQuickItem*>((*SGXQuickInterface::iconButton).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::IconButton;
    SGWWidget::syncQuickProperties();
    SGWButton::syncQuickProperties();
}

SGXChar SGWIconButton::getChar() const {
    return textChar;
}

void SGWIconButton::setChar(SGXChar c){
    (*this).textChar = c;
    (*this).text = c;
    (*(*this).topObject).setProperty("s", (*text.data));
}
