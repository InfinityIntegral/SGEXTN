#include "sgwvesiclecustomisationpage.h"
#include "../widgets/sgwbackground.h"
#include "../widgets/sgwinput.h"
#include "../widgets/sgwpagebackground.h"
#include "../widgets/sgwsequentialscrollview.h"
#include "../widgets/sgwtextbutton.h"
#include "../widgets/sgwblankwidget.h"
#include "../widgets/sgwtextlabel.h"
#include "../widgets/sgwsequentiallonglabel.h"
#include "../widgets/sgwtextinput.h"
#include "../widgets/sgwwidget.h"
#include <QString>
#include "../widgets/sgwhorizontalalignment.h"
#include "../widgets/sgwbutton.h"
#include "../widgets/sgwlabel.h"

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
    SGWVesicleCustomisationPage::instance = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0, 0.0f, 8, false);
    SGWWidget* bg = new SGWSequentialScrollView(SGWVesicleCustomisationPage::instance, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f, 8, false);
    new SGWTextButton(SGWVesicleCustomisationPage::instance, "cancel", &SGWVesicleCustomisationPage::cancelChange, 0.0f, 0.0f, 1.0f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    new SGWTextButton(SGWVesicleCustomisationPage::instance, "confirm", &SGWVesicleCustomisationPage::confirmChange, 0.5f, 0.0f, 1.0f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    SGWWidget* p = nullptr;
    QString s = "";
    
    new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 8);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 3.0f, 8);
    new SGWTextLabel(p, "customise vesicles", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 2.0f, SGWHorizontalAlignment::Center);
    s = "Note: a vesicle is an organelle found inside cells that transport substances.";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 8);
    
    s = "In the settings below, 1 \"unit\" of distance will refer to half the width of the animation screen.";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 8);
    
    s = "    The membrane thickness refers to the thickness of the vesicle membrane and has a default value of 0.05";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "membrane thickness:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWVesicleCustomisationPage::membraneThicknessInput = new SGWTextInput(p, nullptr, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::membraneThicknessError = new SGWTextLabel(p, "nonnegative number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left);
    (*SGWVesicleCustomisationPage::membraneThicknessError).setItemVisibility(false);
    
    s = "    Center distance is the maximum distance that the center of a vesicle can be from the center of the screen on either the x or the y direction. Once that is exceeded, the vesicle reappears on the other side of the screen, keeping its size and shape. This has a default value of 1.5";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "center distance:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWVesicleCustomisationPage::maximumCenterDistanceInput = new SGWTextInput(p, nullptr, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::maximumCenterDistanceError = new SGWTextLabel(p, "nonnegative number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left);
    (*SGWVesicleCustomisationPage::maximumCenterDistanceError).setItemVisibility(false);
    
    s = "    The maximum velocity controls the maximum speed of vesicles in units per second. Setting this too high may be distracting. This has a default value of 0.01";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "maximum velocity:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWVesicleCustomisationPage::maximumVelocityInput = new SGWTextInput(p, nullptr, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::maximumVelocityError = new SGWTextLabel(p, "nonnegative number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left);
    (*SGWVesicleCustomisationPage::maximumVelocityError).setItemVisibility(false);
    
    s = "    The maximum acceleration controls the maximum change in speed of vesicles in units per second per second. This has a default value of 0.01";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "max. acceleration:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWVesicleCustomisationPage::maximumAccelerationInput = new SGWTextInput(p, nullptr, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::maximumAccelerationError = new SGWTextLabel(p, "nonnegative number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left);
    (*SGWVesicleCustomisationPage::maximumAccelerationError).setItemVisibility(false);
    
    s = "    The maximum radius change controls by how much vesicles can become bigger or smaller in each second. Setting this too high may be distracting. This has a default value of 0.01";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "max. radius change:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWVesicleCustomisationPage::maximumRadiusChangeInput = new SGWTextInput(p, nullptr, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::maximumRadiusChangeError = new SGWTextLabel(p, "nonnegative number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left);
    (*SGWVesicleCustomisationPage::maximumRadiusChangeError).setItemVisibility(false);
    
    s = "    The minimum radius controls the smallest possible radius that a vesicle can have. Setting this too small will make small vesicles invisible. The default value for this setting is 0.1";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "minimum radius:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWVesicleCustomisationPage::minimumRadiusInput = new SGWTextInput(p, nullptr, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::minimumRadiusError = new SGWTextLabel(p, "nonnegative number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left);
    (*SGWVesicleCustomisationPage::minimumRadiusError).setItemVisibility(false);
    
    s = "    The maximum radius controls the largest possible radius that a vesicle can have. The default value is 0.35";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "maximum radius:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWVesicleCustomisationPage::maximumRadiusInput = new SGWTextInput(p, nullptr, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::maximumRadiusError = new SGWTextLabel(p, "nonnegative number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left);
    (*SGWVesicleCustomisationPage::maximumRadiusError).setItemVisibility(false);
    
    s = "    The maximum offset, or maximum radius offset, determines how much the radius of a vesicle at a certain point can deviate from the base radius as a proportion of the base radius. This controls how irregularly shaped the vesicles are. This has a default value of 0.1";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "maximum offset:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWVesicleCustomisationPage::maximumRadiusOffsetInput = new SGWTextInput(p, nullptr, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::maximumRadiusOffsetError = new SGWTextLabel(p, "nonnegative number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left);
    (*SGWVesicleCustomisationPage::maximumRadiusOffsetError).setItemVisibility(false);
    
    s = "    The maximum offset change controls the maximum change in offset at any point on any vesicle. The default value for this is 0.1";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "max. offset change:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWVesicleCustomisationPage::maximumRadiusOffsetChangeInput = new SGWTextInput(p, nullptr, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::maximumRadiusOffsetChangeError = new SGWTextLabel(p, "nonnegative number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left);
    (*SGWVesicleCustomisationPage::maximumRadiusOffsetChangeError).setItemVisibility(false);
    
    s = "    The membrane transparency controls the transparency of the vesicle membrane with 0 being fully transparent and 1 being fully opaque. The default value for this is 0.2";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "membrane transparency:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWVesicleCustomisationPage::membraneTransparencyInput = new SGWTextInput(p, nullptr, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::membraneTransparencyError = new SGWTextLabel(p, "number between 0 and 1", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left);
    (*SGWVesicleCustomisationPage::membraneTransparencyError).setItemVisibility(false);
    
    s = "    The center transparency controls the transparency of vesicles at the center. The transparency of vesicle contents forms a gradient from center to edge. The default value of this is 0.1";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "center transparency:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWVesicleCustomisationPage::centerTransparencyInput = new SGWTextInput(p, nullptr, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::centerTransparencyError = new SGWTextLabel(p, "number between 0 and 1", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left);
    (*SGWVesicleCustomisationPage::centerTransparencyError).setItemVisibility(false);
    
    s = "    The edge transparency controls the transparency of vesicles at the edge of the contents region where it meets the membrane. The transparency of vesicle contents forms a gradient from center to edge. The default value of this is 0.05";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "edge transparency:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWVesicleCustomisationPage::edgeTransparencyInput = new SGWTextInput(p, nullptr, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::edgeTransparencyError = new SGWTextLabel(p, "number between 0 and 1", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left);
    (*SGWVesicleCustomisationPage::edgeTransparencyError).setItemVisibility(false);
    
    s = "    This determines the frame rate of the animation in frames per second. Setting the frame rate too high can increase battery usage and setting the frame rate too low can lead to the animation being distracting. You are recommended to set the frame rate around the default frame rate of 10. Note that the frame rate does not need to be an integer.";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 8);
    new SGWTextLabel(p, "frame rate:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWVesicleCustomisationPage::frameRateInput = new SGWTextInput(p, nullptr, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    SGWVesicleCustomisationPage::frameRateError = new SGWTextLabel(p, "positive number", 0.5f, 0.1f, 0.0f, 1.0f, 0.5f, -0.6f, 0.0f, 0.75f, SGWHorizontalAlignment::Left);
    (*SGWVesicleCustomisationPage::frameRateError).setItemVisibility(false);
    
    return SGWVesicleCustomisationPage::instance;
}

void SGWVesicleCustomisationPage::reset(){
    
}

void SGWVesicleCustomisationPage::cancelChange(SGWButton */*unused*/){
    
}

void SGWVesicleCustomisationPage::confirmChange(SGWButton */*unused*/){
    
}
