#include "sgxvesiclesmaterial.h"
#include "sgxvesiclesshader.h"
#include <cstdint>

SGXVesiclesMaterial::SGXVesiclesMaterial(float cx, float cy, float r, float x, float y, float w, float h, float s){
    (*this).cx = cx;
    (*this).cy = cy;
    (*this).r = r;
    (*this).x = x;
    (*this).y = y;
    (*this).w = w;
    (*this).h = h;
    (*this).s = s;
    (*this).setFlag(QSGMaterial::Blending);
}

QSGMaterialShader* SGXVesiclesMaterial::createShader(QSGRendererInterface::RenderMode) const {
    return new SGXVesiclesShader();
}

QSGMaterialType* SGXVesiclesMaterial::type() const {
    static QSGMaterialType thisType;
    return &thisType;
}

int SGXVesiclesMaterial::compare(const QSGMaterial *other) const {
    uintptr_t thisType = reinterpret_cast<uintptr_t>((*this).type());
    uintptr_t otherType = reinterpret_cast<uintptr_t>((*other).type());
    if(thisType < otherType){return -1;}
    if(thisType > otherType){return 1;}
    const SGXVesiclesMaterial* x = static_cast<const SGXVesiclesMaterial*>(other);
    if((*this).cx < (*x).cx){return -1;}
    if((*this).cx > (*x).cx){return 1;}
    if((*this).cy < (*x).cy){return -1;}
    if((*this).cy > (*x).cy){return -1;}
    if((*this).r < (*x).r){return -1;}
    if((*this).r > (*x).r){return 1;}
    return 0;
}
