#include "sgrcolourpickersyncer.h"
#include "../sgrbaserenderer.h"
#include "sgrcolourpickerrenderer.h"

SGRColourPickerSyncer::SGRColourPickerSyncer(){
    (*this).hue = 0.0f;
    (*this).saturation = 0.0f;
    (*this).lightness = 0.0f;
    (*this).transparency = 0.0f;
}

void SGRColourPickerSyncer::sync(SGRBaseRenderer *renderControl){
    SGRColourPickerRenderer* rc = static_cast<SGRColourPickerRenderer*>(renderControl);
    (*rc).hue = hue;
    (*rc).saturation = saturation;
    (*rc).lightness = lightness;
    (*rc).transparency = transparency;
}
