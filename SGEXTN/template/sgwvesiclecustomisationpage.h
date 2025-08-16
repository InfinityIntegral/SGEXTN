#ifndef SGWVESICLECUSTOMISATIONPAGE_H
#define SGWVESICLECUSTOMISATIONPAGE_H

#include <QObject>
#include "../widgets/sgwbackground.h"
#include "../widgets/sgwinput.h"
#include <qtmetamacros.h>
#include "../widgets/sgwbutton.h"
#include "../widgets/sgwlabel.h"

class SGWVesicleCustomisationPage : public QObject
{
    Q_OBJECT
public:
    SGWVesicleCustomisationPage() = delete;
    static SGWBackground* instance;
    static void activate();
    static SGWBackground* initialise();
    static void reset();
    static SGWInput* membraneThicknessInput;
    static SGWInput* maximumCenterDistanceInput;
    static SGWInput* maximumVelocityInput;
    static SGWInput* maximumAccelerationInput;
    static SGWInput* maximumRadiusChangeInput;
    static SGWInput* maximumRadiusInput;
    static SGWInput* minimumRadiusInput;
    static SGWInput* maximumRadiusOffsetInput;
    static SGWInput* maximumRadiusOffsetChangeInput;
    static SGWInput* membraneTransparencyInput;
    static SGWInput* centerTransparencyInput;
    static SGWInput* edgeTransparencyInput;
    static SGWInput* frameRateInput;
    static SGWLabel* membraneThicknessError;
    static SGWLabel* maximumCenterDistanceError;
    static SGWLabel* maximumVelocityError;
    static SGWLabel* maximumAccelerationError;
    static SGWLabel* maximumRadiusChangeError;
    static SGWLabel* maximumRadiusError;
    static SGWLabel* minimumRadiusError;
    static SGWLabel* maximumRadiusOffsetError;
    static SGWLabel* maximumRadiusOffsetChangeError;
    static SGWLabel* membraneTransparencyError;
    static SGWLabel* centerTransparencyError;
    static SGWLabel* edgeTransparencyError;
    static SGWLabel* frameRateError;
    static void cancelChange(SGWButton* /*unused*/);
    static void confirmChange(SGWButton* /*unused*/);
    static void membraneThicknessCheck(SGWInput* /*unused*/);
};

#endif // SGWVESICLECUSTOMISATIONPAGE_H
