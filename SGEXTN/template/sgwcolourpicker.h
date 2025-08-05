#ifndef SGWCOLOURPICKER_H
#define SGWCOLOURPICKER_H

#include <QObject>
#include "../widgets/sgwbackground.h"
#include "../primitives/sgxcolourrgba.h"
#include "../primitives/sgxcolourhsla.h"
#include <qtmetamacros.h>
#include "../colourpickerrendering/huechoice/sgxrendercolourpickerhuechoicesgwidget.h"

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
};

#endif // SGWCOLOURPICKER_H
