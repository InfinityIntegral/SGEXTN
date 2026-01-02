#include <private_api_RI/SGRRendererNode.h>
#include <SGRBaseRenderer.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <QQuickWindow>
#include <rhi/qrhi.h>
#include <QQuickItem>
#include <SGRRenderingProgramme.h>
#include <stdexcept>
#include <SGRCommandRequest.h>
#include <QSGRenderNode>
#include <QRectF>
#include <SGLArray.h>
#include <SGRBaseSyncer.h>
#include <QSGNode>

SGRRendererNode::SGRRendererNode(SGRBaseRenderer *renderControl){
    (*this).rhi = (*SGXQuickInterface::applicationWindow).rhi();
    (*this).renderControl = renderControl;
    (*renderControl).node = this;
    (*this).renderingProgramme = nullptr;
    (*this).rendererToDelete = nullptr;
    (*this).syncerToDelete = nullptr;
    (*this).setFlag(QSGNode::OwnedByParent);
}

SGRRendererNode::~SGRRendererNode(){
    (*renderControl).cleanResourcesOnDestruction();
    delete renderingProgramme;
}

void SGRRendererNode::prepare(){
    QRhiResourceUpdateBatch* resourceUpdate = (*rhi).nextResourceUpdateBatch();
    if(renderingProgramme == nullptr){
        renderingProgramme = (*renderControl).createRenderingProgramme();
        if((*renderingProgramme).isFinalised == false){SGLCrash::crash("An SGEXTN internal API crashed because you forgot to finalise your rendering programme before use, use SGRRenderingProgramme::finaliseRenderingProgramme to finalise it");}
    }
    (*renderingProgramme).resourceUpdateOperation = resourceUpdate;
    SGLArray<float> builtins((*renderControl).internalX, (*renderControl).internalY, (*renderControl).internalW, (*renderControl).internalH, (*renderControl).internalWindowW, (*renderControl).internalWindowH);
    int offscreen = 0;
    if((*renderTarget()).resourceType() == QRhiResource::TextureRenderTarget){offscreen = 1;}
    (*renderingProgramme).updateShaderUniforms(0, 0, 24, builtins.pointerToData(0));
    (*renderingProgramme).updateShaderUniforms(0, 24, 4, &offscreen);
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
    (*commands).setViewport(QRhiViewport(0, 0, static_cast<float>((*renderTarget()).pixelSize().width()), static_cast<float>((*renderTarget()).pixelSize().height())));    
    (*commands).setShaderResources();
    SGRCommandRequest commandRequest(commands);
    (*renderControl).requestRenderCommands(&commandRequest);
}

void SGRRendererNode::releaseResources(){
    (*renderControl).cleanResourcesOnDestruction();
    delete renderingProgramme;
    delete rendererToDelete;
    delete syncerToDelete;
}

QSGRenderNode::RenderingFlags SGRRendererNode::flags() const {
    return (QSGRenderNode::NoExternalRendering | QSGRenderNode::BoundedRectRendering);
}

QSGRenderNode::StateFlags SGRRendererNode::changedStates() const {
    return (QSGRenderNode::ViewportState);
}

QRectF SGRRendererNode::rect() const {
    return QRectF((*renderControl).internalX, (*renderControl).internalY, (*renderControl).internalW, (*renderControl).internalH);
}
