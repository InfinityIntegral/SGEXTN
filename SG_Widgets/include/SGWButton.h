#ifndef SGWBUTTON_H
#define SGWBUTTON_H

#include <SGWWidget.h>
#include <SGXString.h>
#include <SGXColourRGBA.h>
#include <SGWHorizontalAlignment.h>
#include <SGWVerticalAlignment.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SGWWidgetQuickInterface;
class SG_WIDGETS_DLL SGWButton : public SGWWidget
{
public:
    SGWButton() = delete;
    SGWButton(const SGWButton&) = delete;
    SGWButton& operator=(const SGWButton&) = delete;
    SGWButton(SGWButton&&) = delete;
    SGWButton& operator=(SGWButton&&) = delete;
    ~SGWButton() override;
    void syncQuickProperties();
    [[nodiscard]] float getF1() const;
    void setF1(float f1);
    [[nodiscard]] float getF0() const;
    void setF0(float f0);
    [[nodiscard]] SGXString getTextAsString() const;
    [[nodiscard]] int getTextAsInt(bool* isValid, int minimum, int maximum) const;
    [[nodiscard]] float getTextAsFloat(bool* isValid, float minimum, float maximum) const;
    void setTextFromString(const SGXString& s);
    void setTextFromInt(int x);
    void setTextFromFloat(float x);
    [[nodiscard]] SGXString getFont() const;
    void setFont(const SGXString& font);
    [[nodiscard]] SGWHorizontalAlignment::Flag getHorizontalAlignment() const;
    void setHorizontalAlignment(SGWHorizontalAlignment::Flag alignment);
    [[nodiscard]] SGWVerticalAlignment::Flag getVerticalAlignment() const;
    void setVerticalAlignment(SGWVerticalAlignment::Flag alignment);
    [[nodiscard]] bool getSelected() const;
    void setSelected(bool selected);
    int attachedInt;
    SGXString attachedString;
    void (*clickFunction)();
    void (*pressFunction)();
    void (*releaseFunction)();
    void (*clickFunctionWithInt)(int);
    void (*pressFunctionWithInt)(int);
    void (*releaseFunctionWithInt)(int);
    void (*clickFunctionWithString)(const SGXString&);
    void (*pressFunctionWithString)(const SGXString&);
    void (*releaseFunctionWithString)(const SGXString&);
    void (*clickFunctionWithPointer)(SGWButton*);
    void (*pressFunctionWithPointer)(SGWButton*);
    void (*releaseFunctionWithPointer)(SGWButton*);
    [[nodiscard]] int getBackgroundThemeColour(bool* isUsing) const;
    void setBackgroundThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getBackgroundColour(bool* isUsing) const;
    void setBackgroundColour(SGXColourRGBA colour);
    [[nodiscard]] int getForegroundThemeColour(bool* isUsing) const;
    void setForegroundThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getForegroundColour(bool* isUsing) const;
    void setForegroundColour(SGXColourRGBA colour);
    [[nodiscard]] int getBackgroundHoverThemeColour(bool* isUsing) const;
    void setBackgroundHoverThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getBackgroundHoverColour(bool* isUsing) const;
    void setBackgroundHoverColour(SGXColourRGBA colour);
    [[nodiscard]] int getForegroundHoverThemeColour(bool* isUsing) const;
    void setForegroundHoverThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getForegroundHoverColour(bool* isUsing) const;
    void setForegroundHoverColour(SGXColourRGBA colour);
    [[nodiscard]] int getBackgroundFocusThemeColour(bool* isUsing) const;
    void setBackgroundFocusThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getBackgroundFocusColour(bool* isUsing) const;
    void setBackgroundFocusColour(SGXColourRGBA colour);
    [[nodiscard]] int getForegroundFocusThemeColour(bool* isUsing) const;
    void setForegroundFocusThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getForegroundFocusColour(bool* isUsing) const;
    void setForegroundFocusColour(SGXColourRGBA colour);
    [[nodiscard]] int getBackgroundSelectedThemeColour(bool* isUsing) const;
    void setBackgroundSelectedThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getBackgroundSelectedColour(bool* isUsing) const;
    void setBackgroundSelectedColour(SGXColourRGBA colour);
    [[nodiscard]] int getForegroundSelectedThemeColour(bool* isUsing) const;
    void setForegroundSelectedThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getForegroundSelectedColour(bool* isUsing) const;
    void setForegroundSelectedColour(SGXColourRGBA colour);
    [[nodiscard]] int getBackgroundHoverSelectedThemeColour(bool* isUsing) const;
    void setBackgroundHoverSelectedThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getBackgroundHoverSelectedColour(bool* isUsing) const;
    void setBackgroundHoverSelectedColour(SGXColourRGBA colour);
    [[nodiscard]] int getForegroundHoverSelectedThemeColour(bool* isUsing) const;
    void setForegroundHoverSelectedThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getForegroundHoverSelectedColour(bool* isUsing) const;
    void setForegroundHoverSelectedColour(SGXColourRGBA colour);
    [[nodiscard]] int getBackgroundFocusSelectedThemeColour(bool* isUsing) const;
    void setBackgroundFocusSelectedThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getBackgroundFocusSelectedColour(bool* isUsing) const;
    void setBackgroundFocusSelectedColour(SGXColourRGBA colour);
    [[nodiscard]] int getForegroundFocusSelectedThemeColour(bool* isUsing) const;
    void setForegroundFocusSelectedThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getForegroundFocusSelectedColour(bool* isUsing) const;
    void setForegroundFocusSelectedColour(SGXColourRGBA colour);
    void eventReceived(const SGXString& s);
protected:
    SGWButton(SGWWidget* parent, const SGXString& s, void (*attachedFunction)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, const SGXString& font);
    float f1;
    float f0;
    SGXString text;
    SGXString font;
    SGWHorizontalAlignment::Flag horizontalAlignment;
    SGWVerticalAlignment::Flag verticalAlignment;
    bool selected;
    bool usingTheme;
    int backgroundThemeColour;
    SGXColourRGBA backgroundColour = {};
    int foregroundThemeColour;
    SGXColourRGBA foregroundColour = {};
    int backgroundHoverThemeColour;
    SGXColourRGBA backgroundHoverColour = {};
    int foregroundHoverThemeColour;
    SGXColourRGBA foregroundHoverColour = {};
    int backgroundFocusThemeColour;
    SGXColourRGBA backgroundFocusColour = {};
    int foregroundFocusThemeColour;
    SGXColourRGBA foregroundFocusColour = {};
    int backgroundSelectedThemeColour;
    SGXColourRGBA backgroundSelectedColour = {};
    int foregroundSelectedThemeColour;
    SGXColourRGBA foregroundSelectedColour = {};
    int backgroundHoverSelectedThemeColour;
    SGXColourRGBA backgroundHoverSelectedColour = {};
    int foregroundHoverSelectedThemeColour;
    SGXColourRGBA foregroundHoverSelectedColour = {};
    int backgroundFocusSelectedThemeColour;
    SGXColourRGBA backgroundFocusSelectedColour = {};
    int foregroundFocusSelectedThemeColour;
    SGXColourRGBA foregroundFocusSelectedColour = {};
    SGWWidgetQuickInterface* quickInterface;
};

#endif // SGWBUTTON_H
