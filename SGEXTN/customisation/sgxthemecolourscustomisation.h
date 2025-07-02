#ifndef SGXTHEMECOLOURSCUSTOMISATION_H
#define SGXTHEMECOLOURSCUSTOMISATION_H

#include <QObject>
#include <qtmetamacros.h>

class SGXThemeColoursCustomisation : public QObject // non instantiable class for customising app theme colours
{
    Q_OBJECT
public:
    SGXThemeColoursCustomisation() = delete;
    static void loadThemeColours(); // load theme colours from file
    // note that during the National Day period, the theme will be changed to "For Our Nation" instead of "Standard Light" (the default theme), this overrides custom theme configuration
    // there is no builtin API for themes, but all 05524F apps using SGEXTN should have the following themes
    // Standard Light: mainly light pink, default theme
    // Standard Dark: mainly dark pink, equivalent to dark mode
    // For Our Nation: uses the same hue of red as our flag, default during National Day period
    static void syncThemeColours(); // write current theme colours to file
};

#endif // SGXTHEMECOLOURSCUSTOMISATION_H
