#ifndef SGWTEXTINPUT_H
#define SGWTEXTINPUT_H

#include <SGWInput.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SGWWidget;
class SG_WIDGETS_DLL SGWTextInput : public SGWInput
{
public:
    SGWTextInput(SGWWidget* parent, const SGXString& placeholder, void (*validationFunction)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
};

#endif // SGWTEXTINPUT_H
