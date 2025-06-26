#include "sgxrendercutevesiclesshader.h"
#include "sgxrendercutevesiclesmaterial.h"
#include "../quickui/sgxquickuiinterface.h"
#include <QQuickWindow>
#include <QSGTexture>

SGXRenderCuteVesiclesShader::SGXRenderCuteVesiclesShader(){
    setShaderFileName(QSGMaterialShader::VertexStage, ":/cutevesicles/cutevesicles.vert.qsb");
    setShaderFileName(QSGMaterialShader::FragmentStage, ":/cutevesicles/cutevesicles.frag.qsb");
}

bool SGXRenderCuteVesiclesShader::updateGraphicsPipelineState(RenderState &, GraphicsPipelineState *ps, QSGMaterial *, QSGMaterial *){
    if((*ps).cullMode == QSGMaterialShader::GraphicsPipelineState::CullNone && (*ps).blendEnable == true){return false;}
    (*ps).cullMode = QSGMaterialShader::GraphicsPipelineState::CullNone;
    (*ps).blendEnable = true;
    return true;
}

bool SGXRenderCuteVesiclesShader::updateUniformData(RenderState &state, QSGMaterial *newMaterial, QSGMaterial *){
    SGXRenderCuteVesiclesMaterial* mat = static_cast<SGXRenderCuteVesiclesMaterial*>(newMaterial);
    char* uniformBuffer = (*state.uniformData()).data();
    QMatrix4x4 builtinMatrix = state.projectionMatrix();
    float builtinOpacity = state.opacity();
    memcpy(uniformBuffer, &builtinMatrix, 64);
    memcpy(uniformBuffer + 64, &builtinOpacity, 4);
    memcpy(uniformBuffer + 68, &((*mat).x), 4);
    memcpy(uniformBuffer + 72, &((*mat).y), 4);
    memcpy(uniformBuffer + 76, &((*mat).w), 4);
    memcpy(uniformBuffer + 80, &((*mat).h), 4);
    memcpy(uniformBuffer + 84, &((*mat).s), 4);
    return true;
}

void SGXRenderCuteVesiclesShader::updateSampledImage(RenderState &, int binding, QSGTexture **texture, QSGMaterial *newMaterial, QSGMaterial *){
    SGXRenderCuteVesiclesMaterial* mat = static_cast<SGXRenderCuteVesiclesMaterial*>(newMaterial);
    if(binding == 1){
        float* textureData = reinterpret_cast<float*>((*mat).uniformImage.bits());
        textureData[0] = (*mat).membraneColour.getRedAsFloat();
        textureData[1] = (*mat).membraneColour.getGreenAsFloat();
        textureData[2] = (*mat).membraneColour.getBlueAsFloat();
        textureData[4] = (*mat).contentsColour.getRedAsFloat();
        textureData[5] = (*mat).contentsColour.getGreenAsFloat();
        textureData[6] = (*mat).contentsColour.getBlueAsFloat();
        textureData[8] = (*mat).centerTransparency;
        textureData[9] = (*mat).edgeTransparency;
        textureData[10] = (*mat).membraneTransparency;
        for(int i=0; i<10; i++){
            textureData[12 + 2*i] = (*mat).center[i].x;
            textureData[12 + 2*i + 1] = (*mat).center[i].y;
        }
        for(int i=0; i<10; i++){
            textureData[36 + i] = (*mat).radius[i];
        }
        for(int i=0; i<10; i++){
            for(int j=0; j<8; j++){
                textureData[48 + 8*i + j] = (*mat).radiusOffset[i][j];
            }
        }
        QImage testImg = QImage(32, 1, QImage::Format_RGBA8888);
        testImg.fill(QColor(255, 0, 0));
        (*texture) = (*(*SGXQuickUIInterface::rootWindow).window()).createTextureFromImage(testImg);
        //(*texture) = (*(*SGXQuickUIInterface::rootWindow).window()).createTextureFromImage((*mat).uniformImage);
    }
}
