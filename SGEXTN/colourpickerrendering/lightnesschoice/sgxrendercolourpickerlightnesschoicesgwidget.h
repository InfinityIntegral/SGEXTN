#ifndef SGXRENDERCOLOURPICKERLIGHTNESSCHOICESGWIDGET_H
#define SGXRENDERCOLOURPICKERLIGHTNESSCHOICESGWIDGET_H

#include "../../widgets/noninstantiable/sgwwidget.h"
#include "../../widgets/instantiable/sgwcustomrenderer.h"

class SGXRenderColourPickerLightnessChoiceSGWidget : public SGWCustomRenderer
{
public:
    SGXRenderColourPickerLightnessChoiceSGWidget(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    [[nodiscard]] float getSelectedHue() const;
    void setSelectedHue(float x);
    [[nodiscard]] float getSelectedSaturation() const;
    void setSelectedSaturation(float x);
    [[nodiscard]] float getSelectedLightness() const;
    void setSelectedLightness(float x);
protected:
    float selectedHue;
    float selectedSaturation;
    float selectedLightness;
};

#endif // SGXRENDERCOLOURPICKERLIGHTNESSCHOICESGWIDGET_H
