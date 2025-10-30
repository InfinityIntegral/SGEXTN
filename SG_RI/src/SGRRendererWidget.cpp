#include <SGRRendererWidget.h>
#include <QQuickItem>
#include <private_api_RI/SGRRendererGenerator.h>
#include <SGRBaseRenderer.h>
#include <SGRBaseSyncer.h>
#include <SGWType.h>
#include <private_api_RI/SGRRendererNode.h>

SGRRendererWidget::SGRRendererWidget(SGWWidget *parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGRBaseRenderer *renderControl, SGRBaseSyncer* syncControl) : SGWWidget(parent, x1, x0, y1, y0, w1, w0, h1, h0){
    QQuickItem* thisItem = new SGRRendererGenerator(renderControl, syncControl, this);
    (*thisItem).setParentItem((*parent).getBottomObject());
    (*thisItem).setParent((*parent).getBottomObject());
    (*this).topObject = thisItem;
    (*this).bottomObject = thisItem;
    (*this).type = SGWType::CustomRenderer;
    (*this).renderControl = renderControl;
    (*this).syncControl = syncControl;
}

SGRRendererWidget::~SGRRendererWidget(){
    SGRRendererGenerator* item = static_cast<SGRRendererGenerator*>(topObject);
    (*(*item).node).rendererToDelete = renderControl;
    (*(*item).node).syncerToDelete = syncControl;
}

void SGRRendererWidget::updateCustomRenderer() const {
    (*topObject).polish();
    (*topObject).update();
}
