#include "sgrtransparencyindicatorrenderer.h"
#include "../sgrrenderingprogramme.h"
#include "../sgrgraphicslanguagetype.h"
#include "../sgrvertexbufferobject.h"
#include "../sgrelementbufferobject.h"
#include "../../containers/sglarray.h"
#include "../sgrcommandrequest.h"
#include "../../primitives/sgxstring.h"

SGRTransparencyIndicatorRenderer::SGRTransparencyIndicatorRenderer(){
    (*this).vbo = nullptr;
    (*this).ebo = nullptr;
}

SGRRenderingProgramme* SGRTransparencyIndicatorRenderer::createRenderingProgramme(){
    SGRRenderingProgramme* rp = new SGRRenderingProgramme(this);
    (*rp).setShaderQSBFiles(":/SGEXTN/RendererInterface/transparencyindicator/transparencyindicator.vert.qsb", ":/SGEXTN/RendererInterface/transparencyindicator/transparencyindicator.frag.qsb");
    (*rp).finaliseShaderResource();
    (*rp).addVertexBufferObject(2 * 4);
    (*rp).addVertexProperty(0, 0, 0, SGRGraphicsLanguageType::Float, 2);
    (*rp).finaliseVertices();
    (*rp).finaliseRenderingProgramme();
    return rp;
}

void SGRTransparencyIndicatorRenderer::initialise(){
    vbo = new SGRVertexBufferObject(this, 4 * 2 * 4);
    SGLArray<float> vt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    (*renderingProgramme()).updateDataBuffer(vbo, 0, 4 * 2 * 4, vt.pointerToData(0));
    ebo = new SGRElementBufferObject(this, 2 * 3 * 4);
    SGLArray<int> et(0, 1, 2, 1, 2, 3);
    (*renderingProgramme()).updateDataBuffer(ebo, 0, 2 * 3 * 4, et.pointerToData(0));
}

void SGRTransparencyIndicatorRenderer::cleanResourcesOnDestruction(){
    delete vbo;
    delete ebo;
}

void SGRTransparencyIndicatorRenderer::uploadShaderData(){
    
}

void SGRTransparencyIndicatorRenderer::requestRenderCommands(SGRCommandRequest *commandRequest){
    (*commandRequest).addVertexBufferObject(vbo, 0);
    (*commandRequest).chooseElementBufferObject(ebo);
    (*commandRequest).finaliseForDraw();
    (*commandRequest).drawTriangles(2, 0);
}
