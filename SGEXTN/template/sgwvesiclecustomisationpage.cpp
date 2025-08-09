#include "sgwvesiclecustomisationpage.h"
#include "../widgets/sgwbackground.h"
#include "../widgets/sgwcolourpickerwidget.h"
#include "../widgets/sgwinput.h"

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
SGWBackground* SGWVesicleCustomisationPage::confirmDialogInstance = nullptr;

void SGWVesicleCustomisationPage::activate(){
    
}

SGWBackground* SGWVesicleCustomisationPage::initialise(){
    return nullptr;
}

void SGWVesicleCustomisationPage::reset(){
    
}

SGWBackground* SGWVesicleCustomisationPage::initialiseConfirmDialog(){
    return nullptr;
}

void SGWVesicleCustomisationPage::confirmChange(){
    
}

void SGWVesicleCustomisationPage::activateConfirmDialog(){
    
}

void SGWVesicleCustomisationPage::cancelChange(){
    
}

void SGWVesicleCustomisationPage::cancelConfirmDialog(){
    
}
