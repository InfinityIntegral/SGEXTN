#ifndef SGXVESICLESSHADER_H
#define SGXVESICLESSHADER_H

#include <QSGMaterialShader>

class SGXVesiclesShader : public QSGMaterialShader
{
    Q_OBJECT
public:
    SGXVesiclesShader();
    bool updateUniformData(RenderState&, QSGMaterial* newMaterial, QSGMaterial*) override;
    bool isOpaque() const override;
    void updateGraphicsPipelineState(RenderState&, GraphicsPipelineState* ps, QSGMaterial*, QSGMaterial*) override;
};

#endif // SGXVESICLESSHADER_H
