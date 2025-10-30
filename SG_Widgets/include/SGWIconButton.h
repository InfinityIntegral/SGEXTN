#ifndef SGWICONBUTTON_H
#define SGWICONBUTTON_H

#include <SGWButton.h>
#include <SGXChar.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SGWWidget;
class SG_WIDGETS_DLL SGWIconButton : public SGWButton
{
public:
    SGWIconButton(SGWWidget* parent, SGXChar s, void (*attachedFunction)(), float x1, float x0, float y1, float y0, float w1, float w0);
    [[nodiscard]] SGXChar getChar() const;
    void setChar(SGXChar c);
protected:
    SGXChar textChar = {};
};

#endif // SGWICONBUTTON_H
