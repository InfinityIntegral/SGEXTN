#include "sgrbasesyncer.h"
#include "sgrbaserenderer.h"
#include <QQuickItem>
#include "../quickui/sgxquickinterface.h"
#include <QQuickWindow>

void SGRBaseSyncer::syncEverything(SGRBaseRenderer *renderControl){
    sync(renderControl);
    (*renderControl).internalX = static_cast<float>((*associatedItem).mapToScene(QPointF(0.0f, 0.0f)).x());
    (*renderControl).internalY = static_cast<float>((*associatedItem).mapToScene(QPointF(0.0f, 0.0f)).y());
    (*renderControl).internalW = static_cast<float>((*associatedItem).width());
    (*renderControl).internalH = static_cast<float>((*associatedItem).height());
    (*renderControl).internalWindowW = static_cast<float>((*SGXQuickInterface::applicationWindow).width());
    (*renderControl).internalWindowH = static_cast<float>((*SGXQuickInterface::applicationWindow).height());
}

void SGRBaseSyncer::updateRenderedImage(){
    (*associatedItem).polish();
    (*associatedItem).update();
}
