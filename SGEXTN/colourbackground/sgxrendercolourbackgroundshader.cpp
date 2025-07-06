#include "sgxrendercolourbackgroundshader.h"
#include "sgxrendercolourbackgroundmaterial.h"
#include <span>
#include <QSGMaterialShader>
#include <QSGMaterial>
#include <QMatrix4x4>
#include <cstring>

SGXRenderColourBackgroundShader::SGXRenderColourBackgroundShader(){
    setShaderFileName(QSGMaterialShader::VertexStage, ":/SGEXTN/colourbackground/colourbackground.vert.qsb");
    setShaderFileName(QSGMaterialShader::FragmentStage, ":/SGEXTN/colourbackground/colourbackground.frag.qsb");
}

bool SGXRenderColourBackgroundShader::updateUniformData(RenderState &state, QSGMaterial *newMaterial, QSGMaterial */*unused*/){
    SGXRenderColourBackgroundMaterial* mat = static_cast<SGXRenderColourBackgroundMaterial*>(newMaterial); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
    char* uniformBuffer = (*state.uniformData()).data();
    const std::span<char> ubspan(uniformBuffer, 84);
    QMatrix4x4 builtinMatrix = state.projectionMatrix();
    float builtOpacity = state.opacity();
    memcpy(ubspan.data(), &builtinMatrix, 64);
    memcpy(ubspan.data() + 64, &builtOpacity, 4);
    memcpy(ubspan.data() + 68, &((*mat).x), 4);
    memcpy(ubspan.data() + 72, &((*mat).y), 4);
    memcpy(ubspan.data() + 76, &((*mat).w), 4);
    memcpy(ubspan.data() + 80, &((*mat).h), 4);
    return true;
}
