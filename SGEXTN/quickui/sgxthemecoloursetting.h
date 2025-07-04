#ifndef SGXTHEMECOLOURSETTING_H
#define SGXTHEMECOLOURSETTING_H

#include <QObject>
#include <QColor>
#include "../primitives/sgxcolourrgba.h"
#include <qtmetamacros.h>

class SGXThemeColourSetting : public QObject // QML compatibility class for package ThemeColours 0.0
{
    Q_OBJECT
    Q_PROPERTY(QColor noColour READ getNoColour CONSTANT)
    Q_PROPERTY(QColor themeColour0 READ getThemeColour0 WRITE setThemeColour0 NOTIFY changedThemeColour0 FINAL)
    Q_PROPERTY(QColor themeColour1 READ getThemeColour1 WRITE setThemeColour1 NOTIFY changedThemeColour1 FINAL)
    Q_PROPERTY(QColor themeColour2 READ getThemeColour2 WRITE setThemeColour2 NOTIFY changedThemeColour2 FINAL)
    Q_PROPERTY(QColor themeColour3 READ getThemeColour3 WRITE setThemeColour3 NOTIFY changedThemeColour3 FINAL)
    Q_PROPERTY(QColor themeColour4 READ getThemeColour4 WRITE setThemeColour4 NOTIFY changedThemeColour4 FINAL)
    Q_PROPERTY(QColor themeColour5 READ getThemeColour5 WRITE setThemeColour5 NOTIFY changedThemeColour5 FINAL)
    Q_PROPERTY(QColor themeColour6 READ getThemeColour6 WRITE setThemeColour6 NOTIFY changedThemeColour6 FINAL)
    Q_PROPERTY(QColor themeColour7 READ getThemeColour7 WRITE setThemeColour7 NOTIFY changedThemeColour7 FINAL)
    Q_PROPERTY(QColor themeColour8 READ getThemeColour8 WRITE setThemeColour8 NOTIFY changedThemeColour8 FINAL)
public:
    SGXThemeColourSetting();
    SGXColourRGBA noColour = SGXColourRGBA();
    [[nodiscard]] QColor getNoColour() const;
    [[nodiscard]] Q_INVOKABLE QColor getThemeColour(int x) const;
    SGXColourRGBA themeColour0 = SGXColourRGBA();
    [[nodiscard]] QColor getThemeColour0() const;
    void setThemeColour0(const QColor& x);
    SGXColourRGBA themeColour1 = SGXColourRGBA();
    [[nodiscard]] QColor getThemeColour1() const;
    void setThemeColour1(const QColor& x);
    SGXColourRGBA themeColour2 = SGXColourRGBA();
    [[nodiscard]] QColor getThemeColour2() const;
    void setThemeColour2(const QColor& x);
    SGXColourRGBA themeColour3 = SGXColourRGBA();
    [[nodiscard]] QColor getThemeColour3() const;
    void setThemeColour3(const QColor& x);
    SGXColourRGBA themeColour4 = SGXColourRGBA();
    [[nodiscard]] QColor getThemeColour4() const;
    void setThemeColour4(const QColor& x);
    SGXColourRGBA themeColour5 = SGXColourRGBA();
    [[nodiscard]] QColor getThemeColour5() const;
    void setThemeColour5(const QColor& x);
    SGXColourRGBA themeColour6 = SGXColourRGBA();
    [[nodiscard]] QColor getThemeColour6() const;
    void setThemeColour6(const QColor& x);
    SGXColourRGBA themeColour7 = SGXColourRGBA();
    [[nodiscard]] QColor getThemeColour7() const;
    void setThemeColour7(const QColor& x);
    SGXColourRGBA themeColour8 = SGXColourRGBA();
    [[nodiscard]] QColor getThemeColour8() const;
    void setThemeColour8(const QColor& x);
signals:
    void changedThemeColour0();
    void changedThemeColour1();
    void changedThemeColour2();
    void changedThemeColour3();
    void changedThemeColour4();
    void changedThemeColour5();
    void changedThemeColour6();
    void changedThemeColour7();
    void changedThemeColour8();
};

#endif // SGXTHEMECOLOURSETTING_H
