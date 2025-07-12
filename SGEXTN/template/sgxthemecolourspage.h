#ifndef SGXTHEMECOLOURSPAGE_H
#define SGXTHEMECOLOURSPAGE_H

#include <QObject>
#include <QQuickItem>
#include <qtmetamacros.h>
#include <array>

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
};

#endif // SGXTHEMECOLOURSPAGE_H
