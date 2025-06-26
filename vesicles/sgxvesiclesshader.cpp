#include "sgxvesiclesshader.h"
#include "sgxvesiclesmaterial.h"

SGXVesiclesShader::SGXVesiclesShader(){
    setShaderFileName(QSGMaterialShader::VertexStage, ":/vesicles/vesicles.vert.qsb");
    setShaderFileName(QSGMaterialShader::FragmentStage, ":/vesicles/vesicles.frag.qsb");
}

bool SGXVesiclesShader::updateUniformData(RenderState& udh, QSGMaterial *newMaterial, QSGMaterial *){
    SGXVesiclesMaterial* material = static_cast<SGXVesiclesMaterial*>(newMaterial);
    char* ub = (*udh.uniformData()).data();
    memcpy(ub + 68, &((*material).c), 4);
    memcpy(ub + 72, &((*material).r), 4);
    return true;
}

bool SGXVesiclesShader::updateGraphicsPipelineState(RenderState &, GraphicsPipelineState *ps, QSGMaterial *, QSGMaterial *){
    if((*ps).cullMode == QSGMaterialShader::GraphicsPipelineState::CullNone && (*ps).blendEnable == true){return false;}
    (*ps).cullMode = QSGMaterialShader::GraphicsPipelineState::CullNone;
    (*ps).blendEnable = true;
    return true;
}
