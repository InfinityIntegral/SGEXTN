#ifndef SGXRENDERCUTEVESICLESSHADER_H
#define SGXRENDERCUTEVESICLESSHADER_H

#include <QSGMaterialShader>

class SGXRenderCuteVesiclesShader : public QSGMaterialShader
{
public:
    SGXRenderCuteVesiclesShader(); // create instance of shader
    bool updateUniformData(RenderState& state, QSGMaterial* newMaterial, QSGMaterial* /*unused*/) override; // update animation data including screen size and vesicle properties
    bool updateGraphicsPipelineState(RenderState& /*unused*/, GraphicsPipelineState* ps, QSGMaterial* /*unused*/, QSGMaterial* /*unused*/) override; // update graphics pipeline to disable unnecessary effects
};

#endif // SGXRENDERCUTEVESICLESSHADER_H
