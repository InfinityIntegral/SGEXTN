#include "sgwvesiclecustomisationpage.h"
#include "../widgets/sgwbackground.h"
#include "../widgets/sgwcolourpickerwidget.h"
#include "../widgets/sgwinput.h"
#include "../widgets/sgwpagebackground.h"
#include "../widgets/sgwsequentialscrollview.h"
#include "../widgets/sgwtextbutton.h"
#include "../widgets/sgwblankwidget.h"
#include "../widgets/sgwtextlabel.h"
#include "../widgets/sgwsequentiallonglabel.h"
#include "../widgets/sgwtextinput.h"

SGWBackground* SGWVesicleCustomisationPage::instance = nullptr;
SGWColourPickerWidget* SGWVesicleCustomisationPage::membraneColourInput = nullptr;
SGWColourPickerWidget* SGWVesicleCustomisationPage::contentsColourInput = nullptr;
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
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.5f, 8);
    new SGWTextLabel(p, "customise vesicles", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 2.0f, SGWHorizontalAlignment::Center);
    s = "Note: a vesicle is an organelle found inside cells that transport substances.";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 8);
    
    s = "    The membrane colour determines the colour used to draw vesicle membranes, which are the outermost layer of vesicles. The transparency is ignored as vesicle transparency is set separately below. During the National Day period, this colour is locked at Singapore red to celebrate.";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.5f, 8);
    new SGWTextLabel(p, "membrane colour:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWVesicleCustomisationPage::membraneColourInput = new SGWColourPickerWidget(p, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f, SGXColourRGBA(255, 0, 200));
    
    s = "    The contents colour determines the colour of the fluid inside the vesicles. Similar to the membrane colour, the transparency is set separately. During the National Day period, this colour is locked at Singapore white.";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.5f, 8);
    new SGWTextLabel(p, "contents colour:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWVesicleCustomisationPage::contentsColourInput = new SGWColourPickerWidget(p, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f, SGXColourRGBA(255, 255, 255));
    
    s = "The settings below will have a unit of distance equivalent to half the width of the animation screen.";
    new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 8);
    
    s = "    The membrane thickness refers to the thickness of the vesicle membrane and has a default value of 0.05";
    new SGWSequentialLongLabel(bg, s, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    p = new SGWBlankWidget(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.5f, 8);
    new SGWTextLabel(p, "membrane thickness:", 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, -0.6f, 0.0f, 1.0f, SGWHorizontalAlignment::Right);
    SGWVesicleCustomisationPage::membraneThicknessInput = new SGWTextInput(p, nullptr, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 3.0f, 0.0f, 1.0f);
    
    return SGWVesicleCustomisationPage::instance;
}

void SGWVesicleCustomisationPage::reset(){
    
}

void SGWVesicleCustomisationPage::cancelChange(SGWButton */*unused*/){
    
}

void SGWVesicleCustomisationPage::confirmChange(SGWButton */*unused*/){
    
}
