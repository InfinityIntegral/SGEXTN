#include <SGWTextInput.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <SGWWidget.h>
#include <SGWInput.h>
#include <SGWHorizontalAlignment.h>
#include <SGWVerticalAlignment.h>
#include <QQuickItem>
#include <SGWType.h>
#include <SGXString.h>

SGWTextInput::SGWTextInput(SGWWidget *parent, const SGXString& placeholder, void (*validationFunction)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0) : SGWInput(parent, placeholder, validationFunction, x1, x0, y1, y0, w1, w0, h1, h0, h1, h0, SGWHorizontalAlignment::Center, SGWVerticalAlignment::Center){
    QQuickItem* thisItem = static_cast<QQuickItem*>((*SGXQuickInterface::textInput).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::TextInput;
    SGWWidget::syncQuickProperties();
    SGWInput::syncQuickProperties();
}
