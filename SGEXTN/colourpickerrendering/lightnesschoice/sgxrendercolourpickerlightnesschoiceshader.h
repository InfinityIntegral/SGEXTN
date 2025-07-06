#ifndef SGXRENDERCOLOURPICKERLIGHTNESSCHOICESHADER_H
#define SGXRENDERCOLOURPICKERLIGHTNESSCHOICESHADER_H

#include <QSGMaterialShader>

class SGXRenderColourPickerLightnessChoiceShader : public QSGMaterialShader
{
public:
    SGXRenderColourPickerLightnessChoiceShader();
    bool updateUniformData(RenderState &state, QSGMaterial *newMaterial, QSGMaterial */*unused*/) override;
};

#endif // SGXRENDERCOLOURPICKERLIGHTNESSCHOICESHADER_H
