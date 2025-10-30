#include <private_api_RI/SGRTransparencyIndicatorRenderer.h>
#include <SGRRenderingProgramme.h>
#include <SGRGraphicsLanguageType.h>
#include <SGRVertexBufferObject.h>
#include <SGRElementBufferObject.h>
#include <SGLArray.h>
#include <SGRCommandRequest.h>
#include <SGXString.h>

SGRTransparencyIndicatorRenderer::SGRTransparencyIndicatorRenderer(){
    (*this).vbo = nullptr;
    (*this).ebo = nullptr;
}

SGRRenderingProgramme* SGRTransparencyIndicatorRenderer::createRenderingProgramme(){
    SGRRenderingProgramme* rp = new SGRRenderingProgramme(this);
    (*rp).setShaderQSBFiles(":/SGEXTN/transparencyindicator.vert.qsb", ":/SGEXTN/transparencyindicator.frag.qsb");
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
