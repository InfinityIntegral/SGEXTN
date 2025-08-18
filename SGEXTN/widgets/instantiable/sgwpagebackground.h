#ifndef SGWPAGEBACKGROUND_H
#define SGWPAGEBACKGROUND_H

#include <qtmetamacros.h>
#include "../noninstantiable/sgwbackground.h"
#include "../noninstantiable/sgwwidget.h"

class SGWPageBackground : public SGWBackground
{
    Q_OBJECT
public:
    SGWPageBackground(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int themeColour);
};

#endif // SGWPAGEBACKGROUND_H
