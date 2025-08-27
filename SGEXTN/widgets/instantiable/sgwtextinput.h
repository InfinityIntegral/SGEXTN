#ifndef SGWTEXTINPUT_H
#define SGWTEXTINPUT_H

#include "../noninstantiable/sgwinput.h"
#include "../noninstantiable/sgwwidget.h"

class SGWTextInput : public SGWInput
{
public:
    SGWTextInput(SGWWidget* parent, void (*validationFunction)(SGWInput*), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
};

#endif // SGWTEXTINPUT_H
