#include "sgxvesiclesshader.h"
#include "sgxvesiclesmaterial.h"

SGXVesiclesShader::SGXVesiclesShader(){
    setShaderFileName(QSGMaterialShader::VertexStage, ":/vesicles/vesicles.vert.qsb");
    setShaderFileName(QSGMaterialShader::FragmentStage, ":/vesicles/vesicles.frag.qsb");
}

bool SGXVesiclesShader::updateUniformData(RenderState &, QSGMaterial *newMaterial, QSGMaterial *){
    SGXVesiclesMaterial* material = static_cast<SGXVesiclesMaterial*>(newMaterial);
    char* ub = (*(*material).uniformData()).data();
    memcpy(ub, (*material).matrix.constData(), 64);
    memcpy(ub + 64, &((*material).opacity), 16);
    memcpy(ub + 80, &((*material).c), 32);
    memcpy(rb + 112, &((*material).r), 16);
    return true;
}

bool SGXVesiclesShader::isOpaque() const {
    return false;
}

void SGXVesiclesShader::updateGraphicsPipelineState(RenderState &, GraphicsPipelineState *ps, QSGMaterial *, QSGMaterial *){
    (*ps).cullMode = QSGMaterialShader::GraphicsPipelineState::CullNone;
    (*ps).blendEnable = true;
}
