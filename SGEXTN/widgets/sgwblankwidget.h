#ifndef SGWBLANKWIDGET_H
#define SGWBLANKWIDGET_H

#include <qtmetamacros.h>
#include "sgwbackground.h"
#include "sgwwidget.h"

class SGWBlankWidget : public SGWBackground
{
    Q_OBJECT
public:
    SGWBlankWidget(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int themeColour, bool frequentlyUsed);
};

#endif // SGWBLANKWIDGET_H
