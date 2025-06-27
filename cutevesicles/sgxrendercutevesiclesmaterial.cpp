#include "sgxrendercutevesiclesmaterial.h"
#include <QRandomGenerator>
#include "sgxrendercutevesiclesshader.h"

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
    membraneThickness = 0.08f;
    maxCenter = 1.0f;
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
    maxVelocityAllowed = 0.05f;
    maxAccelerationPerSecond = 0.01f;
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
    minRadiusAllowed = 0.1f;
    maxRadiusAllowed = 0.35f;
    maxRadiusChangePerSecond = 0.03f;
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
    maxRadiusOffsetChangePerSecond = 0.05f;
    maxRadiusOffsetAsRadiusPercentage = 0.1f;
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
    membraneColour = SGXColourRGBA(255, 0, 200);
    contentsColour = SGXColourRGBA(255, 255, 255);
    centerTransparency = 0.1f;
    edgeTransparency = 0.05f;
    membraneTransparency = 0.2f;
    framesPerSecond = 10;
    setFlag(QSGMaterial::Blending);
}

QSGMaterialShader* SGXRenderCuteVesiclesMaterial::createShader(QSGRendererInterface::RenderMode) const {
    return new SGXRenderCuteVesiclesShader();
}

QSGMaterialType* SGXRenderCuteVesiclesMaterial::type() const {
    static QSGMaterialType thisType;
    return &thisType;
}

int SGXRenderCuteVesiclesMaterial::compare(const QSGMaterial *other) const {
    uintptr_t thisType = reinterpret_cast<uintptr_t>((*this).type());
    uintptr_t otherType = reinterpret_cast<uintptr_t>((*other).type());
    if(thisType < otherType){return -1;}
    if(thisType > otherType){return 1;}
    return 0;
    // return 0 is only safe because it is guaranteed that only 1 instance of the widget on which the material is attached to can exist. If more than 1 instance can exist, you must continue defining comparison based on size of parameters
}
