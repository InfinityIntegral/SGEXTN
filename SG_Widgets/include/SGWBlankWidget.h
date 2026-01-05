#ifndef SGWBLANKWIDGET_H
#define SGWBLANKWIDGET_H

#include <SGWWidget.h>
#include <SGXColourRGBA.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SG_WIDGETS_DLL SGWBlankWidget : public SGWWidget
{
public:
    SGWBlankWidget(SGWWidget* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
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
