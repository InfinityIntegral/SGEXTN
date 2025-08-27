#ifndef SGWBLANKWIDGET_H
#define SGWBLANKWIDGET_H

#include "../noninstantiable/sgwwidget.h"
#include "../../primitives/sgxcolourrgba.h"

class SGWBlankWidget : public SGWWidget
{
public:
    SGWBlankWidget(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int themeColour);
    [[nodiscard]] int getThemeColour(bool* isUsing) const;
    void setThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getColour(bool* isUsing) const;
    void setColour(SGXColourRGBA colour);
    void syncQuickProperties();
protected:
    bool usingTheme;
    int themeColour;
    SGXColourRGBA colour = {};
};

#endif // SGWBLANKWIDGET_H
