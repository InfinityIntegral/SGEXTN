#ifndef SGXVESICLESSHADER_H
#define SGXVESICLESSHADER_H

#include <QSGMaterialShader>

class SGXVesiclesShader : public QSGMaterialShader
{
public:
    SGXVesiclesShader();
    bool updateUniformData(RenderState& udh, QSGMaterial* newMaterial, QSGMaterial*) override;
    bool updateGraphicsPipelineState(RenderState&, GraphicsPipelineState* ps, QSGMaterial*, QSGMaterial*) override;
};

#endif // SGXVESICLESSHADER_H
