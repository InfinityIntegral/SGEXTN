#ifndef SGXRENDERCOLOURPICKERTRANSPARENCYCHOICEMATERIAL_H
#define SGXRENDERCOLOURPICKERTRANSPARENCYCHOICEMATERIAL_H

#include <QSGMaterial>
#include <QSGMaterialShader>
#include <QSGRendererInterface>
#include <qsgmaterialtype.h>

class SGXRenderColourPickerTransparencyChoiceMaterial : public QSGMaterial
{
public:
    SGXRenderColourPickerTransparencyChoiceMaterial();
    float x;
    float y;
    float w;
    float h;
    float selectedHue;
    float selectedSaturation;
    float selectedLightness;
    float selectedTransparency;
    [[nodiscard]] QSGMaterialShader* createShader(QSGRendererInterface::RenderMode /*unused*/) const override;
    [[nodiscard]] QSGMaterialType* type() const override;
    int compare(const QSGMaterial* other) const override;
};

#endif // SGXRENDERCOLOURPICKERTRANSPARENCYCHOICEMATERIAL_H
