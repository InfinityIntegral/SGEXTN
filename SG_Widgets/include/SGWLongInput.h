#ifndef SGWLONGINPUT_H
#define SGWLONGINPUT_H

#include <SGWInput.h>
#include <SGXColourRGBA.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SGWWidget;
class SG_WIDGETS_DLL SGWLongInput : public SGWInput
{
public:
    SGWLongInput(SGWWidget* parent, const SGXString& placeholder, void (*validationFunction)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, float s1, float s0);
    void syncQuickProperties();
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

#endif // SGWLONGINPUT_H
