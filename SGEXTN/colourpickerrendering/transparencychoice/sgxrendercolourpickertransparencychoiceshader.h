#ifndef SGXRENDERCOLOURPICKERTRANSPARENCYCHOICESHADER_H
#define SGXRENDERCOLOURPICKERTRANSPARENCYCHOICESHADER_H

#include <QSGMaterialShader>

class SGXRenderColourPickerTransparencyChoiceShader : public QSGMaterialShader
{
public:
    SGXRenderColourPickerTransparencyChoiceShader();
    bool updateUniformData(RenderState &state, QSGMaterial *newMaterial, QSGMaterial */*unused*/) override;
};

#endif // SGXRENDERCOLOURPICKERTRANSPARENCYCHOICESHADER_H
