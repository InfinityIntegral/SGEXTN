#ifndef SGRCOLOURPICKERSYNCER_H
#define SGRCOLOURPICKERSYNCER_H

#include <SGRBaseSyncer.h>

#include <private_api_RI/SG_Build_RI.h>

class SG_RI_DLL SGRColourPickerSyncer : public SGRBaseSyncer
{
public:
    SGRColourPickerSyncer();
    float hue;
    float saturation;
    float lightness;
    float transparency;
    void sync(SGRBaseRenderer* renderControl) override;
};

#endif // SGRCOLOURPICKERSYNCER_H
