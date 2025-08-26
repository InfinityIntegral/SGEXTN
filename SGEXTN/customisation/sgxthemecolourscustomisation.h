#ifndef SGXTHEMECOLOURSCUSTOMISATION_H
#define SGXTHEMECOLOURSCUSTOMISATION_H

#include <QObject>
#include <qtmetamacros.h>

class SGXThemeColoursCustomisation : public QObject
{
    Q_OBJECT
public:
    SGXThemeColoursCustomisation() = delete;
    static void loadThemeColours();
    static void syncThemeColours();
};

#endif // SGXTHEMECOLOURSCUSTOMISATION_H
