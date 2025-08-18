#ifndef SGXRENDERCOLOURPICKERSATURATIONCHOICESGWIDGET_H
#define SGXRENDERCOLOURPICKERSATURATIONCHOICESGWIDGET_H

#include <qtmetamacros.h>
#include "../../widgets/noninstantiable/sgwwidget.h"
#include "../../widgets/instantiable/sgwcustomrenderer.h"

class SGXRenderColourPickerSaturationChoiceSGWidget : public SGWCustomRenderer
{
    Q_OBJECT
public:
    SGXRenderColourPickerSaturationChoiceSGWidget(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    [[nodiscard]] float getSelectedHue() const;
    void setSelectedHue(float x);
    [[nodiscard]] float getSelectedSaturation() const;
    void setSelectedSaturation(float x);
protected:
    float selectedHue;
    float selectedSaturation;
};

#endif // SGXRENDERCOLOURPICKERSATURATIONCHOICESGWIDGET_H
