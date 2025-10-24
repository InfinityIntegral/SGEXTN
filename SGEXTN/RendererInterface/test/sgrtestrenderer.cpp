#include "sgrtestrenderer.h"
#include "../sgrvertexbufferobject.h"
#include "../sgrelementbufferobject.h"
#include "../sgrrenderingprogramme.h"
#include "../sgrcommandrequest.h"
#include "../sgrimage.h"

SGRTestRenderer::SGRTestRenderer(){
    (*this).vboPosition = nullptr;
    (*this).vboColour = nullptr;
    (*this).ebo = nullptr;
    (*this).img = nullptr;
}

SGRRenderingProgramme* SGRTestRenderer::createRenderingProgramme(){
    SGRRenderingProgramme* rp = new SGRRenderingProgramme(this);
    (*rp).setShaderQSBFiles(":/SGEXTN/RendererInterface/test/test.vert.qsb", ":/SGEXTN/RendererInterface/test/test.frag.qsb");
    (*rp).addTexture(1);
    (*rp).finaliseShaderResource();
    (*rp).addVertexBufferObject(3 * 4);
    (*rp).addVertexBufferObject(2 * 4);
    (*rp).addVertexProperty(0, 0, 0, SGRGraphicsLanguageType::Float, 3);
    (*rp).addVertexProperty(1, 0, 1, SGRGraphicsLanguageType::Float, 2);
    (*rp).finaliseVertices();
    (*rp).finaliseRenderingProgramme();
    return rp;
}

void SGRTestRenderer::cleanResourcesOnDestruction(){
    delete vboPosition;
    delete vboColour;
    delete ebo;
    delete img;
}

void SGRTestRenderer::initialise(){
    vboPosition = new SGRVertexBufferObject(this, 3 * 3 * 4);
    float vpt[3 * 3] = {
        0.5f, 0.0f, 0.99f,
        0.0f, 1.0f, 0.99f,
        1.0f, 1.0f, 0.99f
    };
    (*renderingProgramme()).updateDataBuffer(vboPosition, 0, 3 * 3 * 4, vpt);
    vboColour = new SGRVertexBufferObject(this, 3 * 2 * 4);
    float vct[3 * 2] = {
        0.003f, 0.8f,
        0.0f, 0.827f,
        0.006f, 0.827f
    };
    (*renderingProgramme()).updateDataBuffer(vboColour, 0, 3 * 2 * 4, vct);
    ebo = new SGRElementBufferObject(this, 1 * 3 * 4);
    int et[1 * 3] = {0, 1, 2};
    (*renderingProgramme()).updateDataBuffer(ebo, 0, 1 * 3 * 4, et);
    img = new SGRImage(":/SGEXTN/bg.jpg");
    (*renderingProgramme()).updateTexture(1, img);
}

void SGRTestRenderer::uploadShaderData(){
    
}

void SGRTestRenderer::requestRenderCommands(SGRCommandRequest *commandRequest){
    (*commandRequest).addVertexBufferObject(vboPosition, 0);
    (*commandRequest).addVertexBufferObject(vboColour, 0);
    (*commandRequest).chooseElementBufferObject(ebo);
    (*commandRequest).finaliseForDraw();
    (*commandRequest).drawTriangles(1, 0);
}
