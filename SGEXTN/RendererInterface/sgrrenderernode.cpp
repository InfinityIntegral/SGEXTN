#include "sgrrenderernode.h"
#include "sgrbaserenderer.h"
#include "../quickui/sgxquickinterface.h"
#include <QQuickWindow>
#include <rhi/qrhi.h>
#include <QQuickItem>
#include "sgrrenderingprogramme.h"
#include <stdexcept>
#include "sgrcommandrequest.h"

SGRRendererNode::SGRRendererNode(SGRBaseRenderer *renderControl){
    (*this).rhi = (*SGXQuickInterface::applicationWindow).rhi();
    (*this).renderControl = renderControl;
    (*renderControl).node = this;
    (*this).renderingProgramme = nullptr;
}

SGRRendererNode::~SGRRendererNode(){
    (*this).releaseResources();
}

void SGRRendererNode::prepare(){
    QRhiResourceUpdateBatch* resourceUpdate = (*rhi).nextResourceUpdateBatch();
    if(renderingProgramme == nullptr){
        renderingProgramme = (*renderControl).createRenderingProgramme();
        if((*renderingProgramme).isFinalised == false){throw std::runtime_error("you forgot to finalise your rendering programme before use, use SGRRenderingProgramme::finaliseRenderingProgramme to finalise it");}
    }
    (*renderingProgramme).resourceUpdateOperation = resourceUpdate;
    float builtins[8] = {(*renderControl).internalX, (*renderControl).internalY, (*renderControl).internalW, (*renderControl).internalH, (*renderControl).internalWindowW, (*renderControl).internalWindowH, 0.0f, 0.0f};
    if((*renderTarget()).resourceType() == QRhiResource::TextureRenderTarget){builtins[6] = 1.0f;}
    (*renderingProgramme).updateShaderUniforms(0, 0, 32, builtins);
    if((*renderControl).initialised == false){
        (*renderControl).initialised = true;
        (*renderControl).initialise();
    }
    (*renderControl).uploadShaderData();
    (*commandBuffer()).resourceUpdate(resourceUpdate);
    (*renderingProgramme).resourceUpdateOperation = nullptr;
}

void SGRRendererNode::render(const RenderState */*unused*/){
    QRhiCommandBuffer* commands = commandBuffer();
    (*commands).setGraphicsPipeline((*renderingProgramme).pipeline);
    (*commands).setViewport(QRhiViewport(0, 0, (*renderTarget()).pixelSize().width(), (*renderTarget()).pixelSize().height()));    
    (*commands).setShaderResources();
    SGRCommandRequest commandRequest(commands);
    (*renderControl).requestRenderCommands(&commandRequest);
}

void SGRRendererNode::releaseResources(){
    (*renderControl).cleanResourcesOnDestruction();
    delete renderingProgramme;
}

QSGRenderNode::RenderingFlags SGRRendererNode::flags() const {
    return (QSGRenderNode::NoExternalRendering | QSGRenderNode::BoundedRectRendering);
}

QSGRenderNode::StateFlags SGRRendererNode::changedStates() const {
    return (QSGRenderNode::ViewportState);
}

QRectF SGRRendererNode::rect() const {
    return QRectF((*associatedItem).mapToScene(QPointF(0.0f, 0.0f)).x(), (*associatedItem).mapToScene(QPointF(0.0f, 0.0f)).y(), (*associatedItem).width(), (*associatedItem).height());
}
