#ifndef SGWCOLOURPICKER_H
#define SGWCOLOURPICKER_H

#include <SGXColourRGBA.h>
#include <SGXColourHSLA.h>
#include <private_api_RI/SG_Build_RI.h>

class SGWBackground;
class SGWSingleTouchReceiver;
class SGWInput;
class SGWColourPickerWidget;
class SGWButton;
class SGXTouchEvent;
class SGWBlankWidget;
class SGRColourPickerSyncer;
class SGRRendererWidget;
class SG_RI_DLL SGWColourPicker
{
public:
    SGWColourPicker() = delete;
    static SGWBackground* instance;
    static SGXColourRGBA colour;
    static SGXColourHSLA colourHSLA;
    static SGWBackground* initialise();
    static void reset();
    static void activate();
    static SGRRendererWidget* hueChoice;
    static SGRColourPickerSyncer* hueSync;
    static void updateUsingColour();
    static void updateUsingColourHSLA();
    static void updateInputs();
    static SGWSingleTouchReceiver* hueTouchReceiver;
    static void updateHue(const SGXTouchEvent& t);
    static SGRRendererWidget* saturationChoice;
    static SGRColourPickerSyncer* saturationSync;
    static SGWSingleTouchReceiver* saturationTouchReceiver;
    static void updateSaturation(const SGXTouchEvent& t);
    static SGRRendererWidget* lightnessChoice;
    static SGRColourPickerSyncer* lightnessSync;
    static SGWSingleTouchReceiver* lightnessTouchReceiver;
    static void updateLightness(const SGXTouchEvent& t);
    static SGRRendererWidget* transparencyChoice;
    static SGRColourPickerSyncer* transparencySync;
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
    static SGWBlankWidget* colourDisplay;
    static bool ignoreInputChanges;
    static SGWColourPickerWidget* colourReceiver;
    static void activateColourPicker(SGWColourPickerWidget* x);
    static void completeColourSelection();
    static SGWButton* completeButton;
};

#endif // SGWCOLOURPICKER_H
