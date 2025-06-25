#include "sgxvesiclesmaterial.h"

SGXVesiclesMaterial::SGXVesiclesMaterial(SGXVector2 c, float r){
    (*this).c = c;
    (*this).r = r;
}

QSGMaterialShader* SGXVesiclesMaterial::createShader(QSGRendererInterface::RenderMode renderMode) const {
    return new SGXVesiclesShader();
}

QSGMaterialType* SGXVesiclesMaterial::type() const {
    static QSGMaterialType thisType;
    return &thisType;
}

int SGXVesiclesMaterial::compare(const QSGMaterial *other) const {
    int thisType = (*(*this).type()).id();
    int otherType = (*(*other).type()).id();
    if(thisType < otherType){return -1;}
    if(thisType > otherType){return 1;}
    SGXVesiclesMaterial* x = static_cast<SGXVesiclesMaterial*>(other);
    if((*this).c.x < (*x).c.x){return -1;}
    if((*this).c.x > (*x).c.x){return 1;}
    if((*this).c.y < (*x).c.y){return -1;}
    if((*this).c.y > (*x).c.y){return -1;}
    if((*this).r < (*x).r){return -1;}
    if((*this).r > (*x).r){return 1;}
    return 0;
}
