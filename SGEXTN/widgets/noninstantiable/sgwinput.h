#ifndef SGWINPUT_H
#define SGWINPUT_H

#include <qtmetamacros.h>
#include "sgwwidget.h"
#include "../enums/sgwhorizontalalignment.h"
#include "../enums/sgwverticalalignment.h"
#include "../../primitives/sgxcolourrgba.h"
#include <QString>

class SGWInput : public SGWWidget
{
    Q_OBJECT
public:
    SGWInput() = delete;
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
    [[nodiscard]] SGWVerticalAlignment::Flag getVerticalAlignment() const;
    void setVerticalAlignment(SGWVerticalAlignment::Flag alignment);
    [[nodiscard]] bool getInvalid() const;
    void setInvalid(bool invalid);
    [[nodiscard]] void (*getTextChangedFunction() const)(SGWInput*);
    void setTextChangedFunction(void (*function)(SGWInput*));
    [[nodiscard]] void (*getFocusStartFunction() const)(SGWInput*);
    void setFocusStartFunction(void (*function)(SGWInput*));
    [[nodiscard]] void (*getFocusEndFunction() const)(SGWInput*);
    void setFocusEndFunction(void (*function)(SGWInput*));
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
    [[nodiscard]] int getBackgroundInvalidThemeColour(bool* isUsing) const;
    void setBackgroundInvalidThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getBackgroundInvalidColour(bool* isUsing) const;
    void setBackgroundInvalidColour(SGXColourRGBA colour);
    [[nodiscard]] int getForegroundInvalidThemeColour(bool* isUsing) const;
    void setForegroundInvalidThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getForegroundInvalidColour(bool* isUsing) const;
    void setForegroundInvalidColour(SGXColourRGBA colour);
    [[nodiscard]] int getBackgroundHoverInvalidThemeColour(bool* isUsing) const;
    void setBackgroundHoverInvalidThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getBackgroundHoverInvalidColour(bool* isUsing) const;
    void setBackgroundHoverInvalidColour(SGXColourRGBA colour);
    [[nodiscard]] int getForegroundHoverInvalidThemeColour(bool* isUsing) const;
    void setForegroundHoverInvalidThemeColour(int themeColour);
    [[nodiscard]] SGXColourRGBA getForegroundHoverInvalidColour(bool* isUsing) const;
    void setForegroundHoverInvalidColour(SGXColourRGBA colour);
protected:
    SGWInput(SGWWidget* parent, void (*validationFunction)(SGWInput*), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float f1, float f0, SGWHorizontalAlignment::Flag horizontalAlignment, SGWVerticalAlignment::Flag verticalAlignment);
    float f1;
    float f0;
    QString text;
    QString font;
    SGWHorizontalAlignment::Flag horizontalAlignment;
    SGWVerticalAlignment::Flag verticalAlignment;
    void (*textChangedFunction)(SGWInput*);
    void (*focusStartFunction)(SGWInput*);
    void (*focusEndFunction)(SGWInput*);
    bool invalid;
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
    int backgroundInvalidThemeColour;
    SGXColourRGBA backgroundInvalidColour = {};
    int foregroundInvalidThemeColour;
    SGXColourRGBA foregroundInvalidColour = {};
    int backgroundHoverInvalidThemeColour;
    SGXColourRGBA backgroundHoverInvalidColour = {};
    int foregroundHoverInvalidThemeColour;
    SGXColourRGBA foregroundHoverInvalidColour = {};
public slots:
    void eventReceived(const QString& s);
};

#endif // SGWINPUT_H
