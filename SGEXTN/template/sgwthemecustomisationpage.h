#ifndef SGWTHEMECUSTOMISATIONPAGE_H
#define SGWTHEMECUSTOMISATIONPAGE_H

#include <qtmetamacros.h>
#include "../widgets/sgwbackground.h"
#include "../widgets/sgwbutton.h"
#include <QObject>
#include <array>
#include "../widgets/sgwlabel.h"
#include "../widgets/sgwblankwidget.h"
#include "../primitives/sgxcolourrgba.h"
#include "../widgets/sgwcolourpickerwidget.h"

class SGWThemeCustomisationPage : public QObject
{
    Q_OBJECT
public:
    SGWThemeCustomisationPage() = delete;
    static void activate();
    static SGWBackground* initialise();
    static SGWBackground* menuInstance;
    static void showThemeDefaultLight(SGWButton* /*unused*/);
    static void showThemeDefaultDark(SGWButton* /*unused*/);
    static void showThemeForOurNation(SGWButton* /*unused*/);
    static void showThemeCustomLight(SGWButton* /*unused*/);
    static void showThemeCustomDark(SGWButton* /*unused*/);
    static void showThemeCustomAny(SGWButton* /*unused*/);
    static SGWBackground* detailsInstance;
    static SGWButton* cancelButton;
    static SGWButton* confirmButton;
    static SGWBackground* detailsScroll;
    static SGWLabel* detailsInfo;
    static std::array<SGWBlankWidget*, 9> coloursDisplay;
    static SGWBackground* initialiseDetailsPage();
    static std::array<SGXColourRGBA, 9> themeColours;
    static QString infoString;
    static void updateElements();
    static bool isUsingCustomLight;
    static SGWLabel* customLightLabel;
    static SGWColourPickerWidget* customLightColourPicker;
    static void updateCustomLight(SGWColourPickerWidget* selector);
    static bool isUsingCustomDark;
    static SGWLabel* customDarkLabel;
    static SGWColourPickerWidget* customDarkColourPicker;
    static void updateCustomDark(SGWColourPickerWidget* selector);
    static bool isUsingCustomAny;
    static SGWLabel* customAnyLabel;
    static std::array<SGWColourPickerWidget*, 9> customAnyColourPicker;
    static void updateCustomAny(SGWColourPickerWidget* selector);
};

#endif // SGWTHEMECUSTOMISATIONPAGE_H
