#ifndef SGWVESICLECUSTOMISATIONPAGE_H
#define SGWVESICLECUSTOMISATIONPAGE_H

#include <QObject>
#include "../widgets/sgwbackground.h"
#include "../widgets/sgwinput.h"
#include "../widgets/sgwcolourpickerwidget.h"
#include <qtmetamacros.h>

class SGWVesicleCustomisationPage : public QObject
{
    Q_OBJECT
public:
    SGWVesicleCustomisationPage() = delete;
    static SGWBackground* instance;
    static void activate();
    static SGWBackground* initialise();
    static void reset();
    static SGWColourPickerWidget* membraneColourInput;
    static SGWColourPickerWidget* contentsColourInput;
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
    static SGWBackground* confirmDialogInstance;
    static SGWBackground* initialiseConfirmDialog();
    static void confirmChange();
    static void activateConfirmDialog();
    static void cancelChange();
    static void cancelConfirmDialog();
};

#endif // SGWVESICLECUSTOMISATIONPAGE_H
