#ifndef SGWVESICLECUSTOMISATIONPAGE_H
#define SGWVESICLECUSTOMISATIONPAGE_H

class SGWBackground;
class SGWInput;
class SGWButton;
class SGWLabel;
class SGWVesicleCustomisationPage
{
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
    static void maximumCenterDistanceCheck(SGWInput* /*unused*/);
    static void maximumVelocityCheck(SGWInput* /*unused*/);
    static void maximumAccelerationCheck(SGWInput* /*unused*/);
    static void maximumRadiusChangeCheck(SGWInput* /*unused*/);
    static void maximumRadiusCheck(SGWInput* /*unused*/);
    static void minimumRadiusCheck(SGWInput* /*unused*/);
    static void maximumRadiusOffsetCheck(SGWInput* /*unused*/);
    static void maximumRadiusOffsetChangeCheck(SGWInput* /*unused*/);
    static void membraneTransparencyCheck(SGWInput* /*unused*/);
    static void centerTransparencyCheck(SGWInput* /*unused*/);
    static void edgeTransparencyCheck(SGWInput* /*unused*/);
    static void frameRateCheck(SGWInput* /*unused*/);
};

#endif // SGWVESICLECUSTOMISATIONPAGE_H
