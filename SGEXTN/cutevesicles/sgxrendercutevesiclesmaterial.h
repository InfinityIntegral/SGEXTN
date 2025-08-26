#ifndef SGXRENDERCUTEVESICLESMATERIAL_H
#define SGXRENDERCUTEVESICLESMATERIAL_H

#include <QSGMaterial>
#include <array>
#include "../primitives/sgxvector2.h"
#include "../primitives/sgxcolourrgba.h"
#include <QSGMaterialShader>
#include <QSGRendererInterface>
#include <qsgmaterialtype.h>

class SGXRenderCuteVesiclesMaterial : public QSGMaterial
{
public:
    SGXRenderCuteVesiclesMaterial();
    float x;
    float y;
    float w;
    float h;
    float s;
    float membraneThickness;
    std::array<SGXVector2, 10> center = {};
    float maxCenter;
    std::array<SGXVector2, 10> velocity = {};
    float maxVelocityAllowed;
    float maxAccelerationPerSecond;
    std::array<float, 10> radius = {};
    float maxRadiusChangePerSecond;
    float minRadiusAllowed;
    float maxRadiusAllowed;
    std::array<std::array<float, 8>, 10> radiusOffset = {};
    float maxRadiusOffsetChangePerSecond;
    float maxRadiusOffsetAsRadiusPercentage;
    SGXColourRGBA membraneColour = SGXColourRGBA();
    SGXColourRGBA contentsColour = SGXColourRGBA();
    float centerTransparency;
    float edgeTransparency;
    float membraneTransparency;
    [[nodiscard]] QSGMaterialShader* createShader(QSGRendererInterface::RenderMode /*unused*/) const override;
    [[nodiscard]] QSGMaterialType* type() const override;
    int compare(const QSGMaterial *other) const override;
};

#endif // SGXRENDERCUTEVESICLESMATERIAL_H
