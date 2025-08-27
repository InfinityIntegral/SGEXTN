#ifndef SGWTEXTBUTTON_H
#define SGWTEXTBUTTON_H

#include "../noninstantiable/sgwbutton.h"
#include "../noninstantiable/sgwwidget.h"
#include <QString>

class SGWTextButton : public SGWButton
{
public:
    SGWTextButton(SGWWidget* parent, const QString& s, void (*attachedFunction)(SGWButton*), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
};

#endif // SGWTEXTBUTTON_H
