#ifndef SGWBACKGROUND_H
#define SGWBACKGROUND_H

#include <qtmetamacros.h>
#include "sgwwidget.h"
#include "../../primitives/sgxcolourrgba.h"

class SGWBackground : public SGWWidget
{
    Q_OBJECT
public:
    SGWBackground() = delete;
    [[nodiscard]] int getThemeColour(bool* isUsing) const;
    void setThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getColour(bool* isUsing) const;
    void setColour(SGXColourRGBA colour);
    void syncQuickProperties();
    static void enable(SGWBackground*& thisPointer, SGWBackground* (*initFunction)(), void (*resetFunction)());
    static void disable(SGWBackground*& thisPointer);
protected:
    SGWBackground(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int themeColour);
    bool usingTheme;
    int themeColour;
    SGXColourRGBA colour = {};
};

#endif // SGWBACKGROUND_H
