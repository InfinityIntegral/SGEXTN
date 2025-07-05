#ifndef SGXRENDERCUTEVESICLESSHADER_H
#define SGXRENDERCUTEVESICLESSHADER_H

#include <QSGMaterialShader>

class SGXRenderCuteVesiclesShader : public QSGMaterialShader
{
public:
    SGXRenderCuteVesiclesShader(); // create instance of shader
    bool updateUniformData(RenderState& state, QSGMaterial* newMaterial, QSGMaterial* /*unused*/) override; // update animation data including screen size and vesicle properties
};

#endif // SGXRENDERCUTEVESICLESSHADER_H
