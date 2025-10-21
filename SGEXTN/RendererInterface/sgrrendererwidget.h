#ifndef SGRRENDERERWIDGET_H
#define SGRRENDERERWIDGET_H

#include "../widgets/noninstantiable/sgwwidget.h"

class SGRBaseRenderer;
class SGRRendererWidget : public SGWWidget
{
public:
    SGRRendererWidget(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGRBaseRenderer* renderControl);
    SGRRendererWidget(const SGRRendererWidget&) = delete;
    SGRRendererWidget& operator=(const SGRRendererWidget&) = delete;
    SGRRendererWidget(SGRRendererWidget&&) = delete;
    SGRRendererWidget& operator=(SGRRendererWidget&&) = delete;
    ~SGRRendererWidget() override;
    SGRBaseRenderer* renderControl;
};

#endif // SGRRENDERERWIDGET_H
