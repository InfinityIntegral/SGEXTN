#ifndef SGXTHEMECOLOURSPAGE_H
#define SGXTHEMECOLOURSPAGE_H

#include <QObject>
#include <QQuickItem>
#include <qtmetamacros.h>
#include <array>
#include "../primitives/sgxcolourrgba.h"

class SGXThemeColoursPage : public QObject
{
    Q_OBJECT
public:
    SGXThemeColoursPage() = delete;
    static QQuickItem* instance;
    static void initialise();
    static std::array<QQuickItem*, 9> customLightColoursDisplay;
    static QQuickItem* customLightMainColourPicker;
    static std::array<QQuickItem*, 9> customDarkColoursDisplay;
    static QQuickItem* customDarkMainColourPicker;
    static std::array<QQuickItem*, 9> customAnyColoursDisplay;
    static std::array<QQuickItem*, 9> customAnyColourPicker;
    static std::array<SGXColourRGBA, 9> coloursToSet;
    static QQuickItem* confirmDialog;
    static bool includeVesicleInTheme;
    static void activateConfirmDialog();
signals:
    void doNothing();
public slots:
    static void activate();
    static void setThemeDefaultLight();
    static void setThemeDefaultDark();
    static void setThemeForOurNation();
    static void setThemeCustomLight();
    static void setThemeCustomDark();
    static void setThemeCustomAny();
    static void updateThemeCustomLight();
    static void updateThemeCustomDark();
    static void updateThemeCustomAny();
    static void confirmThemeColourSettings();
    static void cancelThemeColourSettings();
    static void exitPage();
};

#endif // SGXTHEMECOLOURSPAGE_H
