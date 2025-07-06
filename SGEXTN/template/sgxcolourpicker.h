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
    static void initialise(); // initialise colour picker by creating necessary components
    static void activate(); // show colour picker when a colour picker widget is pressed
    static QQuickItem* instance; // root to colour picker
    static QQuickItem* targetInput; // currently active colour picker widget
    static SGXColourRGBA currentColour; // RGBA colour currently held in colour picker
    static SGXColourHSLA currentColourHSLA; // HSLA colour currently held in colour picker
    static void refresh(); // function to refresh sliders and input fields in colour picker
    static QQmlComponent* hueChoiceTemplate; // QML template for hue slider
    static QQuickItem* createHueChoice(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0); // function to create hue slider
    static QQuickItem* hueChoice; // reference to existing hue slider
    static QQuickItem* hueChoiceTouchReceiver; // reference to touch receiver on existing hue slider
    static QQmlComponent* saturationChoiceTemplate; // QML template for saturation slider
    static QQuickItem* createSaturationChoice(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0); // function to create saturation slider
    static QQuickItem* saturationChoice; // reference to existing saturation slider
    static QQuickItem* saturationChoiceTouchReceiver; // reference to touch receiver on existing saturation slider
    static QQmlComponent* lightnessChoiceTemplate; // QML template for lightness slider
    static QQuickItem* createLightnessChoice(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0); // function to create lightness slider
    static QQuickItem* lightnessChoice; // reference to existing lightness slider
    static QQuickItem* lightnessChoiceTouchReceiver; // reference to touch receiver on existing lightness slider
    static QQmlComponent* transparencyChoiceTemplate; // QML template for transparency slider
    static QQuickItem* createTransparencyChoice(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0); // function to create transparency slider
    static QQuickItem* transparencyChoice; // reference to existing transparency slider
    static QQuickItem* transparencyChoiceTouchReceiver; // reference to touch receiver on existing transparency slider
    static QQuickItem* redInput; // red coordinate input field
    static QQuickItem* greenInput; // green coordinate input field
    static QQuickItem* blueInput; // blue coordinate input field
    static QQuickItem* transparencyInput; // transparency coordinate input field
    static QQmlComponent* colourBackgroundTemplate; // QML template for colour display
    static QQuickItem* createColourBackground(QQuickItem* parent, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0); // function to create colour display
    static QQuickItem* colourDisplay; // reference to existing colour display
    static QQuickItem* hexCodeInput; // hex code input field
signals:
    void doNothing();
public slots:
    static void changeHue(const std::array<SGXTouchEvent, 5>& t); // refresh chosen colour when hue changes
    static void changeSaturation(const std::array<SGXTouchEvent, 5>& t); // refresh chosen colour when saturation changes
    static void changeLightness(const std::array<SGXTouchEvent, 5>& t); // refresh chosen colour when lightness changes
    static void changeTransparencyBySlider(const std::array<SGXTouchEvent, 5>& t); // refresh colour when transparency changes using slider
    static void changeRed(); // refresh chosen colour when red coordinate changes
    static void changeGreen(); // refresh chosen colour when green coordinate changes
    static void changeBlue(); // refresh chosen colour when blue coordinate changes
    static void changeTransparency(); // refresh chosen colour when transparency coordinate changes
    static void changeHexCode(); // refresh chosen colour when changed using hex code
    static void doneSelection(); // turn off colour picker when done
};

#endif // SGXCOLOURPICKER_H
