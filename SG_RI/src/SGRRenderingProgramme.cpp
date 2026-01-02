#include <SGRRenderingProgramme.h>
#include <rhi/qrhi.h>
#include <private_api_RI/SGRRendererNode.h>
#include <QFile>
#include <SGXString.h>
#include <SGLVector.h>
#include <private_api_RI/SGRVertexProperty.h>
#include <SGLPair.h>
#include <SGRCommandRequest.h>
#include <SGRDataBuffer.h>
#include <SGRBaseRenderer.h>
#include <private_api_RI/SGRTexture.h>
#include <SGRImage.h>
#include <SGRGraphicsLanguageType.h>
#include <QIODevice>
#include <rhi/qshader.h>
#include <private_api_Containers/SGLCrash.h>

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
    if(renderControl == nullptr){SGLCrash::crash("SGRRenderingProgramme constructor crashed because the associated render control object is nullptr");}

    (*this).vertexShader = nullptr;
    (*this).fragmentShader = nullptr;
    (*this).shaderResources = nullptr;
    (*this).resourceUpdateOperation = nullptr;
    
    (*this).node = (*renderControl).node;
    (*this).rhi = (*node).rhi;
    
    pipeline = (*rhi).newGraphicsPipeline();
    (*pipeline).setTopology(QRhiGraphicsPipeline::Triangles);

    QRhiGraphicsPipeline::TargetBlend blendFunction;
    blendFunction.enable = true;
    (*pipeline).setTargetBlends({blendFunction});
    
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

void SGRRenderingProgramme::addVertexBufferObject(int vertexSize) const {
    if(vertexSize <= 0){SGLCrash::crash("SGRRenderingProgramme::addVertexBufferObject crashed because the vertex size is zero or negative");}
    (*vertexBufferObjects).pushBack(vertexSize);
}

void SGRRenderingProgramme::addVertexProperty(int vertexBufferObjectIndex, int offsetFromVertexStart, int shaderDeclaredLocation, SGRGraphicsLanguageType::Type propertyType, int vectorLength) const {
    if(offsetFromVertexStart < 0){SGLCrash::crash("SGRRenderingProgramme::addVertexProperty crashed because the offset from the start of the vertex is negative");}
    if(vertexBufferObjectIndex < 0){SGLCrash::crash("SGRRenderingProgramme::addVertexProperty crashed because the index of the vertex buffer object is negative");}
    if(vectorLength < 1 || vectorLength > 4){SGLCrash::crash("SGRRenderingProgramme::addVertexProperty crashed because the vector length is not between 1 to 4 inclusive");}
    (*vertexProperties).pushBack(SGRVertexProperty(vertexBufferObjectIndex, offsetFromVertexStart, shaderDeclaredLocation, propertyType, vectorLength));
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

void SGRRenderingProgramme::addUniformBufferObject(int std140AlignedSize, int shaderDeclaredBinding) const {
    (*uniformBufferObjects).pushBack(SGLPair<int, int>(std140AlignedSize, shaderDeclaredBinding));
}

void SGRRenderingProgramme::addTexture(int shaderDeclaredBinding) const {
    (*textureObjects).pushBack(shaderDeclaredBinding);
}

void SGRRenderingProgramme::finaliseShaderResource(){
    SGLVector<QRhiShaderResourceBinding> resourceBindings;
    {
        QRhiBuffer* uniformBuffer = (*rhi).newBuffer(QRhiBuffer::Dynamic, QRhiBuffer::UniformBuffer, 28);
        (*uniformBuffer).create();
        resourceBindings.pushBack(QRhiShaderResourceBinding::uniformBuffer(0, QRhiShaderResourceBinding::VertexStage | QRhiShaderResourceBinding::FragmentStage, uniformBuffer));
        (*uniformBuffers).pushBack(SGLPair<int, QRhiBuffer*>(0, uniformBuffer));
    }
    for(int i=0; i<(*uniformBufferObjects).length(); i++){
        if((*uniformBufferObjects).at(i).second == 0){SGLCrash::crash("SGRRenderingProgramme::finaliseShaderResource crashed because a uniform buffer object has been attached at binding point 0, uniform buffer binding point 0 is reserved for the SG RI internal uniform buffer object which stores information about the custom renderer, pls attach your own uniform buffer objects to binding points starting from 1");}
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
    if(shadersAreSet == false){SGLCrash::crash("SGRRenderingProgramme::finaliseRenderingProgramme crashed because you forgot to attach QSB shader binaries to the rendering programme, use SGRRenderingProgramme::setShaderQSBFiles to attach them");}
    if(vertexFormattingIsSet == false){SGLCrash::crash("SGRRenderingProgramme::finaliseRenderingProgramme crashed because you forgot to specify the type of data taken as input by your vertex shader and the location of that data, use SGRRenderingProgramme::finaliseVertices to specify these, you must finalise vertex properties after adding them");}
    if(shaderResourceIsSet == false){SGLCrash::crash("SGRRenderingProgramme::finaliseRenderingProgramme crashed because you forgot to specify the shader resources (uniform buffers, textures, storage buffers) used by the shaders, use SGRRenderingProgramme::finaliseShaderResources to specify this, you must finalise shader resources after adding them, and you still must finalise these even if you did not add anything");}
    (*pipeline).setRenderPassDescriptor((*(*node).renderTarget()).renderPassDescriptor());
    (*pipeline).create();
    isFinalised = true;
}

void SGRRenderingProgramme::updateDataBuffer(SGRDataBuffer *buffer, int startLocation, int dataSize, void *pointerToData) const {
    if(buffer == nullptr){SGLCrash::crash("SGRRenderingProgramme::updateDataBuffer crashed because the target buffer is nullptr");}
    if(pointerToData == nullptr){SGLCrash::crash("SGRRenderingProgramme::updateDataBuffer crashed because the source data is nullptr");}
    if(startLocation < 0){SGLCrash::crash("SGRRenderingProgramme::updateDataBuffer crashed because the starting location is negative");}
    if(dataSize < 0){SGLCrash::crash("SGRRenderingProgramme::updateDataBuffer crashed because the length of the data to update is negative");}
    if(startLocation + dataSize > (*buffer).length()){SGLCrash::crash("SGRRenderingProgramme::updateDataBuffer crashed because the ending location, or starting location + length - 1, points beyond the end of the buffer");}
    (*resourceUpdateOperation).updateDynamicBuffer((*buffer).data, startLocation, dataSize, pointerToData);
}

void SGRRenderingProgramme::updateShaderUniforms(int shaderDeclaredBinding, int startLocation, int dataSize, void *pointerToData) const {
    if(shaderDeclaredBinding < 0){SGLCrash::crash("SGRRenderingProgramme::updateShaderUniforms crashed because the specified binding point is negative");}
    if(pointerToData == nullptr){SGLCrash::crash("SGRRenderingProgramme::updateShaderUniforms crashed because the source data is nullptr");}
    if(startLocation < 0){SGLCrash::crash("SGRRenderingProgramme::updateShaderUniforms crashed because the starting location is negative");}
    if(dataSize < 0){SGLCrash::crash("SGRRenderingProgramme::updateShaderUniforms crashed because the length of the data to update is negative");}
    QRhiBuffer* buffer = nullptr;
    for(int i=0; i<(*uniformBuffers).length(); i++){
        if((*uniformBuffers).at(i).first == shaderDeclaredBinding){
            buffer = (*uniformBuffers).at(i).second;
            break;
        }
    }
    if(buffer == nullptr){SGLCrash::crash("SGRRenderingProgramme::updateShaderUniforms crashed because you attempted to upload uniforms to a nonexistent binding point");}
    (*resourceUpdateOperation).updateDynamicBuffer(buffer, startLocation, dataSize, pointerToData);
}

void SGRRenderingProgramme::updateTexture(int shaderDeclaredBinding, SGRImage *sourceImage) const {
    if(shaderDeclaredBinding < 0){SGLCrash::crash("SGRRenderingProgramme::updateTexture crashed because the specified binding point is negative");}
    if(sourceImage == nullptr){SGLCrash::crash("SGRRenderingProgramme::updateTexture crashed because the source image is nullptr");}
    const SGRTexture* texture = nullptr;
    for(int i=0; i<(*textures).length(); i++){
        if((*textures).at(i).first == shaderDeclaredBinding){
            texture = (*textures).at(i).second;
            break;
        }
    }
    if(texture == nullptr){SGLCrash::crash("SGRRenderingProgramme::updateTexture crashed because you attempted to upload a texture to a nonexistent binding point");}
    (*(*texture).data).setPixelSize(QSize((*sourceImage).width(), (*sourceImage).height()));
    (*(*texture).data).create();
    (*resourceUpdateOperation).uploadTexture((*texture).data, (*(*sourceImage).data));
}
