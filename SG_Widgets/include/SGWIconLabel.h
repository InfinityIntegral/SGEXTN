#ifndef SGWICONLABEL_H
#define SGWICONLABEL_H

#include <SGWLabel.h>
#include <SGXChar.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SGWWidget;
class SG_WIDGETS_DLL SGWIconLabel : public SGWLabel
{
public:
    SGWIconLabel(SGWWidget* parent, SGXChar s, float x1, float x0, float y1, float y0, float w1, float w0);
    [[nodiscard]] SGXChar getChar() const;
    void setChar(SGXChar c);
protected:
    SGXChar textChar = {};
};

#endif // SGWICONLABEL_H
