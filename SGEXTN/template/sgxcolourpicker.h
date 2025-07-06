#ifndef SGXCOLOURPICKER_H
#define SGXCOLOURPICKER_H

#include <QObject>
#include <QQuickItem>
#include <QQmlComponent>
#include <qtmetamacros.h>
#include <array>
#include "../primitives/sgxtouchevent.h"
#include "../primitives/sgxcolourrgba.h"
#include "../primitives/sgxcolourhsla.h"

class SGXColourPicker : public QObject
{
    Q_OBJECT
public:
    SGXColourPicker() = delete;
    static void initialise();
    static void activate();
    static QQuickItem* instance;
    static QQuickItem* targetInput;
    static SGXColourRGBA currentColour;
    static SGXColourHSLA currentColourHSLA;
    static void refresh();
    static QQmlComponent* hueChoiceTemplate;
    static QQuickItem* createHueChoice(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    static QQuickItem* hueChoice;
    static QQuickItem* hueChoiceTouchReceiver;
    static QQmlComponent* saturationChoiceTemplate;
    static QQuickItem* createSaturationChoice(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    static QQuickItem* saturationChoice;
    static QQuickItem* saturationChoiceTouchReceiver;
    static QQmlComponent* lightnessChoiceTemplate;
    static QQuickItem* createLightnessChoice(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    static QQuickItem* lightnessChoice;
    static QQuickItem* lightnessChoiceTouchReceiver;
    static QQmlComponent* transparencyChoiceTemplate;
    static QQuickItem* createTransparencyChoice(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    static QQuickItem* transparencyChoice;
    static QQuickItem* transparencyChoiceTouchReceiver;
    static QQuickItem* redInput;
    static QQuickItem* greenInput;
    static QQuickItem* blueInput;
    static QQuickItem* transparencyInput;
    static QQmlComponent* colourBackgroundTemplate;
    static QQuickItem* createColourBackground(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    static QQuickItem* colourDisplay;
    static QQuickItem* hexCodeInput;
signals:
    void doNothing();
public slots:
    static void changeHue(const std::array<SGXTouchEvent, 5>& t);
    static void changeSaturation(const std::array<SGXTouchEvent, 5>& t);
    static void changeLightness(const std::array<SGXTouchEvent, 5>& t);
    static void changeTransparencyBySlider(const std::array<SGXTouchEvent, 5>& t);
    static void changeRed();
    static void changeGreen();
    static void changeBlue();
    static void changeTransparency();
    static void changeHexCode();
    static void doneSelection();
};

#endif // SGXCOLOURPICKER_H
