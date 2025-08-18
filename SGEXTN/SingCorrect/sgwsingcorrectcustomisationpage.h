#ifndef SGWSINGCORRECTCUSTOMISATIONPAGE_H
#define SGWSINGCORRECTCUSTOMISATIONPAGE_H

#include <QObject>
#include <qtmetamacros.h>
#include "../widgets/sgwbackground.h"
#include "../widgets/sgwbutton.h"
#include "../widgets/sgwlabel.h"
#include "../widgets/sgwinput.h"

class SGWSingCorrectCustomisationPage : public QObject
{
    Q_OBJECT
public:
    SGWSingCorrectCustomisationPage() = delete;
    static SGWBackground* instance;
    static SGWBackground* initialise();
    static void activate();
    static void reset();
    static void exit(SGWButton* /*unused*/);
    static SGWButton* enableButton;
    static SGWButton* disableButton;
    static void enableFunction(SGWButton* /*unused*/);
    static void disableFunction(SGWButton* /*unused*/);
    static SGWInput* prefixInput;
    static SGWLabel* prefixInvalidMessage;
    static SGWLabel* prefixUnsavedMessage;
    static void prefixUpdated(SGWInput* /*unused*/);
    static void prefixSaved(SGWInput* /*unused*/);
};

#endif // SGWSINGCORRECTCUSTOMISATIONPAGE_H
