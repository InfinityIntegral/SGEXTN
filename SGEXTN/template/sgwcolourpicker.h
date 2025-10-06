#ifndef SGWCOLOURPICKER_H
#define SGWCOLOURPICKER_H

#include "../primitives/sgxcolourrgba.h"
#include "../primitives/sgxcolourhsla.h"

class SGWBackground;
class SGXRenderColourPickerHueChoiceSGWidget;
class SGXRenderColourPickerSaturationChoiceSGWidget;
class SGXRenderColourPickerLightnessChoiceSGWidget;
class SGXRenderColourPickerTransparencyChoiceSGWidget;
class SGXRenderColourBackgroundSGWidget;
class SGWSingleTouchReceiver;
class SGWInput;
class SGWColourPickerWidget;
class SGWButton;
class SGXTouchEvent;
class SGWColourPicker
{
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
    static SGWSingleTouchReceiver* hueTouchReceiver;
    static void updateHue(const SGXTouchEvent& t);
    static SGXRenderColourPickerSaturationChoiceSGWidget* saturationChoice;
    static SGWSingleTouchReceiver* saturationTouchReceiver;
    static void updateSaturation(const SGXTouchEvent& t);
    static SGXRenderColourPickerLightnessChoiceSGWidget* lightnessChoice;
    static SGWSingleTouchReceiver* lightnessTouchReceiver;
    static void updateLightness(const SGXTouchEvent& t);
    static SGXRenderColourPickerTransparencyChoiceSGWidget* transparencyChoice;
    static SGWSingleTouchReceiver* transparencyTouchReceiver;
    static void updateTransparency(const SGXTouchEvent& t);
    static SGWInput* redInput;
    static void updateRed();
    static SGWInput* greenInput;
    static void updateGreen();
    static SGWInput* blueInput;
    static void updateBlue();
    static SGWInput* transparencyInput;
    static void updateTransparencyFromInput();
    static SGWInput* hexCodeInput;
    static void updateHexCode();
    static SGXRenderColourBackgroundSGWidget* colourDisplay;
    static bool ignoreInputChanges;
    static SGWColourPickerWidget* colourReceiver;
    static void activateColourPicker(SGWColourPickerWidget* x);
    static void completeColourSelection();
    static SGWButton* completeButton;
};

#endif // SGWCOLOURPICKER_H
