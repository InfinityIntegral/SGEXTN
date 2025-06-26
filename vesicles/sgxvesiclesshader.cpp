#include "sgxvesiclesshader.h"
#include "sgxvesiclesmaterial.h"
#include <QSGMaterial>

SGXVesiclesShader::SGXVesiclesShader(){
    setShaderFileName(QSGMaterialShader::VertexStage, ":/vesicles/vesicles.vert.qsb");
    setShaderFileName(QSGMaterialShader::FragmentStage, ":/vesicles/vesicles.frag.qsb");
}

bool SGXVesiclesShader::updateUniformData(RenderState& udh, QSGMaterial *newMaterial, QSGMaterial *){
    SGXVesiclesMaterial* material = static_cast<SGXVesiclesMaterial*>(newMaterial);
    char* ub = (*udh.uniformData()).data();
    QMatrix4x4 transformMatrix = udh.projectionMatrix();
    float transformOpacity = udh.opacity();
    memcpy(ub, &transformMatrix, 64);
    memcpy(ub + 64, &transformOpacity, 4);
    memcpy(ub + 68, &((*material).x), 4);
    memcpy(ub + 72, &((*material).y), 4);
    memcpy(ub + 76, &((*material).w), 4);
    memcpy(ub + 80, &((*material).h), 4);
    memcpy(ub + 84, &((*material).s), 4);
    memcpy(ub + 88, &((*material).cx), 4);
    memcpy(ub + 92, &((*material).cy), 4);
    memcpy(ub + 96, &((*material).r), 4);
    return true;
}

bool SGXVesiclesShader::updateGraphicsPipelineState(RenderState &, GraphicsPipelineState *ps, QSGMaterial *, QSGMaterial *){
    if((*ps).cullMode == QSGMaterialShader::GraphicsPipelineState::CullNone && (*ps).blendEnable == true){return false;}
    (*ps).cullMode = QSGMaterialShader::GraphicsPipelineState::CullNone;
    (*ps).blendEnable = true;
    return true;
}
