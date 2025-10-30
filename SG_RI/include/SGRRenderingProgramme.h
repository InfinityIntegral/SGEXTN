#ifndef SGRRENDERINGPROGRAMME_H
#define SGRRENDERINGPROGRAMME_H

#include <SGRGraphicsLanguageType.h>

#include <private_api_RI/SG_Build_RI.h>

class SGXString;
class QRhiGraphicsPipeline;
class SGRRendererNode;
class QRhiShaderStage;
template <typename T> class SGLVector;
class SGRVertexProperty;
template <typename T1, typename T2> class SGLPair;
class QRhiShaderResourceBindings;
class QRhiBuffer;
class QRhiResourceUpdateBatch;
class SGRDataBuffer;
class QRhi;
class SGRBaseRenderer;
class SGRTexture;
class SGRImage;
class SG_RI_DLL SGRRenderingProgramme
{
public:
    SGRRenderingProgramme(SGRBaseRenderer* renderControl);
    SGRRenderingProgramme(const SGRRenderingProgramme&) = delete;
    SGRRenderingProgramme& operator=(const SGRRenderingProgramme&) = delete;
    SGRRenderingProgramme(SGRRenderingProgramme&& x) = delete;
    SGRRenderingProgramme& operator=(SGRRenderingProgramme&& x) = delete;
    ~SGRRenderingProgramme();
    
    QRhiGraphicsPipeline* pipeline;
    SGRRendererNode* node;
    QRhi* rhi;
    
    bool shadersAreSet;
    QRhiShaderStage* vertexShader;
    QRhiShaderStage* fragmentShader;
    void setShaderQSBFiles(const SGXString& vertexShaderPath, const SGXString& fragmentShaderPath);
    
    bool vertexFormattingIsSet;
    SGLVector<int>* vertexBufferObjects;
    void addVertexBufferObject(int vertexSize) const;
    SGLVector<SGRVertexProperty>* vertexProperties;
    void addVertexProperty(int vertexBufferObjectIndex, int offsetFromVertexStart, int shaderDeclaredLocation, SGRGraphicsLanguageType::Type propertyType, int vectorLength) const;
    void finaliseVertices();
    
    bool shaderResourceIsSet;
    SGLVector<SGLPair<int, int>>* uniformBufferObjects;
    SGLVector<int>* textureObjects;
    void addUniformBufferObject(int std140AlignedSize, int shaderDeclaredBinding) const;
    void addTexture(int shaderDeclaredBinding) const;
    QRhiShaderResourceBindings* shaderResources;
    SGLVector<SGLPair<int, QRhiBuffer*>>* uniformBuffers;
    SGLVector<SGLPair<int, SGRTexture*>>* textures;
    void finaliseShaderResource();
    
    void finaliseRenderingProgramme();
    bool isFinalised;
    
    QRhiResourceUpdateBatch* resourceUpdateOperation;
    void updateDataBuffer(SGRDataBuffer* buffer, int startLocation, int dataSize, void* pointerToData) const;
    void updateShaderUniforms(int shaderDeclaredBinding, int startLocation, int dataSize, void* pointerToData) const;
    void updateTexture(int shaderDeclaredBinding, SGRImage* sourceImage) const;
};

#endif // SGRRENDERINGPROGRAMME_H
