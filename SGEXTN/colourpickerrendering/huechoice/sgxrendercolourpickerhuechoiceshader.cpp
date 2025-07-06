#include "sgxrendercolourpickerhuechoiceshader.h"
#include "sgxrendercolourpickerhuechoicematerial.h"
#include <span>
#include <QSGMaterialShader>
#include <QSGMaterial>
#include <QMatrix4x4>
#include <cstring>

SGXRenderColourPickerHueChoiceShader::SGXRenderColourPickerHueChoiceShader(){
    setShaderFileName(QSGMaterialShader::VertexStage, ":/SGEXTN/colourpickerrendering/huechoice/huechoice.vert.qsb");
    setShaderFileName(QSGMaterialShader::FragmentStage, ":/SGEXTN/colourpickerrendering/huechoice/huechoice.frag.qsb");
}

bool SGXRenderColourPickerHueChoiceShader::updateUniformData(RenderState &state, QSGMaterial *newMaterial, QSGMaterial */*unused*/){
    SGXRenderColourPickerHueChoiceMaterial* mat = static_cast<SGXRenderColourPickerHueChoiceMaterial*>(newMaterial); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
    char* uniformBuffer = (*state.uniformData()).data();
    const std::span<char> ubspan(uniformBuffer, 88);
    QMatrix4x4 builtinMatrix = state.projectionMatrix();
    float builtinOpacity = state.opacity();
    memcpy(ubspan.data(), &builtinMatrix, 64);
    memcpy(ubspan.data() + 64, &builtinOpacity, 4);
    memcpy(ubspan.data() + 68, &((*mat).x), 4);
    memcpy(ubspan.data() + 72, &((*mat).y), 4);
    memcpy(ubspan.data() + 76, &((*mat).w), 4);
    memcpy(ubspan.data() + 80, &((*mat).h), 4);
    memcpy(ubspan.data() + 84, &((*mat).selectedHue), 4);
    return true;
}
