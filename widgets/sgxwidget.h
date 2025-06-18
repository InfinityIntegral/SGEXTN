#ifndef SGXWIDGET_H
#define SGXWIDGET_H

#include <QWidget>
#include "../primitives/sgxcolourrgba.h"
#include "../userDefinedClasses/sgusignalemitter.h"

class SGXWidget : public QWidget // widget to display solid colour, non interactive
{
    Q_OBJECT // NOLINT
public:
    SGXWidget(QWidget* parent, void (SGUSignalEmitter::*resizeSignal)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0); // create widget using default colour (transparent)
    SGXWidget(QWidget* parent, void (SGUSignalEmitter::*resizeSignal)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int themeColourIndex); // create widget using a theme colour
    SGXWidget(QWidget* parent, void (SGUSignalEmitter::*resizeSignal)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGXColourRGBA customColour); // create widget using custom colour
    // the value of each size and location variable is linear factor * width or height of rendering space + constant factor * size unit
    // ensure that x0 + w0 < 13.5 * (1 - x1 - w1) and y0 + h0 < 13.5 * (1 - y1 - h1) to avoid widgets going off screen
    // you are recommended to keep 0.5 * size unit of margin on the 4 sides of the screen
    float x1; // linear factor of x position
    float x0; // constant factor of x position
    float y1; // linear factor of y position
    float y0; // constant factor of y position
    float w1; // linear factor of width
    float w0; // constant factor of width
    float h1; // linear factor of height
    float h0; // constant factor of height
    int colourMode; // mode to shade colour, 0 for default (fully tansparent), 1 for theme colour, -1 for custom colour
    int themeColourIndex; // index of theme colour between 0 to 8 inclusive to shade the widget if colourMode is 1
    SGXColourRGBA customColour = SGXColourRGBA(255, 255, 255, 0); // colour for this widget if colourMode is -1
    void paintEvent(QPaintEvent*) override; // NOLINT(readability-named-parameter)
public slots: // NOLINT
    void resizeObject(); // automatic resizing of widget
};

#endif // SGXWIDGET_H
