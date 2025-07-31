#include "sgxvesiclepropertiespage.h"
#include <QQuickItem>
#include "../quickui/sgxquickuiinterface.h"
#include "../primitives/sgxcolourrgba.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include "../customisation/sgxvesiclespropertiescustomisation.h"
#include <QString>

QQuickItem* SGXVesiclePropertiesPage::instance = nullptr;
QQuickItem* SGXVesiclePropertiesPage::membraneColourInput = nullptr;
QQuickItem* SGXVesiclePropertiesPage::contentsColourInput = nullptr;
QQuickItem* SGXVesiclePropertiesPage::membraneThicknessInput = nullptr;
QQuickItem* SGXVesiclePropertiesPage::maximumCenterDistanceInput = nullptr;
QQuickItem* SGXVesiclePropertiesPage::maximumVelocityInput = nullptr;
QQuickItem* SGXVesiclePropertiesPage::maximumAccelerationInput = nullptr;
QQuickItem* SGXVesiclePropertiesPage::maximumRadiusChangeInput = nullptr;
QQuickItem* SGXVesiclePropertiesPage::maximumRadiusInput = nullptr;
QQuickItem* SGXVesiclePropertiesPage::minimumRadiusInput = nullptr;
QQuickItem* SGXVesiclePropertiesPage::maximumRadiusOffsetInput = nullptr;
QQuickItem* SGXVesiclePropertiesPage::maximumRadiusOffsetChangeInput = nullptr;
QQuickItem* SGXVesiclePropertiesPage::membraneTransparencyInput = nullptr;
QQuickItem* SGXVesiclePropertiesPage::centerTransparencyInput = nullptr;
QQuickItem* SGXVesiclePropertiesPage::edgeTransparencyInput = nullptr;
QQuickItem* SGXVesiclePropertiesPage::frameRateInput = nullptr;
QQuickItem* SGXVesiclePropertiesPage::confirmDialog = nullptr;

void SGXVesiclePropertiesPage::activate(){
    SGXQuickUIInterface::showPage(SGXVesiclePropertiesPage::instance, &SGXVesiclePropertiesPage::initialise, &SGXVesiclePropertiesPage::initialiseInputFields);
}

QQuickItem* SGXVesiclePropertiesPage::initialise(){
    SGXVesiclePropertiesPage::instance = SGXQuickUIInterface::createScrollView(SGXQuickUIInterface::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 28.0f, 0.0f, 0.5f, 8, false);
    SGXQuickUIInterface::createTitle(SGXVesiclePropertiesPage::instance, "Vesicle Properties", 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.5f, 0.0f, 2.0f);
    SGXQuickUIInterface::createTextButton(SGXVesiclePropertiesPage::instance, "exit", &SGXVesiclePropertiesPage::exitPage, 1.0f, -3.0f, 0.0f, 0.5f, 0.0f, 2.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createRightText(SGXVesiclePropertiesPage::instance, "membrane colour:", 0.0f, 0.5f, 0.0f, 3.0f, 0.5f, -0.6f, 0.0f, 1.0f);
    SGXVesiclePropertiesPage::membraneColourInput = SGXQuickUIInterface::createColourPicker(SGXVesiclePropertiesPage::instance, 0.5f, 0.1f, 0.0f, 3.0f, 0.0f, 4.0f, 0.0f, 1.0f, SGXColourRGBA(255, 0, 200));
    SGXQuickUIInterface::createRightText(SGXVesiclePropertiesPage::instance, "membrane colour:", 0.0f, 0.5f, 0.0f, 4.5f, 0.5f, -0.6f, 0.0f, 1.0f);
    SGXVesiclePropertiesPage::contentsColourInput = SGXQuickUIInterface::createColourPicker(SGXVesiclePropertiesPage::instance, 0.5f, 0.1f, 0.0f, 4.5f, 0.0f, 4.0f, 0.0f, 1.0f, SGXColourRGBA(255, 0, 200));
    SGXQuickUIInterface::createRightText(SGXVesiclePropertiesPage::instance, "membrane thickness:", 0.0f, 0.5f, 0.0f, 6.0f, 0.5f, -0.6f, 0.0f, 1.0f);
    SGXVesiclePropertiesPage::membraneThicknessInput =  SGXQuickUIInterface::createInputField(SGXVesiclePropertiesPage::instance, 0.5f, 0.1f, 0.0f, 6.0f, 0.0f, 4.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createRightText(SGXVesiclePropertiesPage::instance, "distance from center:", 0.0f, 0.5f, 0.0f, 7.5f, 0.5f, -0.6f, 0.0f, 1.0f);
    SGXVesiclePropertiesPage::maximumCenterDistanceInput =  SGXQuickUIInterface::createInputField(SGXVesiclePropertiesPage::instance, 0.5f, 0.1f, 0.0f, 7.5f, 0.0f, 4.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createRightText(SGXVesiclePropertiesPage::instance, "maximum velocity:", 0.0f, 0.5f, 0.0f, 9.0f, 0.5f, -0.6f, 0.0f, 1.0f);
    SGXVesiclePropertiesPage::maximumVelocityInput =  SGXQuickUIInterface::createInputField(SGXVesiclePropertiesPage::instance, 0.5f, 0.1f, 0.0f, 9.0f, 0.0f, 4.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createRightText(SGXVesiclePropertiesPage::instance, "maximum acceleration:", 0.0f, 0.5f, 0.0f, 10.5f, 0.5f, -0.6f, 0.0f, 1.0f);
    SGXVesiclePropertiesPage::maximumAccelerationInput =  SGXQuickUIInterface::createInputField(SGXVesiclePropertiesPage::instance, 0.5f, 0.1f, 0.0f, 10.5f, 0.0f, 4.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createRightText(SGXVesiclePropertiesPage::instance, "maximum radius change:", 0.0f, 0.5f, 0.0f, 12.0f, 0.5f, -0.6f, 0.0f, 1.0f);
    SGXVesiclePropertiesPage::maximumRadiusChangeInput =  SGXQuickUIInterface::createInputField(SGXVesiclePropertiesPage::instance, 0.5f, 0.1f, 0.0f, 12.0f, 0.0f, 4.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createRightText(SGXVesiclePropertiesPage::instance, "maximum radius:", 0.0f, 0.5f, 0.0f, 13.5f, 0.5f, -0.6f, 0.0f, 1.0f);
    SGXVesiclePropertiesPage::maximumRadiusInput =  SGXQuickUIInterface::createInputField(SGXVesiclePropertiesPage::instance, 0.5f, 0.1f, 0.0f, 13.5f, 0.0f, 4.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createRightText(SGXVesiclePropertiesPage::instance, "minimum radius:", 0.0f, 0.5f, 0.0f, 15.0f, 0.5f, -0.6f, 0.0f, 1.0f);
    SGXVesiclePropertiesPage::minimumRadiusInput =  SGXQuickUIInterface::createInputField(SGXVesiclePropertiesPage::instance, 0.5f, 0.1f, 0.0f, 15.0f, 0.0f, 4.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createRightText(SGXVesiclePropertiesPage::instance, "maximum radius offset change:", 0.0f, 0.5f, 0.0f, 16.5f, 0.5f, -0.6f, 0.0f, 1.0f);
    SGXVesiclePropertiesPage::maximumRadiusOffsetChangeInput =  SGXQuickUIInterface::createInputField(SGXVesiclePropertiesPage::instance, 0.5f, 0.1f, 0.0f, 16.5f, 0.0f, 4.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createRightText(SGXVesiclePropertiesPage::instance, "maximum radius offset:", 0.0f, 0.5f, 0.0f, 18.0f, 0.5f, -0.6f, 0.0f, 1.0f);
    SGXVesiclePropertiesPage::maximumRadiusOffsetInput =  SGXQuickUIInterface::createInputField(SGXVesiclePropertiesPage::instance, 0.5f, 0.1f, 0.0f, 18.0f, 0.0f, 4.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createRightText(SGXVesiclePropertiesPage::instance, "membrane transparency:", 0.0f, 0.5f, 0.0f, 19.5f, 0.5f, -0.6f, 0.0f, 1.0f);
    SGXVesiclePropertiesPage::membraneTransparencyInput =  SGXQuickUIInterface::createInputField(SGXVesiclePropertiesPage::instance, 0.5f, 0.1f, 0.0f, 19.5f, 0.0f, 4.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createRightText(SGXVesiclePropertiesPage::instance, "center transparency:", 0.0f, 0.5f, 0.0f, 21.0f, 0.5f, -0.6f, 0.0f, 1.0f);
    SGXVesiclePropertiesPage::centerTransparencyInput =  SGXQuickUIInterface::createInputField(SGXVesiclePropertiesPage::instance, 0.5f, 0.1f, 0.0f, 21.0f, 0.0f, 4.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createRightText(SGXVesiclePropertiesPage::instance, "edge transparency:", 0.0f, 0.5f, 0.0f, 22.5f, 0.5f, -0.6f, 0.0f, 1.0f);
    SGXVesiclePropertiesPage::edgeTransparencyInput =  SGXQuickUIInterface::createInputField(SGXVesiclePropertiesPage::instance, 0.5f, 0.1f, 0.0f, 22.5f, 0.0f, 4.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createRightText(SGXVesiclePropertiesPage::instance, "frame rate:", 0.0f, 0.5f, 0.0f, 24.0f, 0.5f, -0.6f, 0.0f, 1.0f);
    SGXVesiclePropertiesPage::frameRateInput =  SGXQuickUIInterface::createInputField(SGXVesiclePropertiesPage::instance, 0.5f, 0.1f, 0.0f, 24.0f, 0.0f, 4.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createTextButton(SGXVesiclePropertiesPage::instance, "update", &SGXVesiclePropertiesPage::activateConfirmDialog, 0.5f, -2.5f, 0.0f, 25.5f, 0.0f, 5.0f, 0.0f, 1.0f);
    return SGXVesiclePropertiesPage::instance;
}

void SGXVesiclePropertiesPage::initialiseInputFields(){
    SGXQuickUIInterface::setColourPickerColour(SGXVesiclePropertiesPage::membraneColourInput, SGUCentralManagement::cuteVesiclesMembraneColour);
    SGXQuickUIInterface::setColourPickerColour(SGXVesiclePropertiesPage::contentsColourInput, SGUCentralManagement::cuteVesiclesContentsColour);
    SGXQuickUIInterface::setInputFieldDataUsingFloat(SGXVesiclePropertiesPage::membraneThicknessInput, SGUCentralManagement::cuteVesiclesMembraneThickness);
    SGXQuickUIInterface::setInputFieldDataUsingFloat(SGXVesiclePropertiesPage::maximumCenterDistanceInput, SGUCentralManagement::cuteVesiclesMaximumCenterDistance);
    SGXQuickUIInterface::setInputFieldDataUsingFloat(SGXVesiclePropertiesPage::maximumVelocityInput, SGUCentralManagement::cuteVesiclesMaximumVelocity);
    SGXQuickUIInterface::setInputFieldDataUsingFloat(SGXVesiclePropertiesPage::maximumAccelerationInput, SGUCentralManagement::cuteVesiclesMaximumAcceleration);
    SGXQuickUIInterface::setInputFieldDataUsingFloat(SGXVesiclePropertiesPage::maximumRadiusChangeInput, SGUCentralManagement::cuteVesiclesMaximumRadiusChange);
    SGXQuickUIInterface::setInputFieldDataUsingFloat(SGXVesiclePropertiesPage::maximumRadiusInput, SGUCentralManagement::cuteVesiclesMaximumRadius);
    SGXQuickUIInterface::setInputFieldDataUsingFloat(SGXVesiclePropertiesPage::minimumRadiusInput, SGUCentralManagement::cuteVesiclesMinimumRadius);
    SGXQuickUIInterface::setInputFieldDataUsingFloat(SGXVesiclePropertiesPage::maximumRadiusOffsetInput, SGUCentralManagement::cuteVesiclesMaximumRadiusOffset);
    SGXQuickUIInterface::setInputFieldDataUsingFloat(SGXVesiclePropertiesPage::maximumRadiusOffsetChangeInput, SGUCentralManagement::cuteVesiclesMaximumRadiusOffsetChange);
    SGXQuickUIInterface::setInputFieldDataUsingFloat(SGXVesiclePropertiesPage::membraneTransparencyInput, SGUCentralManagement::cuteVesiclesMembraneTransparency);
    SGXQuickUIInterface::setInputFieldDataUsingFloat(SGXVesiclePropertiesPage::centerTransparencyInput, SGUCentralManagement::cuteVesiclesCenterTransparency);
    SGXQuickUIInterface::setInputFieldDataUsingFloat(SGXVesiclePropertiesPage::edgeTransparencyInput, SGUCentralManagement::cuteVesiclesEdgeTransparency);
    SGXQuickUIInterface::setInputFieldDataUsingFloat(SGXVesiclePropertiesPage::frameRateInput, SGUCentralManagement::cuteVesiclesFrameRate);
}

void SGXVesiclePropertiesPage::setVesicleProperties(){
    bool isOk = false;
    SGXColourRGBA col = SGXQuickUIInterface::getColourPickerColour(SGXVesiclePropertiesPage::membraneColourInput, isOk);
    col.setTransparency(255);
    SGUCentralManagement::cuteVesiclesMembraneColour = col;
    col = SGXQuickUIInterface::getColourPickerColour(SGXVesiclePropertiesPage::contentsColourInput, isOk);
    col.setTransparency(255);
    SGUCentralManagement::cuteVesiclesContentsColour = col;
    float x = SGXQuickUIInterface::getInputFieldDataAsFloat(SGXVesiclePropertiesPage::membraneThicknessInput, isOk);
    if(isOk == true){SGUCentralManagement::cuteVesiclesMembraneThickness = x;}
    x = SGXQuickUIInterface::getInputFieldDataAsFloat(SGXVesiclePropertiesPage::maximumCenterDistanceInput, isOk);
    if(isOk == true){SGUCentralManagement::cuteVesiclesMaximumCenterDistance = x;}
    x = SGXQuickUIInterface::getInputFieldDataAsFloat(SGXVesiclePropertiesPage::maximumVelocityInput, isOk);
    if(isOk == true){SGUCentralManagement::cuteVesiclesMaximumVelocity = x;}
    x = SGXQuickUIInterface::getInputFieldDataAsFloat(SGXVesiclePropertiesPage::maximumAccelerationInput, isOk);
    if(isOk == true){SGUCentralManagement::cuteVesiclesMaximumAcceleration = x;}
    x = SGXQuickUIInterface::getInputFieldDataAsFloat(SGXVesiclePropertiesPage::maximumRadiusChangeInput, isOk);
    if(isOk == true){SGUCentralManagement::cuteVesiclesMaximumRadiusChange = x;}
    x = SGXQuickUIInterface::getInputFieldDataAsFloat(SGXVesiclePropertiesPage::maximumRadiusInput, isOk);
    if(isOk == true){SGUCentralManagement::cuteVesiclesMaximumRadius = x;}
    x = SGXQuickUIInterface::getInputFieldDataAsFloat(SGXVesiclePropertiesPage::minimumRadiusInput, isOk);
    if(isOk == true){SGUCentralManagement::cuteVesiclesMinimumRadius = x;}
    x = SGXQuickUIInterface::getInputFieldDataAsFloat(SGXVesiclePropertiesPage::maximumRadiusOffsetInput, isOk);
    if(isOk == true){SGUCentralManagement::cuteVesiclesMaximumRadiusOffset = x;}
    x = SGXQuickUIInterface::getInputFieldDataAsFloat(SGXVesiclePropertiesPage::maximumRadiusOffsetChangeInput, isOk);
    if(isOk == true){SGUCentralManagement::cuteVesiclesMaximumRadiusOffsetChange = x;}
    x = SGXQuickUIInterface::getInputFieldDataAsFloat(SGXVesiclePropertiesPage::membraneTransparencyInput, isOk);
    if(isOk == true){SGUCentralManagement::cuteVesiclesMembraneTransparency = x;}
    x = SGXQuickUIInterface::getInputFieldDataAsFloat(SGXVesiclePropertiesPage::centerTransparencyInput, isOk);
    if(isOk == true){SGUCentralManagement::cuteVesiclesCenterTransparency = x;}
    x = SGXQuickUIInterface::getInputFieldDataAsFloat(SGXVesiclePropertiesPage::edgeTransparencyInput, isOk);
    if(isOk == true){SGUCentralManagement::cuteVesiclesEdgeTransparency = x;}
    x = SGXQuickUIInterface::getInputFieldDataAsFloat(SGXVesiclePropertiesPage::frameRateInput, isOk);
    if(isOk == true){SGUCentralManagement::cuteVesiclesFrameRate = x;}
    SGXVesiclesPropertiesCustomisation::syncVesicleProperties();
    SGXQuickUIInterface::hidePage(SGXVesiclePropertiesPage::confirmDialog);
    SGXQuickUIInterface::hidePage(SGXVesiclePropertiesPage::instance);
}

void SGXVesiclePropertiesPage::cancelChange(){
    SGXQuickUIInterface::hidePage(SGXVesiclePropertiesPage::confirmDialog);
}

QQuickItem* SGXVesiclePropertiesPage::initialiseConfirmDialog(){
    SGXVesiclePropertiesPage::confirmDialog =  SGXQuickUIInterface::createWidget(SGXQuickUIInterface::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 6, false);
    const QString s = "By pressing \"confirm\" below, you will change the vesicle properties to match what you have selected. You will have to restart the application for them to be applied. Also note that the National Day theme change takes priority over custom themes, so vesicle colours is locked at red and white during the National Day period, because vesicles need to wear red and white to celebrate too. Usually, vesicle properties take priority over theme colours, so you can use a builtin theme with different colours for vesicle membrane or contents.";
    SGXQuickUIInterface::createLongText(SGXVesiclePropertiesPage::confirmDialog, s, 0.5f, -5.0f, 0.5f, -5.0f, 0.0f, 10.0f, 0.0f, 9.0f, 0.0f, 1.0f, 0.0f, 0.5f);
    SGXQuickUIInterface::createTextButton(SGXVesiclePropertiesPage::confirmDialog, "cancel", &SGXVesiclePropertiesPage::cancelChange, 0.5f, -5.0f, 0.5f, 4.0f, 0.0f, 5.0f, 0.0f, 1.0f);
    SGXQuickUIInterface::createTextButton(SGXVesiclePropertiesPage::confirmDialog, "confirm", &SGXVesiclePropertiesPage::setVesicleProperties, 0.5f, 0.0f, 0.5f, 4.0f, 0.0f, 5.0f, 0.0f, 1.0f);
    return SGXVesiclePropertiesPage::confirmDialog;
}

void SGXVesiclePropertiesPage::activateConfirmDialog(){
    SGXQuickUIInterface::showPage(SGXVesiclePropertiesPage::confirmDialog, &SGXVesiclePropertiesPage::initialiseConfirmDialog, &SGXQuickUIInterface::doNothing);
}

void SGXVesiclePropertiesPage::exitPage(){
    SGXQuickUIInterface::hidePage(SGXVesiclePropertiesPage::instance);
}
