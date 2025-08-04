#ifndef SGWBUTTON_H
#define SGWBUTTON_H

#include <qtmetamacros.h>
#include "sgwwidget.h"
#include "sgwlabel.h"
#include <QString>
#include "../primitives/sgxcolourrgba.h"
#include "sgwhorizontalalignment.h"

class SGWButton : public SGWWidget
{
    Q_OBJECT
public:
    SGWButton(SGWWidget* parent, const QString& s, void (*attachedFunction)(SGWButton*), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, const QString& font);
    void syncQuickProperties();
    [[nodiscard]] float getF1() const;
    void setF1(float f1);
    [[nodiscard]] float getF0() const;
    void setF0(float f0);
    [[nodiscard]] QString getTextAsString() const;
    [[nodiscard]] int getTextAsInt(bool* isValid, int minimum, int maximum) const;
    [[nodiscard]] float getTextAsFloat(bool* isValid, float minimum, float maximum) const;
    void setTextFromString(const QString& s);
    void setTextFromInt(int x);
    void setTextFromFloat(float x);
    [[nodiscard]] QString getFont() const;
    void setFont(const QString& font);
    [[nodiscard]] SGWHorizontalAlignment::Flag getHorizontalAlignment() const;
    void setHorizontalAlignment(SGWHorizontalAlignment::Flag alignment);
    [[nodiscard]] SGWLabel::VerticalAlignment getVerticalAlignment() const;
    void setVerticalAlignment(SGWLabel::VerticalAlignment alignment);
    [[nodiscard]] bool getSelected() const;
    void setSelected(bool selected);
    [[nodiscard]] void (*getClickFunction() const)(SGWButton*);
    void setClickFunction(void (*function)(SGWButton*));
    [[nodiscard]] void (*getPressFunction() const)(SGWButton*);
    void setPressFunction(void (*function)(SGWButton*));
    [[nodiscard]] void (*getReleaseFunction() const)(SGWButton*);
    void setReleaseFunction(void (*function)(SGWButton*));
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
protected:
    float f1;
    float f0;
    QString text;
    QString font;
    SGWHorizontalAlignment::Flag horizontalAlignment;
    SGWLabel::VerticalAlignment verticalAlignment;
    void (*clickFunction)(SGWButton*);
    void (*pressFunction)(SGWButton*);
    void (*releaseFunction)(SGWButton*);
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
public slots:
    void eventReceived(const QString& s);
};

#endif // SGWBUTTON_H
