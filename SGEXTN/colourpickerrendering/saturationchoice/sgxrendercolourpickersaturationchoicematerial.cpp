#include "sgxrendercolourpickersaturationchoicematerial.h"
#include "sgxrendercolourpickersaturationchoiceshader.h"
#include <QSGRendererInterface>
#include <QSGMaterialShader>
#include <qsgmaterialtype.h>
#include <QSGMaterial>
#include <cstdint>

SGXRenderColourPickerSaturationChoiceMaterial::SGXRenderColourPickerSaturationChoiceMaterial(){
    x = 0.0f;
    y = 0.0f;
    w = 0.0f;
    h = 0.0f;
    selectedHue = 0.0f;
    selectedSaturation = 0.0f;
}

QSGMaterialShader* SGXRenderColourPickerSaturationChoiceMaterial::createShader(QSGRendererInterface::RenderMode /*unused*/) const {
    return new SGXRenderColourPickerSaturationChoiceShader();
}

QSGMaterialType* SGXRenderColourPickerSaturationChoiceMaterial::type() const {
    static QSGMaterialType thisType;
    return &thisType;
}

int SGXRenderColourPickerSaturationChoiceMaterial::compare(const QSGMaterial *other) const {
    const uintptr_t thisType = reinterpret_cast<uintptr_t>((*this).type()); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    const uintptr_t otherType = reinterpret_cast<uintptr_t>((*other).type()); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    if(thisType < otherType){return -1;}
    if(thisType > otherType){return 1;}
    return 0;
    // return 0 is only safe because it is guaranteed that only 1 instance of the widget on which the material is attached to can exist. If more than 1 instance can exist, you must continue defining comparison based on size of parameters
}
