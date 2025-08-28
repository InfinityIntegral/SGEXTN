#ifndef SGWCOLOURPICKERWIDGET_H
#define SGWCOLOURPICKERWIDGET_H

#include "../noninstantiable/sgwwidget.h"
#include "../../primitives/sgxcolourrgba.h"

class QString;
class SGWWidgetQuickInterface;
class SGWColourPickerWidget : public SGWWidget
{
public:
    SGWColourPickerWidget(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGXColourRGBA defaultColour);
    SGWColourPickerWidget() = delete;
    SGWColourPickerWidget(const SGWColourPickerWidget&) = delete;
    SGWColourPickerWidget& operator=(const SGWColourPickerWidget&) = delete;
    SGWColourPickerWidget(SGWColourPickerWidget&&) = delete;
    SGWColourPickerWidget& operator=(SGWColourPickerWidget&&) = delete;
    ~SGWColourPickerWidget() override;
    void syncQuickProperties();
    [[nodiscard]] SGXColourRGBA getColour() const;
    void setColour(SGXColourRGBA colour);
    [[nodiscard]] int getBackgroundThemeColour(bool* isUsing) const;
    void setBackgroundThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getBackgroundColour(bool* isUsing) const;
    void setBackgroundColour(SGXColourRGBA colour);
    [[nodiscard]] int getBackgroundHoverThemeColour(bool* isUsing) const;
    void setBackgroundHoverThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getBackgroundHoverColour(bool* isUsing) const;
    void setBackgroundHoverColour(SGXColourRGBA colour);
    [[nodiscard]] int getBackgroundFocusThemeColour(bool* isUsing) const;
    void setBackgroundFocusThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getBackgroundFocusColour(bool* isUsing) const;
    void setBackgroundFocusColour(SGXColourRGBA colour);
    [[nodiscard]] float getE1() const;
    void setE1(float e1);
    [[nodiscard]] float getE0() const;
    void setE0(float e0);
    [[nodiscard]] void (*getAttachedFunction() const)(SGWColourPickerWidget*);
    void setAttachedFunction(void (*function)(SGWColourPickerWidget*));
    void eventReceived(const QString& s);
protected:
    float e1;
    float e0;
    SGXColourRGBA colour = {};
    bool usingTheme;
    int backgroundThemeColour;
    SGXColourRGBA backgroundColour = {};
    int backgroundHoverThemeColour;
    SGXColourRGBA backgroundHoverColour = {};
    int backgroundFocusThemeColour;
    SGXColourRGBA backgroundFocusColour = {};
    void (*attachedFunction)(SGWColourPickerWidget*);
    SGWWidgetQuickInterface* quickInterface;
};

#endif // SGWCOLOURPICKERWIDGET_H
