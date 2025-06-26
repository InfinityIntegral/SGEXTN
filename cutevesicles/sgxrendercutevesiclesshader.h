#ifndef SGXRENDERCUTEVESICLESSHADER_H
#define SGXRENDERCUTEVESICLESSHADER_H

#include <QSGMaterialShader>

class SGXRenderCuteVesiclesShader : public QSGMaterialShader
{
public:
    SGXRenderCuteVesiclesShader();
    bool updateUniformData(RenderState& state, QSGMaterial* newMaterial, QSGMaterial*) override;
    bool updateGraphicsPipelineState(RenderState&, GraphicsPipelineState* ps, QSGMaterial*, QSGMaterial*) override;
    void updateSampledImage(RenderState&, int binding, QSGTexture** texture, QSGMaterial* newMaterial, QSGMaterial*) override;
};

#endif // SGXRENDERCUTEVESICLESSHADER_H
