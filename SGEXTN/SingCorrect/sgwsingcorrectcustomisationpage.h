#ifndef SGWSINGCORRECTCUSTOMISATIONPAGE_H
#define SGWSINGCORRECTCUSTOMISATIONPAGE_H

#include <QObject>
#include <qtmetamacros.h>
#include "../widgets/sgwbackground.h"
#include "../widgets/sgwbutton.h"

class SGWSingCorrectCustomisationPage : public QObject
{
    Q_OBJECT
public:
    SGWSingCorrectCustomisationPage() = delete;
    static SGWBackground* instance;
    static SGWBackground* initialise();
    static SGWBackground* scroll;
    static SGWButton* exitButton;
    static void activate();
    static void reset();
    static void exit(SGWButton* /*unused*/);
};

#endif // SGWSINGCORRECTCUSTOMISATIONPAGE_H
