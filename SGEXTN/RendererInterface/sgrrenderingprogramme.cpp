#include "sgrrenderingprogramme.h"
#include <rhi/qrhi.h>
#include "sgrrenderernode.h"
#include <QFile>
#include "../primitives/sgxstring.h"
#include "../containers/sglvector.h"
#include "sgrvertexproperty.h"
#include "../containers/sglpair.h"
#include <stdexcept>
#include "sgrcommandrequest.h"
#include "sgrdatabuffer.h"
#include "sgrbaserenderer.h"
#include "sgrtexture.h"
#include "sgrimage.h"

namespace {
QRhiVertexInputAttribute::Format temp_getVertexAttributeType(SGRGraphicsLanguageType::Type type, int vectorLength){
    if(type == SGRGraphicsLanguageType::Float){
        if(vectorLength == 1){return QRhiVertexInputAttribute::Float;}
        if(vectorLength == 2){return QRhiVertexInputAttribute::Float2;}
        if(vectorLength == 3){return QRhiVertexInputAttribute::Float3;}
        return QRhiVertexInputAttribute::Float4;
    }
    if(type == SGRGraphicsLanguageType::Int){
        if(vectorLength == 1){return QRhiVertexInputAttribute::SInt;}
        if(vectorLength == 2){return QRhiVertexInputAttribute::SInt2;}
        if(vectorLength == 3){return QRhiVertexInputAttribute::SInt3;}
        return QRhiVertexInputAttribute::SInt4;
    }
    if(vectorLength == 1){return QRhiVertexInputAttribute::UInt;}
    if(vectorLength == 2){return QRhiVertexInputAttribute::UInt2;}
    if(vectorLength == 3){return QRhiVertexInputAttribute::UInt3;}
    return QRhiVertexInputAttribute::UInt4;
}
}

SGRRenderingProgramme::SGRRenderingProgramme(SGRBaseRenderer *renderControl){
    (*this).node = (*renderControl).node;
    (*this).rhi = (*node).rhi;
    
    pipeline = (*rhi).newGraphicsPipeline();
    (*pipeline).setTopology(QRhiGraphicsPipeline::Triangles);

    QRhiGraphicsPipeline::TargetBlend blendFunction;
    blendFunction.enable = true;
    (*pipeline).setTargetBlends({blendFunction});
    
    (*pipeline).setDepthTest(true);
    (*pipeline).setDepthWrite(true);
    (*pipeline).setDepthOp(QRhiGraphicsPipeline::Less);
    
    vertexBufferObjects = new SGLVector<int>();
    vertexProperties = new SGLVector<SGRVertexProperty>();
    uniformBufferObjects = new SGLVector<SGLPair<int, int>>();
    textureObjects = new SGLVector<int>();
    uniformBuffers = new SGLVector<SGLPair<int, QRhiBuffer*>>();
    textures = new SGLVector<SGLPair<int, SGRTexture*>>();
    
    shadersAreSet = false;
    vertexFormattingIsSet = false;
    shaderResourceIsSet = false;
    isFinalised = false;
}

SGRRenderingProgramme::~SGRRenderingProgramme(){
    (*pipeline).destroy();
    delete pipeline;
    delete vertexShader;
    delete fragmentShader;
    delete vertexBufferObjects;
    delete vertexProperties;
    delete uniformBufferObjects;
    delete textureObjects;
    for(int i=0; i<(*uniformBuffers).length(); i++){
        (*(*uniformBuffers).at(i).second).destroy();
        delete (*uniformBuffers).at(i).second;
    }
    delete uniformBuffers;
    for(int i=0; i<(*textures).length(); i++){
        (*(*(*textures).at(i).second).data).destroy();
        delete (*textures).at(i).second;
    }
    delete textures;
    (*shaderResources).destroy();
    delete shaderResources;
}

void SGRRenderingProgramme::setShaderQSBFiles(const SGXString &vertexShaderPath, const SGXString &fragmentShaderPath){
    {
        QFile v(*vertexShaderPath.data);
        (void)v.open(QIODevice::ReadOnly);
        vertexShader = new QRhiShaderStage(QRhiShaderStage::Vertex, QShader::fromSerialized(v.readAll()));
    }
    {
        QFile v(*fragmentShaderPath.data);
        (void)v.open(QIODevice::ReadOnly);
        fragmentShader = new QRhiShaderStage(QRhiShaderStage::Fragment, QShader::fromSerialized(v.readAll()));
    }
    (*pipeline).setShaderStages({*vertexShader, *fragmentShader});
    shadersAreSet = true;
}

void SGRRenderingProgramme::addVertexBufferObject(int vertexSize){
    (*vertexBufferObjects).pushBack(vertexSize);
}

void SGRRenderingProgramme::addVertexProperty(int vertexBufferObjectIndex, int offsetFromVertexStart, int shaderDeclaredLocation, SGRGraphicsLanguageType::Type propertyType, int vectorLength){
    SGRVertexProperty vp(vertexBufferObjectIndex, offsetFromVertexStart, shaderDeclaredLocation, propertyType, vectorLength);
    (*vertexProperties).pushBack(vp);
}

void SGRRenderingProgramme::finaliseVertices(){
    SGLVector<QRhiVertexInputBinding> vb;
    for(int i=0; i<(*vertexBufferObjects).length(); i++){
        vb.pushBack(QRhiVertexInputBinding((*vertexBufferObjects).at(i)));
    }
    SGLVector<QRhiVertexInputAttribute> va;
    for(int i=0; i<(*vertexProperties).length(); i++){
        va.pushBack(QRhiVertexInputAttribute((*vertexProperties).at(i).vertexBufferObjectIndex, (*vertexProperties).at(i).shaderDeclaredLocation, temp_getVertexAttributeType((*vertexProperties).at(i).propertyType, (*vertexProperties).at(i).vectorLength), (*vertexProperties).at(i).offsetFromVertexStart));
    }
    QRhiVertexInputLayout vl;
    vl.setBindings(vb.pointerToData(0), vb.pointerToData(vb.length()));
    vl.setAttributes(va.pointerToData(0), va.pointerToData(va.length()));
    (*pipeline).setVertexInputLayout(vl);
    vertexFormattingIsSet = true;
}

void SGRRenderingProgramme::addUniformBufferObject(int std140AlignedSize, int shaderDeclaredBinding){
    (*uniformBufferObjects).pushBack(SGLPair<int, int>(std140AlignedSize, shaderDeclaredBinding));
}

void SGRRenderingProgramme::addTexture(int shaderDeclaredBinding){
    (*textureObjects).pushBack(shaderDeclaredBinding);
}

void SGRRenderingProgramme::finaliseShaderResource(){
    SGLVector<QRhiShaderResourceBinding> resourceBindings;
    {
        QRhiBuffer* uniformBuffer = (*rhi).newBuffer(QRhiBuffer::Dynamic, QRhiBuffer::UniformBuffer, 32);
        (*uniformBuffer).create();
        resourceBindings.pushBack(QRhiShaderResourceBinding::uniformBuffer(0, QRhiShaderResourceBinding::VertexStage | QRhiShaderResourceBinding::FragmentStage, uniformBuffer));
        (*uniformBuffers).pushBack(SGLPair<int, QRhiBuffer*>(0, uniformBuffer));
    }
    for(int i=0; i<(*uniformBufferObjects).length(); i++){
        if((*uniformBufferObjects).at(i).second == 0){throw std::runtime_error("uniform buffer binding point 0 is reserved for the SG RI internal uniform buffer object which stores information about the custom renderer, pls attach your own uniform buffer objects to binding points starting from 1");}
        QRhiBuffer* uniformBuffer = (*rhi).newBuffer(QRhiBuffer::Dynamic, QRhiBuffer::UniformBuffer, (*uniformBufferObjects).at(i).first);
        (*uniformBuffer).create();
        resourceBindings.pushBack(QRhiShaderResourceBinding::uniformBuffer((*uniformBufferObjects).at(i).second, QRhiShaderResourceBinding::VertexStage | QRhiShaderResourceBinding::FragmentStage, uniformBuffer));
        (*uniformBuffers).pushBack(SGLPair<int, QRhiBuffer*>((*uniformBufferObjects).at(i).second, uniformBuffer));
    }
    for(int i=0; i<(*textureObjects).length(); i++){
        SGRTexture* texture = new SGRTexture(rhi);
        resourceBindings.pushBack(QRhiShaderResourceBinding::sampledTexture((*textureObjects).at(i), QRhiShaderResourceBinding::VertexStage | QRhiShaderResourceBinding::FragmentStage, (*texture).data, (*texture).textureSampler));
        (*textures).pushBack(SGLPair<int, SGRTexture*>((*textureObjects).at(i), texture));
    }
    shaderResources = (*rhi).newShaderResourceBindings();
    (*shaderResources).setBindings(resourceBindings.pointerToData(0), resourceBindings.pointerToData(resourceBindings.length()));
    (*shaderResources).create();
    (*pipeline).setShaderResourceBindings(shaderResources);
    shaderResourceIsSet = true;
}

void SGRRenderingProgramme::finaliseRenderingProgramme(){
    if(shadersAreSet == false){
        throw std::runtime_error("you forgot to attach QSB shader binaries to the rendering programme, use SGRRenderingProgramme::setShaderQSBFiles to attach them");
    }
    if(vertexFormattingIsSet == false){
        throw std::runtime_error("you forgot to specify the type of data taken as input by your vertex shader and the location of that data, use SGRRenderingProgramme::finaliseVertices to specify these, you must finalise vertex properties after adding them");
    }
    if(shaderResourceIsSet == false){
        throw std::runtime_error("you forgot to specify the shader resources (uniform buffers, textures, storage buffers) used by the shaders, use SGRRenderingProgramme::finaliseShaderResources to specify this, you must finalise shader resources after adding them, and you still must finalise these even if you did not add anything");
    }
    (*pipeline).setRenderPassDescriptor((*(*node).renderTarget()).renderPassDescriptor());
    (*pipeline).create();
    isFinalised = true;
}

void SGRRenderingProgramme::updateDataBuffer(SGRDataBuffer *buffer, int startLocation, int dataSize, void *pointerToData){
    (*resourceUpdateOperation).updateDynamicBuffer((*buffer).data, startLocation, dataSize, pointerToData);
}

void SGRRenderingProgramme::updateShaderUniforms(int shaderDeclaredBinding, int startLocation, int dataSize, void *pointerToData){
    QRhiBuffer* buffer = nullptr;
    for(int i=0; i<(*uniformBuffers).length(); i++){
        if((*uniformBuffers).at(i).first == shaderDeclaredBinding){
            buffer = (*uniformBuffers).at(i).second;
            break;
        }
    }
    if(buffer == nullptr){throw std::runtime_error("you attempted to upload uniforms to a nonexistent binding point");}
    (*resourceUpdateOperation).updateDynamicBuffer(buffer, startLocation, dataSize, pointerToData);
}

void SGRRenderingProgramme::updateTexture(int shaderDeclaredBinding, SGRImage *sourceImage){
    SGRTexture* texture = nullptr;
    for(int i=0; i<(*textures).length(); i++){
        if((*textures).at(i).first == shaderDeclaredBinding){
            texture = (*textures).at(i).second;
            break;
        }
    }
    if(texture == nullptr){throw std::runtime_error("you attempted to upload a texture to a nonexistent binding point");}
    (*(*texture).data).setPixelSize(QSize((*sourceImage).width(), (*sourceImage).height()));
    (*(*texture).data).create();
    (*resourceUpdateOperation).uploadTexture((*texture).data, (*(*sourceImage).data));
}
