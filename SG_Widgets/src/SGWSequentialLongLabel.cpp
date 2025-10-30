#include <SGWSequentialLongLabel.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <SGWWidget.h>
#include <SGXString.h>
#include <SGWLabel.h>
#include <QQuickItem>
#include <SGWType.h>
#include <SGWHorizontalAlignment.h>
#include <SGWVerticalAlignment.h>
#include <SGWDefaultFonts.h>

SGWSequentialLongLabel::SGWSequentialLongLabel(SGWWidget *parent, const SGXString &s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0) : SGWLabel(parent, s, x1, x0, y1, y0, w1, w0, h1, h0, h1, h0, SGWHorizontalAlignment::Left, SGWVerticalAlignment::Top, SGWDefaultFonts::textFont){
    QQuickItem* thisItem = static_cast<QQuickItem*>((*SGXQuickInterface::sequentialLongLabel).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::SequentialLongLabel;
    SGWWidget::syncQuickProperties();
    SGWLabel::syncQuickProperties();
}
