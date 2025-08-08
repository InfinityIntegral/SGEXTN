#ifndef SGXRENDERCOLOURBACKGROUNDSGWIDGET_H
#define SGXRENDERCOLOURBACKGROUNDSGWIDGET_H

#include <qtmetamacros.h>
#include "../widgets/sgwcustomrenderer.h"
#include "../widgets/sgwwidget.h"
#include "../primitives/sgxcolourrgba.h"

class SGXRenderColourBackgroundSGWidget : public SGWCustomRenderer
{
    Q_OBJECT
public:
    SGXRenderColourBackgroundSGWidget(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGXColourRGBA c);
    [[nodiscard]] SGXColourRGBA getColour() const;
    void setColour(SGXColourRGBA c);
protected:
    SGXColourRGBA colour = {};
};

#endif // SGXRENDERCOLOURBACKGROUNDSGWIDGET_H
