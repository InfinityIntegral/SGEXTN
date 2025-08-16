#ifndef SGWTHEMECUSTOMISATIONPAGE_H
#define SGWTHEMECUSTOMISATIONPAGE_H

#include <qtmetamacros.h>
#include "../widgets/sgwbackground.h"
#include "../widgets/sgwbutton.h"
#include <QObject>

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
};

#endif // SGWTHEMECUSTOMISATIONPAGE_H
