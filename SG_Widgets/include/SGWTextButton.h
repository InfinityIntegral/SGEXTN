#ifndef SGWTEXTBUTTON_H
#define SGWTEXTBUTTON_H

#include <SGWButton.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SGXString;
class SGWWidget;
class SG_WIDGETS_DLL SGWTextButton : public SGWButton
{
public:
    SGWTextButton(SGWWidget* parent, const SGXString& s, void (*attachedFunction)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
};

#endif // SGWTEXTBUTTON_H
