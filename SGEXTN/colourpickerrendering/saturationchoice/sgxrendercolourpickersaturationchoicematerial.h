#ifndef SGXRENDERCOLOURPICKERSATURATIONCHOICEMATERIAL_H
#define SGXRENDERCOLOURPICKERSATURATIONCHOICEMATERIAL_H

#include <QSGMaterial>
#include <QSGMaterialShader>
#include <QSGRendererInterface>
#include <qsgmaterialtype.h>

class SGXRenderColourPickerSaturationChoiceMaterial : public QSGMaterial
{
public:
    SGXRenderColourPickerSaturationChoiceMaterial();
    float x;
    float y;
    float w;
    float h;
    float selectedHue;
    float selectedSaturation;
    [[nodiscard]] QSGMaterialShader* createShader(QSGRendererInterface::RenderMode /*unused*/) const override;
    [[nodiscard]] QSGMaterialType* type() const override;
    int compare(const QSGMaterial* other) const override;
};

#endif // SGXRENDERCOLOURPICKERSATURATIONCHOICEMATERIAL_H
