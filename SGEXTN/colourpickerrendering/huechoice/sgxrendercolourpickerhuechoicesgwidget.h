#ifndef SGXRENDERCOLOURPICKERHUECHOICESGWIDGET_H
#define SGXRENDERCOLOURPICKERHUECHOICESGWIDGET_H

#include <qtmetamacros.h>
#include "../../widgets/sgwcustomrenderer.h"
#include "../../widgets/sgwwidget.h"

class SGXRenderColourPickerHueChoiceSGWidget : public SGWCustomRenderer
{
    Q_OBJECT
public:
    SGXRenderColourPickerHueChoiceSGWidget(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    [[nodiscard]] float getSelectedHue() const;
    void setSelectedHue(float x);
protected:
    float selectedHue;
};

#endif // SGXRENDERCOLOURPICKERHUECHOICESGWIDGET_H
