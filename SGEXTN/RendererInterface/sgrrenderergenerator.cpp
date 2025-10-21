#include "sgrrenderergenerator.h"
#include "sgrrenderernode.h"
#include "../bypassquickui/sgxresizer.h"
#include "../widgets/noninstantiable/sgwwidget.h"

SGRRendererGenerator::SGRRendererGenerator(SGRBaseRenderer* renderControl, SGWWidget *attachedWidget) : QQuickItem(nullptr){
    setFlag(ItemHasContents, true);
    (*this).renderControl = renderControl;
    (*this).attachedWidget = attachedWidget;
}

QSGNode* SGRRendererGenerator::updatePaintNode(QSGNode *old, UpdatePaintNodeData */*unused*/){
    SGRRendererNode* node = static_cast<SGRRendererNode*>(old);
    if(node == nullptr){
        node = new SGRRendererNode(renderControl);
        (*node).associatedItem = this;
    }
    return node;
}

void SGRRendererGenerator::updatePolish(){
    setX((*attachedWidget).getX1() * ((*attachedWidget).getParentW1() * SGXResizer::getRenderSpaceWidth() + (*attachedWidget).getParentW0() * SGXResizer::getSizeUnit()) + (*attachedWidget).getX0() * SGXResizer::getSizeUnit());
    setY((*attachedWidget).getY1() * ((*attachedWidget).getParentH1() * SGXResizer::getRenderSpaceHeight() + (*attachedWidget).getParentH0() * SGXResizer::getSizeUnit()) + (*attachedWidget).getY0() * SGXResizer::getSizeUnit());
    setWidth((*attachedWidget).getW1() * ((*attachedWidget).getParentW1() * SGXResizer::getRenderSpaceWidth() + (*attachedWidget).getParentW0() * SGXResizer::getSizeUnit()) + (*attachedWidget).getW0() * SGXResizer::getSizeUnit());
    setHeight((*attachedWidget).getH1() * ((*attachedWidget).getParentH1() * SGXResizer::getRenderSpaceHeight() + (*attachedWidget).getParentH0() * SGXResizer::getSizeUnit()) + (*attachedWidget).getH0() * SGXResizer::getSizeUnit());
}
