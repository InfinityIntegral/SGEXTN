#include "sgwtextinput.h"
#include "../quickui/sgxquickinterface.h"
#include "sgwwidget.h"
#include "sgwinput.h"
#include "sgwhorizontalalignment.h"
#include "sgwverticalalignment.h"
#include <QQuickItem>
#include <QObject>
#include "sgwtype.h"

SGWTextInput::SGWTextInput(SGWWidget *parent, void (*validationFunction)(SGWInput *), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0) : SGWInput(parent, validationFunction, x1, x0, y1, y0, w1, w0, h1, h0, h1, h0, SGWHorizontalAlignment::Center, SGWVerticalAlignment::Center){
    QQuickItem* thisItem = qobject_cast<QQuickItem*>((*SGXQuickInterface::textInput).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).type = SGWType::TextInput;
    SGWWidget::syncQuickProperties();
    SGWInput::syncQuickProperties();
}
