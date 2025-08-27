#ifndef SGXRENDERCOLOURPICKERTRANSPARENCYCHOICESGWIDGET_H
#define SGXRENDERCOLOURPICKERTRANSPARENCYCHOICESGWIDGET_H

#include "../../widgets/noninstantiable/sgwwidget.h"
#include "../../widgets/instantiable/sgwcustomrenderer.h"

class SGXRenderColourPickerTransparencyChoiceSGWidget : public SGWCustomRenderer
{
public:
    SGXRenderColourPickerTransparencyChoiceSGWidget(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    [[nodiscard]] float getSelectedHue() const;
    void setSelectedHue(float x);
    [[nodiscard]] float getSelectedSaturation() const;
    void setSelectedSaturation(float x);
    [[nodiscard]] float getSelectedLightness() const;
    void setSelectedLightness(float x);
    [[nodiscard]] float getSelectedTransparency() const;
    void setSelectedTransparency(float x);
protected:
    float selectedHue;
    float selectedSaturation;
    float selectedLightness;
    float selectedTransparency;
};

#endif // SGXRENDERCOLOURPICKERTRANSPARENCYCHOICESGWIDGET_H
