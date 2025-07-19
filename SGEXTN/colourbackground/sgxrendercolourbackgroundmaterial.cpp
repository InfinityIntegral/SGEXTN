#include "sgxrendercolourbackgroundmaterial.h"
#include "sgxrendercolourbackgroundshader.h"
#include <QSGRendererInterface>
#include <QSGMaterialShader>
#include <qsgmaterialtype.h>
#include <QSGMaterial>
#include <cstdint>

SGXRenderColourBackgroundMaterial::SGXRenderColourBackgroundMaterial(){
    x = 0.0f;
    y = 0.0f;
    w = 0.0f;
    h = 0.0f;
}

QSGMaterialShader* SGXRenderColourBackgroundMaterial::createShader(QSGRendererInterface::RenderMode /*unused*/) const {
    return new SGXRenderColourBackgroundShader();
}

QSGMaterialType* SGXRenderColourBackgroundMaterial::type() const {
    static QSGMaterialType thisType;
    return &thisType;
}

int SGXRenderColourBackgroundMaterial::compare(const QSGMaterial *other) const {
    const uintptr_t thisType = reinterpret_cast<uintptr_t>((*this).type());
    const uintptr_t otherType = reinterpret_cast<uintptr_t>((*other).type());
    if(thisType < otherType){return -1;}
    if(thisType > otherType){return 1;}
    return 0;
    // return 0 is only safe because it is guaranteed that only 1 instance of the widget on which the material is attached to can exist. If more than 1 instance can exist, you must continue defining comparison based on size of parameters
}
