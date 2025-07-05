#ifndef SGXRENDERCOLOURPICKERHUECHOICESHADER_H
#define SGXRENDERCOLOURPICKERHUECHOICESHADER_H

#include <QSGMaterialShader>

class SGXRenderColourPickerHueChoiceShader : public QSGMaterialShader
{
public:
    SGXRenderColourPickerHueChoiceShader();
    bool updateUniformData(RenderState &state, QSGMaterial *newMaterial, QSGMaterial */*unused*/) override;
};

#endif // SGXRENDERCOLOURPICKERHUECHOICESHADER_H
