#include "sgxvesiclepropertiespage.h"
#include <QQuickItem>
#include "../quickui/sgxquickuiinterface.h"
#include "../primitives/sgxcolourrgba.h"

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

void SGXVesiclePropertiesPage::activate(){
    if(SGXVesiclePropertiesPage::instance == nullptr){SGXVesiclePropertiesPage::initialise();}
    (*SGXVesiclePropertiesPage::instance).setVisible(true);
}

void SGXVesiclePropertiesPage::initialise(){
    SGXVesiclePropertiesPage::instance = SGXQuickUIInterface::createScrollView(SGXQuickUIInterface::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 26.5f, 0.0f, 0.5f, 8);
    SGXQuickUIInterface::createTitle(SGXVesiclePropertiesPage::instance, "Vesicle Properties", 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.5f, 0.0f, 2.0f);
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
}
