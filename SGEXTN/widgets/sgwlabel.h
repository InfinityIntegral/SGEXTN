#ifndef SGWLABEL_H
#define SGWLABEL_H

#include <qtmetamacros.h>
#include "sgwwidget.h"
#include "../primitives/sgxcolourrgba.h"
#include <QString>
#include "sgwhorizontalalignment.h"
#include "sgwverticalalignment.h"

class SGWLabel : public SGWWidget
{
    Q_OBJECT
public:
    SGWLabel(SGWWidget* parent, const QString& s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, SGWHorizontalAlignment::Flag horizontalAlignment, SGWVerticalAlignment::Flag verticalAlignment, const QString& font);
    static QString textFont;
    static QString iconsFont;
    void syncQuickProperties();
    [[nodiscard]] float getF1() const;
    void setF1(float f1);
    [[nodiscard]] float getF0() const;
    void setF0(float f0);
    [[nodiscard]] QString getTextAsString() const;
    [[nodiscard]] int getTextAsInt(bool* isValid, int minimum, int maximum) const;
    [[nodiscard]] float getTextAsFloat(bool* isValid, float minimum, float maximum) const;
    void setTextFromString(const QString& text);
    void setTextFromInt(int x);
    void setTextFromFloat(float x);
    [[nodiscard]] QString getFont() const;
    void setFont(const QString& font);
    [[nodiscard]] SGWHorizontalAlignment::Flag getHorizontalAlignment() const;
    void setHorizontalAlignment(SGWHorizontalAlignment::Flag alignment);
    [[nodiscard]] SGWVerticalAlignment::Flag getVerticalAlignment() const;
    void setVerticalAlignment(SGWVerticalAlignment::Flag alignment);
    [[nodiscard]] int getBackgroundThemeColour(bool* isUsing) const;
    void setBackgroundThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getBackgroundColour(bool* isUsing) const;
    void setBackgroundColour(SGXColourRGBA colour);
    [[nodiscard]] int getForegroundThemeColour(bool* isUsing) const;
    void setForegroundThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getForegroundColour(bool* isUsing) const;
    void setForegroundColour(SGXColourRGBA colour);
protected:
    float f1;
    float f0;
    QString text;
    QString font;
    SGWHorizontalAlignment::Flag horizontalAlignment;
    SGWVerticalAlignment::Flag verticalAlignment;
    bool usingTheme;
    int backgroundThemeColour;
    SGXColourRGBA backgroundColour = {};
    int foregroundThemeColour;
    SGXColourRGBA foregroundColour = {};
};

#endif // SGWLABEL_H
