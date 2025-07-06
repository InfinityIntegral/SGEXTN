#include "sgxrendercolourpickersaturationchoiceshader.h"
#include "sgxrendercolourpickersaturationchoicematerial.h"
#include <span>
#include <QSGMaterialShader>
#include <QSGMaterial>
#include <QMatrix4x4>
#include <cstring>

SGXRenderColourPickerSaturationChoiceShader::SGXRenderColourPickerSaturationChoiceShader(){
    setShaderFileName(QSGMaterialShader::VertexStage, ":/SGEXTN/colourpickerrendering/saturationchoice/saturationchoice.vert.qsb");
    setShaderFileName(QSGMaterialShader::FragmentStage, ":/SGEXTN/colourpickerrendering/saturationchoice/saturationchoice.frag.qsb");
}

bool SGXRenderColourPickerSaturationChoiceShader::updateUniformData(RenderState &state, QSGMaterial *newMaterial, QSGMaterial */*unused*/){
    SGXRenderColourPickerSaturationChoiceMaterial* mat = static_cast<SGXRenderColourPickerSaturationChoiceMaterial*>(newMaterial); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
    char* uniformBuffer = (*state.uniformData()).data();
    const std::span<char> ubspan(uniformBuffer, 92);
    QMatrix4x4 builtinMatrix = state.projectionMatrix();
    float builtOpacity = state.opacity();
    memcpy(ubspan.data(), &builtinMatrix, 64);
    memcpy(ubspan.data() + 64, &builtOpacity, 4);
    memcpy(ubspan.data() + 68, &((*mat).x), 4);
    memcpy(ubspan.data() + 72, &((*mat).y), 4);
    memcpy(ubspan.data() + 76, &((*mat).w), 4);
    memcpy(ubspan.data() + 80, &((*mat).h), 4);
    memcpy(ubspan.data() + 84, &((*mat).selectedHue), 4);
    memcpy(ubspan.data() + 88, &((*mat).selectedSaturation), 4);
    return true;
}
