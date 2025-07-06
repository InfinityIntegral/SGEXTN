#ifndef SGXRENDERCOLOURBACKGROUNDMATERIAL_H
#define SGXRENDERCOLOURBACKGROUNDMATERIAL_H

#include <QSGMaterial>
#include <QSGMaterialShader>
#include <QSGRendererInterface>
#include <qsgmaterialtype.h>

class SGXRenderColourBackgroundMaterial : public QSGMaterial
{
public:
    SGXRenderColourBackgroundMaterial();
    float x;
    float y;
    float w;
    float h;
    [[nodiscard]] QSGMaterialShader* createShader(QSGRendererInterface::RenderMode /*unused*/) const override;
    [[nodiscard]] QSGMaterialType* type() const override;
    int compare(const QSGMaterial* other) const override;
};

#endif // SGXRENDERCOLOURBACKGROUNDMATERIAL_H
