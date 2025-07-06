#ifndef SGXRENDERCOLOURPICKERLIGHTNESSCHOICEMATERIAL_H
#define SGXRENDERCOLOURPICKERLIGHTNESSCHOICEMATERIAL_H

#include <QSGMaterial>
#include <QSGMaterialShader>
#include <QSGRendererInterface>
#include <qsgmaterialtype.h>

class SGXRenderColourPickerLightnessChoiceMaterial : public QSGMaterial
{
public:
    SGXRenderColourPickerLightnessChoiceMaterial();
    float x;
    float y;
    float w;
    float h;
    float selectedHue;
    float selectedSaturation;
    float selectedLightness;
    [[nodiscard]] QSGMaterialShader* createShader(QSGRendererInterface::RenderMode /*unused*/) const override;
    [[nodiscard]] QSGMaterialType* type() const override;
    int compare(const QSGMaterial* other) const override;
};

#endif // SGXRENDERCOLOURPICKERLIGHTNESSCHOICEMATERIAL_H
