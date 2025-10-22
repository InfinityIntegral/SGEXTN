#ifndef SGRRENDERERWIDGET_H
#define SGRRENDERERWIDGET_H

#include "../widgets/noninstantiable/sgwwidget.h"

class SGRBaseRenderer;
class SGRBaseSyncer;
class SGRRendererWidget : public SGWWidget
{
public:
    SGRRendererWidget(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGRBaseRenderer* renderControl, SGRBaseSyncer* syncControl);
    SGRRendererWidget(const SGRRendererWidget&) = delete;
    SGRRendererWidget& operator=(const SGRRendererWidget&) = delete;
    SGRRendererWidget(SGRRendererWidget&&) = delete;
    SGRRendererWidget& operator=(SGRRendererWidget&&) = delete;
    ~SGRRendererWidget() override;
    SGRBaseRenderer* renderControl;
    SGRBaseSyncer* syncControl;
};

#endif // SGRRENDERERWIDGET_H
