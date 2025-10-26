#ifndef SGRCOLOURPICKERSYNCER_H
#define SGRCOLOURPICKERSYNCER_H

#include "../sgrbasesyncer.h"

class SGRColourPickerSyncer : public SGRBaseSyncer
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
