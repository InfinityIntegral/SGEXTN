#include "sgxvesiclesmaterial.h"
#include "sgxvesiclesshader.h"
#include <cstdint>

SGXVesiclesMaterial::SGXVesiclesMaterial(SGXVector2 c, float r){
    (*this).c = c;
    (*this).r = r;
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
    if((*this).c.x < (*x).c.x){return -1;}
    if((*this).c.x > (*x).c.x){return 1;}
    if((*this).c.y < (*x).c.y){return -1;}
    if((*this).c.y > (*x).c.y){return -1;}
    if((*this).r < (*x).r){return -1;}
    if((*this).r > (*x).r){return 1;}
    return 0;
}
