#include "sgwvesiclecustomisationpage.h"
#include "../widgets/noninstantiable/sgwbackground.h"
#include "../widgets/noninstantiable/sgwinput.h"
#include "../widgets/instantiable/sgwpagebackground.h"
#include "../widgets/instantiable/sgwsequentialscrollview.h"
#include "../widgets/instantiable/sgwtextbutton.h"
#include "../widgets/instantiable/sgwblankwidget.h"
#include "../widgets/instantiable/sgwtextlabel.h"
#include "../widgets/instantiable/sgwsequentiallonglabel.h"
#include "../widgets/instantiable/sgwtextinput.h"
#include "../widgets/noninstantiable/sgwwidget.h"
#include <QString>
#include "../widgets/enums/sgwhorizontalalignment.h"
#include "../widgets/noninstantiable/sgwbutton.h"
#include "../widgets/noninstantiable/sgwlabel.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include <limits>
#include "../widgets/unique/sgwstatusbar.h"
#include "../customisation/sgxvesiclespropertiescustomisation.h"

SGWBackground* SGWVesicleCustomisationPage::instance = nullptr;
SGWInput* SGWVesicleCustomisationPage::membraneThicknessInput = nullptr;
SGWInput* SGWVesicleCustomisationPage::maximumCenterDistanceInput = nullptr;
SGWInput* SGWVesicleCustomisationPage::maximumVelocityInput = nullptr;
SGWInput* SGWVesicleCustomisationPage::maximumAccelerationInput = nullptr;
SGWInput* SGWVesicleCustomisationPage::maximumRadiusChangeInput = nullptr;
SGWInput* SGWVesicleCustomisationPage::maximumRadiusInput = nullptr;
SGWInput* SGWVesicleCustomisationPage::minimumRadiusInput = nullptr;
SGWInput* SGWVesicleCustomisationPage::maximumRadiusOffsetInput = nullptr;
SGWInput* SGWVesicleCustomisationPage::maximumRadiusOffsetChangeInput = nullptr;
SGWInput* SGWVesicleCustomisationPage::membraneTransparencyInput = nullptr;
SGWInput* SGWVesicleCustomisationPage::centerTransparencyInput = nullptr;
SGWInput* SGWVesicleCustomisationPage::edgeTransparencyInput = nullptr;
SGWInput* SGWVesicleCustomisationPage::frameRateInput = nullptr;
SGWLabel* SGWVesicleCustomisationPage::membraneThicknessError = nullptr;
SGWLabel* SGWVesicleCustomisationPage::maximumCenterDistanceError = nullptr;
SGWLabel* SGWVesicleCustomisationPage::maximumVelocityError = nullptr;
SGWLabel* SGWVesicleCustomisationPage::maximumAccelerationError = nullptr;
SGWLabel* SGWVesicleCustomisationPage::maximumRadiusChangeError = nullptr;
SGWLabel* SGWVesicleCustomisationPage::maximumRadiusError = nullptr;
SGWLabel* SGWVesicleCustomisationPage::minimumRadiusError = nullptr;
SGWLabel* SGWVesicleCustomisationPage::maximumRadiusOffsetError = nullptr;
SGWLabel* SGWVesicleCustomisationPage::maximumRadiusOffsetChangeError = nullptr;
SGWLabel* SGWVesicleCustomisationPage::membraneTransparencyError = nullptr;
SGWLabel* SGWVesicleCustomisationPage::centerTransparencyError = nullptr;
SGWLabel* SGWVesicleCustomisationPage::edgeTransparencyError = nullptr;
SGWLabel* SGWVesicleCustomisationPage::frameRateError = nullptr;

void SGWVesicleCustomisationPage::activate(){
    SGWBackground::enable(SGWVesicleCustomisationPage::instance, &SGWVesicleCustomisationPage::initialise, &SGWVesicleCustomisationPage::reset);
}

SGWBackground* SGWVesicleCustomisationPage::initialise(){
    SGWVesicleCustomisationPage::instance = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0, 0.0f, 8);
    SGWWidget* bg = new SGWSequentialScrollView(SGWVesicleCustomisationPage::instance, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f, 8);
    new SGWTextButton(SGWVesicleCustomisationPage::instance, "cancel", &SGWVesicleCustomisationPage::cancelChange, 0.0f, 0.0f, 1.0f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    new SGWTextButton(SGWVesicleCustomisationPage::instance, "confirm", &SGWVesicleCustomisationPage::confirmChange, 0.5f, 0.0f, 1.0f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    SGWWidget* p = nullptr;
    QString s = "";
    
    new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 8);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 3.0f, 8);
    new SGWTextLabel(p, "customise vesicles", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 2.0f, SGWHorizontalAlignment::Center, false);
    s = "Note: a vesicle is an organelle found inside cells that transport substances.";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 8);
    
    s = "In the settings below, 1 \"unit\" of distance will refer to half the width of the animation screen.";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 8);
    
    s = "    The membrane thickness refers to the thickness of the vesicle membrane and has a default value of 0.05";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "membrane thickness:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWVesicleCustomisationPage::membraneThicknessInput = new SGWTextInput(p, &SGWVesicleCustomisationPage::membraneThicknessCheck, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::membraneThicknessError = new SGWTextLabel(p, "nonnegative number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    
    s = "    Center distance is the maximum distance that the center of a vesicle can be from the center of the screen on either the x or the y direction. Once that is exceeded, the vesicle reappears on the other side of the screen, keeping its size and shape. This has a default value of 1.5";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "center distance:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWVesicleCustomisationPage::maximumCenterDistanceInput = new SGWTextInput(p, &SGWVesicleCustomisationPage::maximumCenterDistanceCheck, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::maximumCenterDistanceError = new SGWTextLabel(p, "nonnegative number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    
    s = "    The maximum velocity controls the maximum speed of vesicles in units per second. Setting this too high may be distracting. This has a default value of 0.01";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "maximum velocity:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWVesicleCustomisationPage::maximumVelocityInput = new SGWTextInput(p, &SGWVesicleCustomisationPage::maximumVelocityCheck, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::maximumVelocityError = new SGWTextLabel(p, "nonnegative number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    
    s = "    The maximum acceleration controls the maximum change in speed of vesicles in units per second per second. This has a default value of 0.01";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "max. acceleration:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWVesicleCustomisationPage::maximumAccelerationInput = new SGWTextInput(p, &SGWVesicleCustomisationPage::maximumAccelerationCheck, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::maximumAccelerationError = new SGWTextLabel(p, "nonnegative number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    
    s = "    The maximum radius change controls by how much vesicles can become bigger or smaller in each second. Setting this too high may be distracting. This has a default value of 0.01";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "max. radius change:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWVesicleCustomisationPage::maximumRadiusChangeInput = new SGWTextInput(p, &SGWVesicleCustomisationPage::maximumRadiusChangeCheck, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::maximumRadiusChangeError = new SGWTextLabel(p, "nonnegative number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    
    s = "    The minimum radius controls the smallest possible radius that a vesicle can have. Setting this too small will make small vesicles invisible. The default value for this setting is 0.1";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "minimum radius:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWVesicleCustomisationPage::minimumRadiusInput = new SGWTextInput(p, &SGWVesicleCustomisationPage::minimumRadiusCheck, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::minimumRadiusError = new SGWTextLabel(p, "nonnegative number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    
    s = "    The maximum radius controls the largest possible radius that a vesicle can have. The default value is 0.35";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "maximum radius:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWVesicleCustomisationPage::maximumRadiusInput = new SGWTextInput(p, &SGWVesicleCustomisationPage::maximumRadiusCheck, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::maximumRadiusError = new SGWTextLabel(p, "nonnegative number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    
    s = "    The maximum offset, or maximum radius offset, determines how much the radius of a vesicle at a certain point can deviate from the base radius as a proportion of the base radius. This controls how irregularly shaped the vesicles are. This has a default value of 0.1";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "maximum offset:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWVesicleCustomisationPage::maximumRadiusOffsetInput = new SGWTextInput(p, &SGWVesicleCustomisationPage::maximumRadiusOffsetCheck, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::maximumRadiusOffsetError = new SGWTextLabel(p, "nonnegative number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    
    s = "    The maximum offset change controls the maximum change in offset at any point on any vesicle. The default value for this is 0.1";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "max. offset change:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWVesicleCustomisationPage::maximumRadiusOffsetChangeInput = new SGWTextInput(p, &SGWVesicleCustomisationPage::maximumRadiusOffsetChangeCheck, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::maximumRadiusOffsetChangeError = new SGWTextLabel(p, "nonnegative number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    
    s = "    The membrane transparency controls the transparency of the vesicle membrane with 0 being fully transparent and 1 being fully opaque. The default value for this is 0.2";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "membrane transparency:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWVesicleCustomisationPage::membraneTransparencyInput = new SGWTextInput(p, &SGWVesicleCustomisationPage::membraneTransparencyCheck, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::membraneTransparencyError = new SGWTextLabel(p, "number between 0 and 1", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    
    s = "    The center transparency controls the transparency of vesicles at the center. The transparency of vesicle contents forms a gradient from center to edge. The default value of this is 0.1";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "center transparency:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWVesicleCustomisationPage::centerTransparencyInput = new SGWTextInput(p, &SGWVesicleCustomisationPage::centerTransparencyCheck, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::centerTransparencyError = new SGWTextLabel(p, "number between 0 and 1", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    
    s = "    The edge transparency controls the transparency of vesicles at the edge of the contents region where it meets the membrane. The transparency of vesicle contents forms a gradient from center to edge. The default value of this is 0.05";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "edge transparency:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWVesicleCustomisationPage::edgeTransparencyInput = new SGWTextInput(p, &SGWVesicleCustomisationPage::edgeTransparencyCheck, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::edgeTransparencyError = new SGWTextLabel(p, "number between 0 and 1", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    
    s = "    This determines the frame rate of the animation in frames per second. Setting the frame rate too high can increase battery usage and setting the frame rate too low can lead to the animation being distracting. You are recommended to set the frame rate around the default frame rate of 10. Note that the frame rate does not need to be an integer.";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "frame rate:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWVesicleCustomisationPage::frameRateInput = new SGWTextInput(p, &SGWVesicleCustomisationPage::frameRateCheck, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::frameRateError = new SGWTextLabel(p, "positive number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    
    return SGWVesicleCustomisationPage::instance;
}

void SGWVesicleCustomisationPage::reset(){
    (*SGWVesicleCustomisationPage::membraneThicknessInput).setTextFromFloat(SGUCentralManagement::cuteVesiclesMembraneThickness);
    (*SGWVesicleCustomisationPage::maximumCenterDistanceInput).setTextFromFloat(SGUCentralManagement::cuteVesiclesMaximumCenterDistance);
    (*SGWVesicleCustomisationPage::maximumVelocityInput).setTextFromFloat(SGUCentralManagement::cuteVesiclesMaximumVelocity);
    (*SGWVesicleCustomisationPage::maximumAccelerationInput).setTextFromFloat(SGUCentralManagement::cuteVesiclesMaximumAcceleration);
    (*SGWVesicleCustomisationPage::maximumRadiusChangeInput).setTextFromFloat(SGUCentralManagement::cuteVesiclesMaximumRadiusChange);
    (*SGWVesicleCustomisationPage::maximumRadiusInput).setTextFromFloat(SGUCentralManagement::cuteVesiclesMaximumRadius);
    (*SGWVesicleCustomisationPage::minimumRadiusInput).setTextFromFloat(SGUCentralManagement::cuteVesiclesMinimumRadius);
    (*SGWVesicleCustomisationPage::maximumRadiusOffsetInput).setTextFromFloat(SGUCentralManagement::cuteVesiclesMaximumRadiusOffset);
    (*SGWVesicleCustomisationPage::maximumRadiusOffsetChangeInput).setTextFromFloat(SGUCentralManagement::cuteVesiclesMaximumRadiusOffsetChange);
    (*SGWVesicleCustomisationPage::membraneTransparencyInput).setTextFromFloat(SGUCentralManagement::cuteVesiclesMembraneTransparency);
    (*SGWVesicleCustomisationPage::centerTransparencyInput).setTextFromFloat(SGUCentralManagement::cuteVesiclesCenterTransparency);
    (*SGWVesicleCustomisationPage::edgeTransparencyInput).setTextFromFloat(SGUCentralManagement::cuteVesiclesEdgeTransparency);
    (*SGWVesicleCustomisationPage::frameRateInput).setTextFromFloat(SGUCentralManagement::cuteVesiclesFrameRate);
}

void SGWVesicleCustomisationPage::cancelChange(SGWButton */*unused*/){
    SGWBackground::disable(SGWVesicleCustomisationPage::instance);
}

void SGWVesicleCustomisationPage::confirmChange(SGWButton */*unused*/){
    bool isValid = true;
    bool prevValid = false;
    (void)(*SGWVesicleCustomisationPage::membraneThicknessInput).getTextAsFloat(&prevValid, 0.0f, std::numeric_limits<float>::infinity());
    if(prevValid == false){isValid = false;}
    (void)(*SGWVesicleCustomisationPage::maximumCenterDistanceInput).getTextAsFloat(&prevValid, 0.0f, std::numeric_limits<float>::infinity());
    if(prevValid == false){isValid = false;}
    (void)(*SGWVesicleCustomisationPage::maximumVelocityInput).getTextAsFloat(&prevValid, 0.0f, std::numeric_limits<float>::infinity());
    if(prevValid == false){isValid = false;}
    (void)(*SGWVesicleCustomisationPage::maximumAccelerationInput).getTextAsFloat(&prevValid, 0.0f, std::numeric_limits<float>::infinity());
    if(prevValid == false){isValid = false;}
    (void)(*SGWVesicleCustomisationPage::maximumRadiusChangeInput).getTextAsFloat(&prevValid, 0.0f, std::numeric_limits<float>::infinity());
    if(prevValid == false){isValid = false;}
    (void)(*SGWVesicleCustomisationPage::maximumRadiusInput).getTextAsFloat(&prevValid, 0.0f, std::numeric_limits<float>::infinity());
    if(prevValid == false){isValid = false;}
    (void)(*SGWVesicleCustomisationPage::minimumRadiusInput).getTextAsFloat(&prevValid, 0.0f, std::numeric_limits<float>::infinity());
    if(prevValid == false){isValid = false;}
    (void)(*SGWVesicleCustomisationPage::maximumRadiusOffsetInput).getTextAsFloat(&prevValid, 0.0f, std::numeric_limits<float>::infinity());
    if(prevValid == false){isValid = false;}
    (void)(*SGWVesicleCustomisationPage::maximumRadiusOffsetChangeInput).getTextAsFloat(&prevValid, 0.0f, std::numeric_limits<float>::infinity());
    if(prevValid == false){isValid = false;}
    (void)(*SGWVesicleCustomisationPage::membraneTransparencyInput).getTextAsFloat(&prevValid, 0.0f, 1.0f);
    if(prevValid == false){isValid = false;}
    (void)(*SGWVesicleCustomisationPage::centerTransparencyInput).getTextAsFloat(&prevValid, 0.0f, 1.0f);
    if(prevValid == false){isValid = false;}
    (void)(*SGWVesicleCustomisationPage::edgeTransparencyInput).getTextAsFloat(&prevValid, 0.0f, 1.0f);
    if(prevValid == false){isValid = false;}
    (void)(*SGWVesicleCustomisationPage::frameRateInput).getTextAsFloat(&prevValid, std::numeric_limits<float>::denorm_min(), std::numeric_limits<float>::infinity());
    if(prevValid == false){isValid = false;}
    if(isValid == false){
        SGWStatusBar::notify("invalid input");
        return;
    }
    SGUCentralManagement::cuteVesiclesMembraneThickness = (*SGWVesicleCustomisationPage::membraneThicknessInput).getTextAsFloat(nullptr, 0.0f, std::numeric_limits<float>::infinity());
    SGUCentralManagement::cuteVesiclesMaximumCenterDistance = (*SGWVesicleCustomisationPage::maximumCenterDistanceInput).getTextAsFloat(nullptr, 0.0f, std::numeric_limits<float>::infinity());
    SGUCentralManagement::cuteVesiclesMaximumVelocity = (*SGWVesicleCustomisationPage::maximumVelocityInput).getTextAsFloat(nullptr, 0.0f, std::numeric_limits<float>::infinity());
    SGUCentralManagement::cuteVesiclesMaximumAcceleration = (*SGWVesicleCustomisationPage::maximumAccelerationInput).getTextAsFloat(nullptr, 0.0f, std::numeric_limits<float>::infinity());
    SGUCentralManagement::cuteVesiclesMaximumRadiusChange = (*SGWVesicleCustomisationPage::maximumRadiusChangeInput).getTextAsFloat(nullptr, 0.0f, std::numeric_limits<float>::infinity());
    SGUCentralManagement::cuteVesiclesMaximumRadius = (*SGWVesicleCustomisationPage::maximumRadiusInput).getTextAsFloat(nullptr, 0.0f, std::numeric_limits<float>::infinity());
    SGUCentralManagement::cuteVesiclesMinimumRadius = (*SGWVesicleCustomisationPage::minimumRadiusInput).getTextAsFloat(nullptr, 0.0f, std::numeric_limits<float>::infinity());
    SGUCentralManagement::cuteVesiclesMaximumRadiusOffset = (*SGWVesicleCustomisationPage::maximumRadiusOffsetInput).getTextAsFloat(nullptr, 0.0f, std::numeric_limits<float>::infinity());
    SGUCentralManagement::cuteVesiclesMaximumRadiusOffsetChange = (*SGWVesicleCustomisationPage::maximumRadiusOffsetChangeInput).getTextAsFloat(nullptr, 0.0f, std::numeric_limits<float>::infinity());
    SGUCentralManagement::cuteVesiclesMembraneTransparency = (*SGWVesicleCustomisationPage::membraneTransparencyInput).getTextAsFloat(nullptr, 0.0f, 1.0f);
    SGUCentralManagement::cuteVesiclesCenterTransparency = (*SGWVesicleCustomisationPage::centerTransparencyInput).getTextAsFloat(nullptr, 0.0f, 1.0f);
    SGUCentralManagement::cuteVesiclesEdgeTransparency = (*SGWVesicleCustomisationPage::edgeTransparencyInput).getTextAsFloat(nullptr, 0.0f, 1.0f);
    SGUCentralManagement::cuteVesiclesFrameRate = (*SGWVesicleCustomisationPage::frameRateInput).getTextAsFloat(nullptr, std::numeric_limits<float>::denorm_min(), std::numeric_limits<float>::infinity());
    SGXVesiclesPropertiesCustomisation::syncVesicleProperties();
    SGWBackground::disable(SGWVesicleCustomisationPage::instance);
}

void SGWVesicleCustomisationPage::membraneThicknessCheck(SGWInput */*unused*/){
    bool isValid = false;
    (void)(*SGWVesicleCustomisationPage::membraneThicknessInput).getTextAsFloat(&isValid, 0.0f, std::numeric_limits<float>::infinity());
    if(isValid == false){
        (*SGWVesicleCustomisationPage::membraneThicknessInput).setInvalid(true);
        (*SGWVesicleCustomisationPage::membraneThicknessError).setItemVisibility(true);
    }
    else{
        (*SGWVesicleCustomisationPage::membraneThicknessInput).setInvalid(false);
        (*SGWVesicleCustomisationPage::membraneThicknessError).setItemVisibility(false);
    }
}

void SGWVesicleCustomisationPage::maximumCenterDistanceCheck(SGWInput */*unused*/){
    bool isValid = false;
    (void)(*SGWVesicleCustomisationPage::maximumCenterDistanceInput).getTextAsFloat(&isValid, 0.0f, std::numeric_limits<float>::infinity());
    if(isValid == false){
        (*SGWVesicleCustomisationPage::maximumCenterDistanceInput).setInvalid(true);
        (*SGWVesicleCustomisationPage::maximumCenterDistanceError).setItemVisibility(true);
    }
    else{
        (*SGWVesicleCustomisationPage::maximumCenterDistanceInput).setInvalid(false);
        (*SGWVesicleCustomisationPage::maximumCenterDistanceError).setItemVisibility(false);
    }
}

void SGWVesicleCustomisationPage::maximumVelocityCheck(SGWInput */*unused*/){
    bool isValid = false;
    (void)(*SGWVesicleCustomisationPage::maximumVelocityInput).getTextAsFloat(&isValid, 0.0f, std::numeric_limits<float>::infinity());
    if(isValid == false){
        (*SGWVesicleCustomisationPage::maximumVelocityInput).setInvalid(true);
        (*SGWVesicleCustomisationPage::maximumVelocityError).setItemVisibility(true);
    }
    else{
        (*SGWVesicleCustomisationPage::maximumVelocityInput).setInvalid(false);
        (*SGWVesicleCustomisationPage::maximumVelocityError).setItemVisibility(false);
    }
}

void SGWVesicleCustomisationPage::maximumAccelerationCheck(SGWInput */*unused*/){
    bool isValid = false;
    (void)(*SGWVesicleCustomisationPage::maximumAccelerationInput).getTextAsFloat(&isValid, 0.0f, std::numeric_limits<float>::infinity());
    if(isValid == false){
        (*SGWVesicleCustomisationPage::maximumAccelerationInput).setInvalid(true);
        (*SGWVesicleCustomisationPage::maximumAccelerationError).setItemVisibility(true);
    }
    else{
        (*SGWVesicleCustomisationPage::maximumAccelerationInput).setInvalid(false);
        (*SGWVesicleCustomisationPage::maximumAccelerationError).setItemVisibility(false);
    }
}

void SGWVesicleCustomisationPage::maximumRadiusChangeCheck(SGWInput */*unused*/){
    bool isValid = false;
    (void)(*SGWVesicleCustomisationPage::maximumRadiusChangeInput).getTextAsFloat(&isValid, 0.0f, std::numeric_limits<float>::infinity());
    if(isValid == false){
        (*SGWVesicleCustomisationPage::maximumRadiusChangeInput).setInvalid(true);
        (*SGWVesicleCustomisationPage::maximumRadiusChangeError).setItemVisibility(true);
    }
    else{
        (*SGWVesicleCustomisationPage::maximumRadiusChangeInput).setInvalid(false);
        (*SGWVesicleCustomisationPage::maximumRadiusChangeError).setItemVisibility(false);
    }
}

void SGWVesicleCustomisationPage::maximumRadiusCheck(SGWInput */*unused*/){
    bool isValid = false;
    (void)(*SGWVesicleCustomisationPage::maximumRadiusInput).getTextAsFloat(&isValid, 0.0f, std::numeric_limits<float>::infinity());
    if(isValid == false){
        (*SGWVesicleCustomisationPage::maximumRadiusInput).setInvalid(true);
        (*SGWVesicleCustomisationPage::maximumRadiusError).setItemVisibility(true);
    }
    else{
        (*SGWVesicleCustomisationPage::maximumRadiusInput).setInvalid(false);
        (*SGWVesicleCustomisationPage::maximumRadiusError).setItemVisibility(false);
    }
}

void SGWVesicleCustomisationPage::minimumRadiusCheck(SGWInput */*unused*/){
    bool isValid = false;
    (void)(*SGWVesicleCustomisationPage::minimumRadiusInput).getTextAsFloat(&isValid, 0.0f, std::numeric_limits<float>::infinity());
    if(isValid == false){
        (*SGWVesicleCustomisationPage::minimumRadiusInput).setInvalid(true);
        (*SGWVesicleCustomisationPage::minimumRadiusError).setItemVisibility(true);
    }
    else{
        (*SGWVesicleCustomisationPage::minimumRadiusInput).setInvalid(false);
        (*SGWVesicleCustomisationPage::minimumRadiusError).setItemVisibility(false);
    }
}

void SGWVesicleCustomisationPage::maximumRadiusOffsetCheck(SGWInput */*unused*/){
    bool isValid = false;
    (void)(*SGWVesicleCustomisationPage::maximumRadiusOffsetInput).getTextAsFloat(&isValid, 0.0f, std::numeric_limits<float>::infinity());
    if(isValid == false){
        (*SGWVesicleCustomisationPage::maximumRadiusOffsetInput).setInvalid(true);
        (*SGWVesicleCustomisationPage::maximumRadiusOffsetError).setItemVisibility(true);
    }
    else{
        (*SGWVesicleCustomisationPage::maximumRadiusOffsetInput).setInvalid(false);
        (*SGWVesicleCustomisationPage::maximumRadiusOffsetError).setItemVisibility(false);
    }
}

void SGWVesicleCustomisationPage::maximumRadiusOffsetChangeCheck(SGWInput */*unused*/){
    bool isValid = false;
    (void)(*SGWVesicleCustomisationPage::maximumRadiusOffsetChangeInput).getTextAsFloat(&isValid, 0.0f, std::numeric_limits<float>::infinity());
    if(isValid == false){
        (*SGWVesicleCustomisationPage::maximumRadiusOffsetChangeInput).setInvalid(true);
        (*SGWVesicleCustomisationPage::maximumRadiusOffsetChangeError).setItemVisibility(true);
    }
    else{
        (*SGWVesicleCustomisationPage::maximumRadiusOffsetChangeInput).setInvalid(false);
        (*SGWVesicleCustomisationPage::maximumRadiusOffsetChangeError).setItemVisibility(false);
    }
}

void SGWVesicleCustomisationPage::membraneTransparencyCheck(SGWInput */*unused*/){
    bool isValid = false;
    (void)(*SGWVesicleCustomisationPage::membraneTransparencyInput).getTextAsFloat(&isValid, 0.0f, 1.0f);
    if(isValid == false){
        (*SGWVesicleCustomisationPage::membraneTransparencyInput).setInvalid(true);
        (*SGWVesicleCustomisationPage::membraneTransparencyError).setItemVisibility(true);
    }
    else{
        (*SGWVesicleCustomisationPage::membraneTransparencyInput).setInvalid(false);
        (*SGWVesicleCustomisationPage::membraneTransparencyError).setItemVisibility(false);
    }
}

void SGWVesicleCustomisationPage::centerTransparencyCheck(SGWInput */*unused*/){
    bool isValid = false;
    (void)(*SGWVesicleCustomisationPage::centerTransparencyInput).getTextAsFloat(&isValid, 0.0f, 1.0f);
    if(isValid == false){
        (*SGWVesicleCustomisationPage::centerTransparencyInput).setInvalid(true);
        (*SGWVesicleCustomisationPage::centerTransparencyError).setItemVisibility(true);
    }
    else{
        (*SGWVesicleCustomisationPage::centerTransparencyInput).setInvalid(false);
        (*SGWVesicleCustomisationPage::centerTransparencyError).setItemVisibility(false);
    }
}

void SGWVesicleCustomisationPage::edgeTransparencyCheck(SGWInput */*unused*/){
    bool isValid = false;
    (void)(*SGWVesicleCustomisationPage::edgeTransparencyInput).getTextAsFloat(&isValid, 0.0f, 1.0f);
    if(isValid == false){
        (*SGWVesicleCustomisationPage::edgeTransparencyInput).setInvalid(true);
        (*SGWVesicleCustomisationPage::edgeTransparencyError).setItemVisibility(true);
    }
    else{
        (*SGWVesicleCustomisationPage::edgeTransparencyInput).setInvalid(false);
        (*SGWVesicleCustomisationPage::edgeTransparencyError).setItemVisibility(false);
    }
}

void SGWVesicleCustomisationPage::frameRateCheck(SGWInput */*unused*/){
    bool isValid = false;
    (void)(*SGWVesicleCustomisationPage::frameRateInput).getTextAsFloat(&isValid, std::numeric_limits<float>::denorm_min(), std::numeric_limits<float>::infinity());
    if(isValid == false){
        (*SGWVesicleCustomisationPage::frameRateInput).setInvalid(true);
        (*SGWVesicleCustomisationPage::frameRateError).setItemVisibility(true);
    }
    else{
        (*SGWVesicleCustomisationPage::frameRateInput).setInvalid(false);
        (*SGWVesicleCustomisationPage::frameRateError).setItemVisibility(false);
    }
}
