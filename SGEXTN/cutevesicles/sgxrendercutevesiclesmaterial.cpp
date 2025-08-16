#include "sgxrendercutevesiclesmaterial.h"
#include <QRandomGenerator>
#include "sgxrendercutevesiclesshader.h"
#include "../primitives/sgxvector2.h"
#include "../primitives/sgxcolourrgba.h"
#include <QSGMaterialShader>
#include <QSGRendererInterface>
#include <qsgmaterialtype.h>
#include <QSGMaterial>
#include <cstdint>
#include "../userDefinedClasses/sgucentralmanagement.h"

namespace{
inline float randomFloat(float min, float max){
    double x = (*QRandomGenerator::global()).generateDouble();
    x = static_cast<double>(min) + x * (static_cast<double>(max) - static_cast<double>(min));
    return static_cast<float>(x);
}
}

SGXRenderCuteVesiclesMaterial::SGXRenderCuteVesiclesMaterial(){
    x = 0.0f;
    y = 0.0f;
    w = 0.0f;
    h = 0.0f;
    s = 0.0f;
    membraneThickness = SGUCentralManagement::cuteVesiclesMembraneThickness;
    maxCenter = SGUCentralManagement::cuteVesiclesMaximumCenterDistance;
    center = {
        SGXVector2(randomFloat((-1.0f) * maxCenter, maxCenter), randomFloat((-1.0f) * maxCenter, maxCenter)),
        SGXVector2(randomFloat((-1.0f) * maxCenter, maxCenter), randomFloat((-1.0f) * maxCenter, maxCenter)),
        SGXVector2(randomFloat((-1.0f) * maxCenter, maxCenter), randomFloat((-1.0f) * maxCenter, maxCenter)),
        SGXVector2(randomFloat((-1.0f) * maxCenter, maxCenter), randomFloat((-1.0f) * maxCenter, maxCenter)),
        SGXVector2(randomFloat((-1.0f) * maxCenter, maxCenter), randomFloat((-1.0f) * maxCenter, maxCenter)),
        SGXVector2(randomFloat((-1.0f) * maxCenter, maxCenter), randomFloat((-1.0f) * maxCenter, maxCenter)),
        SGXVector2(randomFloat((-1.0f) * maxCenter, maxCenter), randomFloat((-1.0f) * maxCenter, maxCenter)),
        SGXVector2(randomFloat((-1.0f) * maxCenter, maxCenter), randomFloat((-1.0f) * maxCenter, maxCenter)),
        SGXVector2(randomFloat((-1.0f) * maxCenter, maxCenter), randomFloat((-1.0f) * maxCenter, maxCenter)),
        SGXVector2(randomFloat((-1.0f) * maxCenter, maxCenter), randomFloat((-1.0f) * maxCenter, maxCenter))
    };
    maxVelocityAllowed = SGUCentralManagement::cuteVesiclesMaximumVelocity;
    maxAccelerationPerSecond = SGUCentralManagement::cuteVesiclesMaximumAcceleration;
    velocity = {
        SGXVector2(randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed), randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed)),
        SGXVector2(randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed), randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed)),
        SGXVector2(randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed), randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed)),
        SGXVector2(randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed), randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed)),
        SGXVector2(randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed), randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed)),
        SGXVector2(randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed), randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed)),
        SGXVector2(randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed), randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed)),
        SGXVector2(randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed), randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed)),
        SGXVector2(randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed), randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed)),
        SGXVector2(randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed), randomFloat((-1.0f) * maxVelocityAllowed, maxVelocityAllowed))
    };
    minRadiusAllowed = SGUCentralManagement::cuteVesiclesMinimumRadius;
    maxRadiusAllowed = SGUCentralManagement::cuteVesiclesMaximumRadius;
    maxRadiusChangePerSecond = SGUCentralManagement::cuteVesiclesMaximumRadiusChange;
    radius = {
        randomFloat(minRadiusAllowed, maxRadiusAllowed),
        randomFloat(minRadiusAllowed, maxRadiusAllowed),
        randomFloat(minRadiusAllowed, maxRadiusAllowed),
        randomFloat(minRadiusAllowed, maxRadiusAllowed),
        randomFloat(minRadiusAllowed, maxRadiusAllowed),
        randomFloat(minRadiusAllowed, maxRadiusAllowed),
        randomFloat(minRadiusAllowed, maxRadiusAllowed),
        randomFloat(minRadiusAllowed, maxRadiusAllowed),
        randomFloat(minRadiusAllowed, maxRadiusAllowed),
        randomFloat(minRadiusAllowed, maxRadiusAllowed)
    };
    maxRadiusOffsetChangePerSecond = SGUCentralManagement::cuteVesiclesMaximumRadiusOffsetChange;
    maxRadiusOffsetAsRadiusPercentage = SGUCentralManagement::cuteVesiclesMaximumRadiusOffset;
    radiusOffset = {{
        {
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
        },
        {
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
        },
        {
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
        },
        {
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
        },
        {
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
        },
        {
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
        },
        {
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
        },
        {
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
        },
        {
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
        },
        {
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
            randomFloat((-1.0f) * maxRadiusOffsetAsRadiusPercentage, maxRadiusOffsetAsRadiusPercentage),
        },
    }};
    membraneColour = SGUCentralManagement::themeColour4;
    contentsColour = SGUCentralManagement::themeColour8;
    centerTransparency = SGUCentralManagement::cuteVesiclesCenterTransparency;
    edgeTransparency = SGUCentralManagement::cuteVesiclesEdgeTransparency;
    membraneTransparency = SGUCentralManagement::cuteVesiclesMembraneTransparency;
}

QSGMaterialShader* SGXRenderCuteVesiclesMaterial::createShader(QSGRendererInterface::RenderMode /*unused*/) const {
    return new SGXRenderCuteVesiclesShader();
}

QSGMaterialType* SGXRenderCuteVesiclesMaterial::type() const {
    static QSGMaterialType thisType;
    return &thisType;
}

int SGXRenderCuteVesiclesMaterial::compare(const QSGMaterial *other) const {
    const uintptr_t thisType = reinterpret_cast<uintptr_t>((*this).type());
    const uintptr_t otherType = reinterpret_cast<uintptr_t>((*other).type());
    if(thisType < otherType){return -1;}
    if(thisType > otherType){return 1;}
    return 0;
    // return 0 is only safe because it is guaranteed that only 1 instance of the widget on which the material is attached to can exist. If more than 1 instance can exist, you must continue defining comparison based on size of parameters
}
