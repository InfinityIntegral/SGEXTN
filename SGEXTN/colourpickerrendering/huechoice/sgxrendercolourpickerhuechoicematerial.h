#ifndef SGXRENDERCOLOURPICKERHUECHOICEMATERIAL_H
#define SGXRENDERCOLOURPICKERHUECHOICEMATERIAL_H

#include <QSGMaterial>
#include <QSGMaterialShader>
#include <QSGRendererInterface>
#include <qsgmaterialtype.h>

class SGXRenderColourPickerHueChoiceMaterial : public QSGMaterial
{
public:
    SGXRenderColourPickerHueChoiceMaterial();
    float x;
    float y;
    float w;
    float h;
    float selectedHue;
    [[nodiscard]] QSGMaterialShader* createShader(QSGRendererInterface::RenderMode /*unused*/) const override;
    [[nodiscard]] QSGMaterialType* type() const override;
    int compare(const QSGMaterial* other) const override;
};

#endif // SGXRENDERCOLOURPICKERHUECHOICEMATERIAL_H
