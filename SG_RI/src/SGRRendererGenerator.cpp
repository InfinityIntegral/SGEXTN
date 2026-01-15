#include <private_api_RI/SGRRendererGenerator.h>
#include <private_api_RI/SGRRendererNode.h>
#include <SGXResizer.h>
#include <SGWWidget.h>
#include <SGRBaseSyncer.h>
#include <QQuickItem>
#include <QSGRenderNode>
#include <SGRBaseRenderer.h>
#include<private_api_Widgets/SGXQuickInterface.h>
#include <QQuickWindow>
#include <QTimer>

SGRRendererGenerator::SGRRendererGenerator(SGRBaseRenderer* renderControl, SGRBaseSyncer* syncControl, SGWWidget *attachedWidget, QQuickItem *parentItem) : QQuickItem(parentItem){
    setFlag(ItemHasContents, true);
    (*this).renderControl = renderControl;
    (*this).syncControl = syncControl;
    (*this).attachedWidget = attachedWidget;
    (*this).node = nullptr;
    (*this).setClip(true);
    (*this).syncSize();
    QTimer* refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, this, &SGRRendererGenerator::syncSize);
    (*refreshTimer).start(0);
}

QSGNode* SGRRendererGenerator::updatePaintNode(QSGNode *old, UpdatePaintNodeData */*unused*/){
    SGRRendererNode* node = static_cast<SGRRendererNode*>(old);
    if(node == nullptr){node = new SGRRendererNode(renderControl);}
    (*renderControl).internalX = static_cast<float>(mapToScene(QPointF(0.0f, 0.0f)).x());
    (*renderControl).internalY = static_cast<float>(mapToScene(QPointF(0.0f, 0.0f)).y());
    (*renderControl).internalW = static_cast<float>(width());
    (*renderControl).internalH = static_cast<float>(height());
    (*renderControl).internalWindowW = static_cast<float>((*SGXQuickInterface::applicationWindow).width());
    (*renderControl).internalWindowH = static_cast<float>((*SGXQuickInterface::applicationWindow).height());
    if(syncControl != nullptr){(*syncControl).sync(renderControl);}
    (*this).node = node;
    return node;
}

void SGRRendererGenerator::syncSize(){
    const float prevX = static_cast<float>((*this).mapToGlobal(0, 0).x());
    const float prevY = static_cast<float>((*this).mapToGlobal(0, 0).y());
    const float prevW = static_cast<float>(width());
    const float prevH = static_cast<float>(height());
    if(attachedWidget == nullptr){
        setWidth((*parentItem()).width());
        setHeight((*parentItem()).height());
        update();
        return;
    }
    setX((*attachedWidget).getX1() * ((*attachedWidget).getParentW1() * SGXResizer::getRenderSpaceWidth() + (*attachedWidget).getParentW0() * SGXResizer::getSizeUnit()) + (*attachedWidget).getX0() * SGXResizer::getSizeUnit());
    setY((*attachedWidget).getY1() * ((*attachedWidget).getParentH1() * SGXResizer::getRenderSpaceHeight() + (*attachedWidget).getParentH0() * SGXResizer::getSizeUnit()) + (*attachedWidget).getY0() * SGXResizer::getSizeUnit());
    setWidth((*attachedWidget).getW1() * ((*attachedWidget).getParentW1() * SGXResizer::getRenderSpaceWidth() + (*attachedWidget).getParentW0() * SGXResizer::getSizeUnit()) + (*attachedWidget).getW0() * SGXResizer::getSizeUnit());
    setHeight((*attachedWidget).getH1() * ((*attachedWidget).getParentH1() * SGXResizer::getRenderSpaceHeight() + (*attachedWidget).getParentH0() * SGXResizer::getSizeUnit()) + (*attachedWidget).getH0() * SGXResizer::getSizeUnit());
    if(prevX == (*this).mapToGlobal(0, 0).x() && prevY == (*this).mapToGlobal(0, 0).y() && prevW == width() && prevH == height()){return;}
    update();
}

void SGRRendererGenerator::updatePolish(){
    QQuickItem::updatePolish();
    SGRRendererGenerator::syncSize();
}
