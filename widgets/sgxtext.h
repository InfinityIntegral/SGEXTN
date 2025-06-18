#ifndef SGXTEXT_H
#define SGXTEXT_H

#include <QWidget>
#include "../userDefinedClasses/sgusignalemitter.h"
#include "../primitives/sgxcolourrgba.h"
#include <QString>
#include <QFont>

class SGXText : public QWidget // text label, non interactive
{
    Q_OBJECT // NOLINT
public:
    SGXText(QWidget* parent, void (SGUSignalEmitter::*resizeSignal)(), const QString& s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0); // create text label using default colours
    SGXText(QWidget* parent, void (SGUSignalEmitter::*resizeSignal)(), const QString& s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, int bgThemeColourIndex, int fgThemeColourIndex); // create text label using theme colours
    SGXText(QWidget *parent, void (SGUSignalEmitter::*resizeSignal)(), const QString& s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, SGXColourRGBA bgCustomColour, SGXColourRGBA fgCustomColour); // create text label using custom colours
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
    int bgColourMode; // mode to shade background, 0 for default (fully tansparent), 1 for theme colour, -1 for custom colour
    int fgColourMode; // mode to shade text, 0 for default (fully tansparent), 1 for theme colour, -1 for custom colour
    int bgThemeColourIndex; // index of theme colour between 0 to 8 inclusive to shade the background if colourMode is 1
    int fgThemeColourIndex; // index of theme colour between 0 to 8 inclusive to shade the text if colourMode is 1
    SGXColourRGBA bgCustomColour = SGXColourRGBA(255, 255, 255, 0); // colour for background if colourMode is -1
    SGXColourRGBA fgCustomColour = SGXColourRGBA(255, 255, 255, 0); // colour for text if colourMode is -1
    QString s; // text displayed in label
    QFont font; // font used for label with size set
    void setText(const QString& s); // function to change text and update widget
    void paintEvent(QPaintEvent*) override; // NOLINT(readability-named-parameter)
public slots: // NOLINT
    void resizeObject(); // automatic resizing of widget
};

#endif // SGXTEXT_H
