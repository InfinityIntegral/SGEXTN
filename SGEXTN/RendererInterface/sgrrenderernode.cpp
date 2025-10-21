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
    (*this).window = SGXQuickInterface::applicationWindow;
    (*this).renderControl = renderControl;
    (*renderControl).node = this;
    (*this).renderingProgramme = nullptr;
}

SGRRendererNode::SGRRendererNode(SGRRendererNode &&x){
    (*this).renderControl = x.renderControl;
    x.renderControl = nullptr;
}

SGRRendererNode::~SGRRendererNode(){
    (*this).releaseResources();
}

void SGRRendererNode::prepare(){
    QRhi* rhi = (*window).rhi();
    QRhiResourceUpdateBatch* resourceUpdate = (*rhi).nextResourceUpdateBatch();
    if(renderingProgramme == nullptr){
        renderingProgramme = (*renderControl).createRenderingProgramme();
        if((*renderingProgramme).isFinalised == false){std::runtime_error("you forgot to finalise your rendering programme before use, use SGRRenderingProgramme::finaliseRenderingProgramme to finalise it");}
    }
    (*renderingProgramme).resourceUpdateOperation = resourceUpdate;
    float builtins[8] = {
        static_cast<float>((*associatedItem).mapToScene(QPointF(0.0f, 0.0f)).x()),
        static_cast<float>((*associatedItem).mapToScene(QPointF(0.0f, 0.0f)).y()),
        static_cast<float>((*associatedItem).width()),
        static_cast<float>((*associatedItem).height()),
        static_cast<float>((*SGXQuickInterface::applicationWindow).width()),
        static_cast<float>((*SGXQuickInterface::applicationWindow).height()),
        0.0f, 0.0f
    };
    (*renderingProgramme).updateShaderUniforms(0, 0, 32, builtins);
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
    return (QSGRenderNode::NoExternalRendering | QSGRenderNode::DepthAwareRendering);
}

QSGRenderNode::StateFlags SGRRendererNode::changedStates() const {
    return (QSGRenderNode::DepthState | QSGRenderNode::BlendState | QSGRenderNode::ViewportState);
}
