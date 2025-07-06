#ifndef SGXRENDERCOLOURPICKERSATURATIONCHOICESHADER_H
#define SGXRENDERCOLOURPICKERSATURATIONCHOICESHADER_H

#include <QSGMaterialShader>

class SGXRenderColourPickerSaturationChoiceShader : public QSGMaterialShader
{
public:
    SGXRenderColourPickerSaturationChoiceShader();
    bool updateUniformData(RenderState &state, QSGMaterial *newMaterial, QSGMaterial */*unused*/) override;
};

#endif // SGXRENDERCOLOURPICKERSATURATIONCHOICESHADER_H
