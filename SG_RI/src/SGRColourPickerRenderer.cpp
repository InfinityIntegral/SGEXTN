#include <private_api_RI/SGRColourPickerRenderer.h>
#include <SGRVertexBufferObject.h>
#include <SGRElementBufferObject.h>
#include <SGRRenderingProgramme.h>
#include <SGRGraphicsLanguageType.h>
#include <SGLArray.h>
#include <SGXString.h>
#include <SGRCommandRequest.h>

SGRColourPickerRenderer::SGRColourPickerRenderer(int type){
    (*this).type = type;
    (*this).hue = 0.0f;
    (*this).saturation = 0.0f;
    (*this).lightness = 0.0f;
    (*this).transparency = 0.0f;
    (*this).vbo = nullptr;
    (*this).ebo = nullptr;
}

SGRRenderingProgramme* SGRColourPickerRenderer::createRenderingProgramme(){
    SGRRenderingProgramme* rp = new SGRRenderingProgramme(this);
    (*rp).setShaderQSBFiles(":/SGEXTN/colourpicker.vert.qsb", ":/SGEXTN/colourpicker.frag.qsb");
    (*rp).addUniformBufferObject(20, 1);
    (*rp).finaliseShaderResource();
    (*rp).addVertexBufferObject(2 * 4);
    (*rp).addVertexProperty(0, 0, 0, SGRGraphicsLanguageType::Float, 2);
    (*rp).finaliseVertices();
    (*rp).finaliseRenderingProgramme();
    return rp;
}

void SGRColourPickerRenderer::initialise(){
    vbo = new SGRVertexBufferObject(this, 4 * 2 * 4);
    SGLArray<float> vt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    (*renderingProgramme()).updateDataBuffer(vbo, 0, 4 * 2 * 4, vt.pointerToData(0));
    ebo = new SGRElementBufferObject(this, 2 * 3 * 4);
    SGLArray<int> et(0, 1, 2, 1, 2, 3);
    (*renderingProgramme()).updateDataBuffer(ebo, 0, 2 * 3 * 4, et.pointerToData(0));
}

void SGRColourPickerRenderer::cleanResourcesOnDestruction(){
    delete vbo;
    delete ebo;
}

void SGRColourPickerRenderer::uploadShaderData(){
    SGLArray<float> ut(hue, saturation, lightness, transparency);
    (*renderingProgramme()).updateShaderUniforms(1, 0, 16, ut.pointerToData(0));
    (*renderingProgramme()).updateShaderUniforms(1, 16, 4, &type);
}

void SGRColourPickerRenderer::requestRenderCommands(SGRCommandRequest *commandRequest){
    (*commandRequest).addVertexBufferObject(vbo, 0);
    (*commandRequest).chooseElementBufferObject(ebo);
    (*commandRequest).finaliseForDraw();
    (*commandRequest).drawTriangles(2, 0);
}
