#include "sgxrendercutevesiclesshader.h"
#include "sgxrendercutevesiclesmaterial.h"
#include <QSGMaterialShader>
#include <QSGMaterial>
#include <QMatrix4x4>
#include <cstring>
#include <cstddef>
#include <span>

SGXRenderCuteVesiclesShader::SGXRenderCuteVesiclesShader(){
    setShaderFileName(QSGMaterialShader::VertexStage, ":/SGEXTN/cutevesicles/cutevesicles.vert.qsb");
    setShaderFileName(QSGMaterialShader::FragmentStage, ":/SGEXTN/cutevesicles/cutevesicles.frag.qsb");
}

bool SGXRenderCuteVesiclesShader::updateUniformData(RenderState &state, QSGMaterial *newMaterial, QSGMaterial */*unused*/){
    SGXRenderCuteVesiclesMaterial* mat = static_cast<SGXRenderCuteVesiclesMaterial*>(newMaterial); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
    char* uniformBuffer = (*state.uniformData()).data();
    const std::span<char> ubspan(uniformBuffer, 1712);
    QMatrix4x4 builtinMatrix = state.projectionMatrix();
    float builtinOpacity = state.opacity();
    memcpy(ubspan.data(), &builtinMatrix, 64);
    memcpy(ubspan.data() + 64, &builtinOpacity, 4);
    memcpy(ubspan.data() + 68, &((*mat).x), 4);
    memcpy(ubspan.data() + 72, &((*mat).y), 4);
    memcpy(ubspan.data() + 76, &((*mat).w), 4);
    memcpy(ubspan.data() + 80, &((*mat).h), 4);
    memcpy(ubspan.data() + 84, &((*mat).s), 4);
    float membraneR = (*mat).membraneColour.getRedAsFloat();
    float membraneG = (*mat).membraneColour.getGreenAsFloat();
    float membraneB = (*mat).membraneColour.getBlueAsFloat();
    float contentsR = (*mat).contentsColour.getRedAsFloat();
    float contentsG = (*mat).contentsColour.getGreenAsFloat();
    float contentsB = (*mat).contentsColour.getBlueAsFloat();
    memcpy(ubspan.data() + 88, &membraneR, 4);
    memcpy(ubspan.data() + 92, &membraneG, 4);
    memcpy(ubspan.data() + 96, &membraneB, 4);
    memcpy(ubspan.data() + 100, &contentsR, 4);
    memcpy(ubspan.data() + 104, &contentsG, 4);
    memcpy(ubspan.data() + 108, &contentsB, 4);
    memcpy(ubspan.data() + 112, &((*mat).centerTransparency), 4);
    memcpy(ubspan.data() + 116, &((*mat).edgeTransparency), 4);
    memcpy(ubspan.data() + 120, &((*mat).membraneTransparency), 4);
    memcpy(ubspan.data() + 124, &((*mat).membraneThickness), 4);
    for(int i=0; i<10; i++){
        memcpy(ubspan.data() + static_cast<ptrdiff_t>(128 + 16*i), &((*mat).center.at(i).x), 4);
        memcpy(ubspan.data() + static_cast<ptrdiff_t>(132 + 16*i), &((*mat).center.at(i).y), 4);
    }
    for(int i=0; i<10; i++){
        float offsetRadius = 0.0f;
        for(int j=0; j<8; j++){
            offsetRadius = (*mat).radius.at(i) + (*mat).radiusOffset.at(i).at(j) * (*mat).radius.at(i);
            memcpy(ubspan.data() + static_cast<ptrdiff_t>(288 + 144 * i + 16 * j), &offsetRadius, 4);
        }
        offsetRadius = (*mat).radius.at(i) + (*mat).radiusOffset.at(i)[0] * (*mat).radius.at(i);
        memcpy(ubspan.data() + static_cast<ptrdiff_t>(416 + 144 * i), &offsetRadius, 4);
    }
    return true;
}
