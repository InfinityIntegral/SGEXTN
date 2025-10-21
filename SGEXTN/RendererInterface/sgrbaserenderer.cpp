#include "sgrbaserenderer.h"
#include "sgrrenderernode.h"

SGRRenderingProgramme* SGRBaseRenderer::renderingProgramme(){
    return (*node).renderingProgramme;
}
