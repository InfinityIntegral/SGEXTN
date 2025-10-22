#include "sgrbaserenderer.h"
#include "sgrrenderernode.h"

SGRBaseRenderer::SGRBaseRenderer(){
    initialised = false;
}

SGRRenderingProgramme* SGRBaseRenderer::renderingProgramme(){
    return (*node).renderingProgramme;
}
