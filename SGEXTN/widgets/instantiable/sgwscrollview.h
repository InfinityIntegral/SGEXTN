#ifndef SGWSCROLLVIEW_H
#define SGWSCROLLVIEW_H

#include "../noninstantiable/sgwbackground.h"
#include "../../primitives/sgxcolourrgba.h"
#include "../noninstantiable/sgwwidget.h"

class SGWScrollView : public SGWBackground
{
public:
    SGWScrollView(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float i1, float i0, float s1, float s0, int themeColour);
    void syncQuickProperties();
    [[nodiscard]] float getI1() const;
    void setI1(float i1);
    [[nodiscard]] float getI0() const;
    void setI0(float i0);
    [[nodiscard]] float getS1() const;
    void setS1(float s1);
    [[nodiscard]] float getS0() const;
    void setS0(float s0);
    [[nodiscard]] int getScrollbarBackgroundThemeColour(bool* isUsing) const;
    void setScrollbarBackgroundThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getScrollbarBackgroundColour(bool* isUsing) const;
    void setScrollbarBackgroundColour(SGXColourRGBA colour);
    [[nodiscard]] int getScrollbarForegroundThemeColour(bool* isUsing) const;
    void setScrollbarForegroundThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getScrollbarForegroundColour(bool* isUsing) const;
    void setScrollbarForegroundColour(SGXColourRGBA colour);
    [[nodiscard]] int getScrollbarBackgroundHoverThemeColour(bool* isUsing) const;
    void setScrollbarBackgroundHoverThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getScrollbarBackgroundHoverColour(bool* isUsing) const;
    void setScrollbarBackgroundHoverColour(SGXColourRGBA colour);
    [[nodiscard]] int getScrollbarForegroundHoverThemeColour(bool* isUsing) const;
    void setScrollbarForegroundHoverThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getScrollbarForegroundHoverColour(bool* isUsing) const;
    void setScrollbarForegroundHoverColour(SGXColourRGBA colour);
    [[nodiscard]] int getScrollbarBackgroundFocusThemeColour(bool* isUsing) const;
    void setScrollbarBackgroundFocusThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getScrollbarBackgroundFocusColour(bool* isUsing) const;
    void setScrollbarBackgroundFocusColour(SGXColourRGBA colour);
    [[nodiscard]] int getScrollbarForegroundFocusThemeColour(bool* isUsing) const;
    void setScrollbarForegroundFocusThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getScrollbarForegroundFocusColour(bool* isUsing) const;
    void setScrollbarForegroundFocusColour(SGXColourRGBA colour);
protected:
    float i1;
    float i0;
    float s1;
    float s0;
    int scrollbarBackgroundThemeColour;
    SGXColourRGBA scrollbarBackgroundColour = {};
    int scrollbarForegroundThemeColour;
    SGXColourRGBA scrollbarForegroundColour = {};
    int scrollbarBackgroundHoverThemeColour;
    SGXColourRGBA scrollbarBackgroundHoverColour = {};
    int scrollbarForegroundHoverThemeColour;
    SGXColourRGBA scrollbarForegroundHoverColour = {};
    int scrollbarBackgroundFocusThemeColour;
    SGXColourRGBA scrollbarBackgroundFocusColour = {};
    int scrollbarForegroundFocusThemeColour;
    SGXColourRGBA scrollbarForegroundFocusColour = {};
};

#endif // SGWSCROLLVIEW_H
