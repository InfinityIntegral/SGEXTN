#include <SGRBaseRenderer.h>
#include <private_api_RI/SGRRendererNode.h>

SGRBaseRenderer::SGRBaseRenderer(){
    initialised = false;
    node = nullptr;
    internalX = 0.0f;
    internalY = 0.0f;
    internalW = 0.0f;
    internalH = 0.0f;
    internalWindowW = 0.0f;
    internalWindowH = 0.0f;
}

SGRRenderingProgramme* SGRBaseRenderer::renderingProgramme() const {
    return (*node).renderingProgramme;
}
