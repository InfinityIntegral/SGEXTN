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
    qDebug() << "updating graphics pipeline";
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
    float membraneR = (*mat).membraneColour.getRedAsFloat();
    float membraneG = (*mat).membraneColour.getGreenAsFloat();
    float membraneB = (*mat).membraneColour.getBlueAsFloat();
    float contentsR = (*mat).contentsColour.getRedAsFloat();
    float contentsG = (*mat).contentsColour.getGreenAsFloat();
    float contentsB = (*mat).contentsColour.getBlueAsFloat();
    memcpy(uniformBuffer + 88, &membraneR, 4);
    memcpy(uniformBuffer + 92, &membraneG, 4);
    memcpy(uniformBuffer + 96, &membraneB, 4);
    memcpy(uniformBuffer + 100, &contentsR, 4);
    memcpy(uniformBuffer + 104, &contentsG, 4);
    memcpy(uniformBuffer + 108, &contentsB, 4);
    memcpy(uniformBuffer + 112, &((*mat).centerTransparency), 4);
    memcpy(uniformBuffer + 116, &((*mat).edgeTransparency), 4);
    memcpy(uniformBuffer + 120, &((*mat).membraneTransparency), 4);
    memcpy(uniformBuffer + 124, &((*mat).membraneThickness), 4);
    memcpy(uniformBuffer + 128, &((*mat).center[0].x), 4);
    memcpy(uniformBuffer + 132, &((*mat).center[0].y), 4);
    float offsetRadius = 0.0f;
    for(int i=0; i<8; i++){
        offsetRadius = (*mat).radius[0] + (*mat).radiusOffset[0][i] * (*mat).radius[0];
        memcpy(uniformBuffer + 144 + 16 * i, &offsetRadius, 4);
    }
    offsetRadius = (*mat).radius[0] + (*mat).radiusOffset[0][0] * (*mat).radius[0];
    memcpy(uniformBuffer + 272, &offsetRadius, 4);
    return true;
}
