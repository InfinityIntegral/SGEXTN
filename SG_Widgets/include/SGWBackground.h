#ifndef SGWBACKGROUND_H
#define SGWBACKGROUND_H

#include <SGWWidget.h>
#include <SGXColourRGBA.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

template <typename T> class SGLStack;
class SG_WIDGETS_DLL SGWBackground : public SGWWidget
{
public:
    SGWBackground() = delete;
    [[nodiscard]] int getThemeColour(bool* isUsing) const;
    void setThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getColour(bool* isUsing) const;
    void setColour(SGXColourRGBA colour);
    void syncQuickProperties();
    static void enable(SGWBackground*& thisPointer, SGWBackground* (*initFunction)(), void (*resetFunction)());
    static void disable(SGWBackground*& thisPointer);
    static SGLStack<SGWBackground*>* activePages;
    static void terminate();
protected:
    SGWBackground(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int themeColour);
    bool usingTheme;
    int themeColour;
    SGXColourRGBA colour = {};
};

#endif // SGWBACKGROUND_H
