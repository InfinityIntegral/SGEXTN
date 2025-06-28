#ifndef SGXRENDERCUTEVESICLESMATERIAL_H
#define SGXRENDERCUTEVESICLESMATERIAL_H

#include <QSGMaterial>
#include <array>
#include "../primitives/sgxvector2.h"
#include "../primitives/sgxcolourrgba.h"
#include <QSGMaterialShader>
#include <QSGRendererInterface>
#include <qsgmaterialtype.h>

class SGXRenderCuteVesiclesMaterial : public QSGMaterial // material for vesicle animations
{
public:
    SGXRenderCuteVesiclesMaterial(); // create new instance of material
    float x; // store x position of animation widget
    float y; // store y position of animation widget
    float w; // store width of animation widget
    float h; // store height of animation widget
    float s; // store maximum of width and height of animation widget
    float membraneThickness; // thickness of vesicle membrane in units, where a unit is half of the maximum of the width and the height of the animation widget
    std::array<SGXVector2, 10> center = {}; // positions of centers of vesicles in units, where a unit is half of the maximum of the width and the height of the animation widget
    float maxCenter; // maximum distance on both axis that a vesicle can be from the center in units, where a unit is half of the maximum of the width and the height of the animation widget
    std::array<SGXVector2, 10> velocity = {}; // velocity of vesicles in units per second, where a unit is half of the maximum of the width and the height of the animation widget
    float maxVelocityAllowed; // maximum possible velocity of vesicles in units per second, where a unit is half of the maximum of the width and the height of the animation widget
    float maxAccelerationPerSecond; // maximum possible acceleration of vesicles in units per second, where a unit is half of the maximum of the width and the height of the animation widget
    std::array<float, 10> radius = {}; // radii of vesicles in units, where a unit is half of the maximum of the width and the height of the animation widget
    float maxRadiusChangePerSecond; // maximum possible rate of change of vesicle radius in units per second, where a unit is half of the maximum of the width and the height of the animation widget
    float minRadiusAllowed; // minimum possible vesicle radius in units, where a unit is half of the maximum of the width and the height of the animation widget
    float maxRadiusAllowed; // maximum possible vesicle radius in units, where a unit is half of the maximum of the width and the height of the animation widget
    std::array<std::array<float, 8>, 10> radiusOffset = {}; // radius offset of vesicles as ratio to radius, the radius offset gives vesicles their squishy feel
    float maxRadiusOffsetChangePerSecond; // maximum possible change in vesicle radius offset per second as ratio to radius, the radius offset gives vesicles their squishy feel
    float maxRadiusOffsetAsRadiusPercentage; // maximum possible vesicle radius offset as ratio to radius, the radius offset gives vesicles their squishy feel
    SGXColourRGBA membraneColour = SGXColourRGBA(); // colour of vesicle membrane (phospholipid bilayer)
    SGXColourRGBA contentsColour = SGXColourRGBA(); // colour of vesicle contents
    float centerTransparency; // transparency of contents at center of vesicle
    float edgeTransparency; // transparency of contents at edge of vesicle
    float membraneTransparency; // transparency of vesicle membrane (phospholipid bilayer)
    [[nodiscard]] QSGMaterialShader* createShader(QSGRendererInterface::RenderMode /*unused*/) const override; // function to create instance of material shader
    [[nodiscard]] QSGMaterialType* type() const override; // function to get type index of this material
    int compare(const QSGMaterial *other) const override; // function to compare if this material instance is identical to another material instance for optimisation
};

#endif // SGXRENDERCUTEVESICLESMATERIAL_H
