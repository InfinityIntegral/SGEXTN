#include "sgwcustomrenderer.h"
#include "../../quickui/sgxquickinterface.h"
#include <QHash>
#include "../../primitives/sgxstring.h"
#include <QQmlComponent>
#include "../noninstantiable/sgwwidget.h"
#include "../enums/sgwtype.h"
#include <QQuickItem>
#include <QQmlApplicationEngine>

QHash<SGXString, QQmlComponent*>* SGWCustomRenderer::componentDatabase = nullptr;

SGWCustomRenderer::SGWCustomRenderer(SGWWidget* parent, const SGXString& qmlCodeLocation, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0) : SGWWidget(parent, x1, x0, y1, y0, w1, w0, h1, h0){
    (*this).type = SGWType::CustomRenderer;
    if(SGWCustomRenderer::componentDatabase == nullptr){SGWCustomRenderer::componentDatabase = new QHash<SGXString, QQmlComponent*>();}
    if((*SGWCustomRenderer::componentDatabase).contains(qmlCodeLocation) == false){(*SGWCustomRenderer::componentDatabase).insert(qmlCodeLocation, new QQmlComponent(SGXQuickInterface::e, (*qmlCodeLocation.data)));}
    QQuickItem* thisItem = static_cast<QQuickItem*>((*(*SGWCustomRenderer::componentDatabase)[qmlCodeLocation]).create());
    (*this).initialiseQuickItemReferences(thisItem);
    (*this).bottomObject = (*this).topObject;
    SGWWidget::syncQuickProperties();
}

void SGWCustomRenderer::redraw(){
    (*topObject).update();
}
