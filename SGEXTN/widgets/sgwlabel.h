#ifndef SGWLABEL_H
#define SGWLABEL_H

#include <qtmetamacros.h>
#include "sgwwidget.h"
#include "../primitives/sgxcolourrgba.h"
#include <QString>
#include <qnamespace.h>

class SGWLabel : public SGWWidget
{
    Q_OBJECT
public:
    enum HorizontalAlignment{
        AlignLeft,
        AlignHCenter,
        AlignRight
    };
    enum VerticalAlignment{
        AlignTop,
        AlignVCenter,
        AlignBottom
    };
    SGWLabel(SGWWidget* parent, const QString& s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, SGWLabel::HorizontalAlignment horizontalAlignment, SGWLabel::VerticalAlignment verticalAlignment, const QString& font);
    static QString textFont;
    static QString iconsFont;
    void syncQuickProperties();
    static Qt::AlignmentFlag verticalAlignmentToQtAlignmentFlag(SGWLabel::VerticalAlignment x);
    static Qt::AlignmentFlag horizontalAlignmentToQtAlignmentFlag(SGWLabel::HorizontalAlignment x);
    [[nodiscard]] float getF1() const;
    void setF1(float f1);
    [[nodiscard]] float getF0() const;
    void setF0(float f0);
    [[nodiscard]] const QString& getTextAsString() const;
    [[nodiscard]] int getTextAsInt(bool* isValid, int minimum, int maximum) const;
    [[nodiscard]] float getTextAsFloat(bool* isValid, float minimum, float maximum) const;
    void setTextFromString(const QString& text);
    void setTextFromInt(int x);
    void setTextFromFloat(float x);
    [[nodiscard]] const QString& getFont() const;
    void setFont(const QString& font);
    [[nodiscard]] SGWLabel::HorizontalAlignment getHorizontalAlignment() const;
    void setHorizontalAlignment(SGWLabel::HorizontalAlignment alignment);
    [[nodiscard]] SGWLabel::VerticalAlignment getVerticalAlignment() const;
    void setVerticalAlignment(SGWLabel::VerticalAlignment alignment);
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
    SGWLabel::HorizontalAlignment horizontalAlignment;
    SGWLabel::VerticalAlignment verticalAlignment;
    bool usingTheme;
    int backgroundThemeColour;
    SGXColourRGBA backgroundColour = {};
    int foregroundThemeColour;
    SGXColourRGBA foregroundColour = {};
};

#endif // SGWLABEL_H
