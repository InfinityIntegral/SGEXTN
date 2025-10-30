#include <SGWTextButton.h>
#include <SGWDefaultFonts.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <SGWWidget.h>
#include <SGXString.h>
#include <SGWButton.h>
#include <QQuickItem>
#include <SGWType.h>

SGWTextButton::SGWTextButton(SGWWidget *parent, const SGXString &s, void (*attachedFunction)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0) : SGWButton(parent, s, attachedFunction, x1, x0, y1, y0, w1, w0, h1, h0, h1, h0, SGWDefaultFonts::textFont){
    QQuickItem* thisItem = static_cast<QQuickItem*>((*SGXQuickInterface::textButton).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::TextButton;
    SGWWidget::syncQuickProperties();
    SGWButton::syncQuickProperties();
}
