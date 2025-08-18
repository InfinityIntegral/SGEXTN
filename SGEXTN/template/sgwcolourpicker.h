#ifndef SGWCOLOURPICKER_H
#define SGWCOLOURPICKER_H

#include <QObject>
#include "../widgets/noninstantiable/sgwbackground.h"
#include "../primitives/sgxcolourrgba.h"
#include "../primitives/sgxcolourhsla.h"
#include <qtmetamacros.h>
#include "../colourpickerrendering/huechoice/sgxrendercolourpickerhuechoicesgwidget.h"
#include "../widgets/instantiable/sgwtouchreceiver.h"
#include <array>
#include "../primitives/sgxtouchevent.h"
#include "../colourpickerrendering/saturationchoice/sgxrendercolourpickersaturationchoicesgwidget.h"
#include "../colourpickerrendering/lightnesschoice/sgxrendercolourpickerlightnesschoicesgwidget.h"
#include "../colourpickerrendering/transparencychoice/sgxrendercolourpickertransparencychoicesgwidget.h"
#include "../widgets/noninstantiable/sgwinput.h"
#include "../colourbackground/sgxrendercolourbackgroundsgwidget.h"
#include "../widgets/instantiable/sgwcolourpickerwidget.h"
#include "../widgets/noninstantiable/sgwbutton.h"

class SGWColourPicker : public QObject
{
    Q_OBJECT
public:
    SGWColourPicker() = delete;
    static SGWBackground* instance;
    static SGXColourRGBA colour;
    static SGXColourHSLA colourHSLA;
    static SGWBackground* initialise();
    static void reset();
    static void activate();
    static SGXRenderColourPickerHueChoiceSGWidget* hueChoice;
    static void updateUsingColour();
    static void updateUsingColourHSLA();
    static void updateInputs();
    static SGWTouchReceiver* hueTouchReceiver;
    static void updateHue(SGWTouchReceiver* /*unused*/, const std::array<SGXTouchEvent, 5>& t);
    static SGXRenderColourPickerSaturationChoiceSGWidget* saturationChoice;
    static SGWTouchReceiver* saturationTouchReceiver;
    static void updateSaturation(SGWTouchReceiver* /*unused*/, const std::array<SGXTouchEvent, 5>& t);
    static SGXRenderColourPickerLightnessChoiceSGWidget* lightnessChoice;
    static SGWTouchReceiver* lightnessTouchReceiver;
    static void updateLightness(SGWTouchReceiver* /*unused*/, const std::array<SGXTouchEvent, 5>& t);
    static SGXRenderColourPickerTransparencyChoiceSGWidget* transparencyChoice;
    static SGWTouchReceiver* transparencyTouchReceiver;
    static void updateTransparency(SGWTouchReceiver* /*unused*/, const std::array<SGXTouchEvent, 5>& t);
    static SGWInput* redInput;
    static void updateRed(SGWInput* /*unused*/);
    static SGWInput* greenInput;
    static void updateGreen(SGWInput* /*unused*/);
    static SGWInput* blueInput;
    static void updateBlue(SGWInput* /*unused*/);
    static SGWInput* transparencyInput;
    static void updateTransparencyFromInput(SGWInput* /*unused*/);
    static SGWInput* hexCodeInput;
    static void updateHexCode(SGWInput* /*unused*/);
    static SGXRenderColourBackgroundSGWidget* colourDisplay;
    static bool ignoreInputChanges;
    static SGWColourPickerWidget* colourReceiver;
    static void activateColourPicker(SGWColourPickerWidget* x);
    static void completeColourSelection(SGWButton* /*unused*/);
    static SGWButton* completeButton;
};

#endif // SGWCOLOURPICKER_H
