#include "sgrrenderergenerator.h"
#include "sgrrenderernode.h"
#include "../bypassquickui/sgxresizer.h"
#include "../widgets/noninstantiable/sgwwidget.h"
#include "sgrbasesyncer.h"
#include <QQuickItem>
#include <QSGRenderNode>

SGRRendererGenerator::SGRRendererGenerator(SGRBaseRenderer* renderControl, SGRBaseSyncer* syncControl, SGWWidget *attachedWidget) : QQuickItem(nullptr){
    setFlag(ItemHasContents, true);
    (*this).renderControl = renderControl;
    (*this).syncControl = syncControl;
    (*syncControl).associatedItem = this;
    (*this).attachedWidget = attachedWidget;
    (*this).syncSize();
}

QSGNode* SGRRendererGenerator::updatePaintNode(QSGNode *old, UpdatePaintNodeData */*unused*/){
    SGRRendererNode* node = static_cast<SGRRendererNode*>(old);
    if(node == nullptr){
        node = new SGRRendererNode(renderControl);
        (*node).associatedItem = this;
    }
    (*syncControl).syncEverything(renderControl);
    (*node).markDirty(QSGRenderNode::DirtyForceUpdate);
    return node;
}

void SGRRendererGenerator::syncSize(){
    setX((*attachedWidget).getX1() * ((*attachedWidget).getParentW1() * SGXResizer::getRenderSpaceWidth() + (*attachedWidget).getParentW0() * SGXResizer::getSizeUnit()) + (*attachedWidget).getX0() * SGXResizer::getSizeUnit());
    setY((*attachedWidget).getY1() * ((*attachedWidget).getParentH1() * SGXResizer::getRenderSpaceHeight() + (*attachedWidget).getParentH0() * SGXResizer::getSizeUnit()) + (*attachedWidget).getY0() * SGXResizer::getSizeUnit());
    setWidth((*attachedWidget).getW1() * ((*attachedWidget).getParentW1() * SGXResizer::getRenderSpaceWidth() + (*attachedWidget).getParentW0() * SGXResizer::getSizeUnit()) + (*attachedWidget).getW0() * SGXResizer::getSizeUnit());
    setHeight((*attachedWidget).getH1() * ((*attachedWidget).getParentH1() * SGXResizer::getRenderSpaceHeight() + (*attachedWidget).getParentH0() * SGXResizer::getSizeUnit()) + (*attachedWidget).getH0() * SGXResizer::getSizeUnit());
}

void SGRRendererGenerator::updatePolish(){
    SGRRendererGenerator::syncSize();
}
