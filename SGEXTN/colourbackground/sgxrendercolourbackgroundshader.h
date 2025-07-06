#ifndef SGXRENDERCOLOURBACKGROUNDSHADER_H
#define SGXRENDERCOLOURBACKGROUNDSHADER_H

#include <QSGMaterialShader>

class SGXRenderColourBackgroundShader : public QSGMaterialShader
{
public:
    SGXRenderColourBackgroundShader();
    bool updateUniformData(RenderState &state, QSGMaterial *newMaterial, QSGMaterial */*unused*/) override;
};

#endif // SGXRENDERCOLOURBACKGROUNDSHADER_H
