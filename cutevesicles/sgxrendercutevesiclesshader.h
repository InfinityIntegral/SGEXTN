#ifndef SGXRENDERCUTEVESICLESSHADER_H
#define SGXRENDERCUTEVESICLESSHADER_H

#include <QSGMaterialShader>

class SGXRenderCuteVesiclesShader : public QSGMaterialShader
{
public:
    SGXRenderCuteVesiclesShader();
    bool updateUniformData(RenderState& state, QSGMaterial* newMaterial, QSGMaterial* /*unused*/) override;
    bool updateGraphicsPipelineState(RenderState& /*unused*/, GraphicsPipelineState* ps, QSGMaterial* /*unused*/, QSGMaterial* /*unused*/) override;
};

#endif // SGXRENDERCUTEVESICLESSHADER_H
