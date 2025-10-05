#ifndef SGWCOLOURPICKER_H
#define SGWCOLOURPICKER_H

#include "../primitives/sgxcolourrgba.h"
#include "../primitives/sgxcolourhsla.h"

template <typename T> class SGLArray;
class SGWBackground;
class SGXRenderColourPickerHueChoiceSGWidget;
class SGXRenderColourPickerSaturationChoiceSGWidget;
class SGXRenderColourPickerLightnessChoiceSGWidget;
class SGXRenderColourPickerTransparencyChoiceSGWidget;
class SGXRenderColourBackgroundSGWidget;
class SGWTouchReceiver;
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
    static SGWTouchReceiver* hueTouchReceiver;
    static void updateHue(SGWTouchReceiver* /*unused*/, const SGLArray<SGXTouchEvent>& t);
    static SGXRenderColourPickerSaturationChoiceSGWidget* saturationChoice;
    static SGWTouchReceiver* saturationTouchReceiver;
    static void updateSaturation(SGWTouchReceiver* /*unused*/, const SGLArray<SGXTouchEvent>& t);
    static SGXRenderColourPickerLightnessChoiceSGWidget* lightnessChoice;
    static SGWTouchReceiver* lightnessTouchReceiver;
    static void updateLightness(SGWTouchReceiver* /*unused*/, const SGLArray<SGXTouchEvent>& t);
    static SGXRenderColourPickerTransparencyChoiceSGWidget* transparencyChoice;
    static SGWTouchReceiver* transparencyTouchReceiver;
    static void updateTransparency(SGWTouchReceiver* /*unused*/, const SGLArray<SGXTouchEvent>& t);
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
