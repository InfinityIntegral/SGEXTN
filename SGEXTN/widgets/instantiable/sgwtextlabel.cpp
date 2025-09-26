#include "sgwtextlabel.h"
#include "../../quickui/sgxquickinterface.h"
#include "../noninstantiable/sgwwidget.h"
#include "../../primitives/sgxstring.h"
#include "../noninstantiable/sgwlabel.h"
#include <QQuickItem>
#include "../enums/sgwtype.h"
#include "../enums/sgwhorizontalalignment.h"
#include "../enums/sgwverticalalignment.h"
#include "../enums/sgwdefaultfonts.h"

SGWTextLabel::SGWTextLabel(SGWWidget *parent, const SGXString &s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGWHorizontalAlignment::Flag alignment, bool isWarning) : SGWLabel(parent, s, x1, x0, y1, y0, w1, w0, h1, h0, h1, h0, alignment, SGWVerticalAlignment::Center, SGWDefaultFonts::textFont){
    QQuickItem* thisItem = static_cast<QQuickItem*>((*SGXQuickInterface::textLabel).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::TextLabel;
    SGWWidget::syncQuickProperties();
    SGWLabel::syncQuickProperties();
    if(isWarning == true){
        (*this).setForegroundThemeColour(2);
        (*this).setItemVisibility(false);
    }
}
