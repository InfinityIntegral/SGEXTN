#ifndef SGXICON_H
#define SGXICON_H

#include <QWidget>
#include "../userDefinedClasses/sgusignalemitter.h"
#include "../primitives/sgxcolourrgba.h"
#include <QChar>
#include <QFont>
#include <QColor>

class SGXIcon : public QWidget // non interative icon
{
    Q_OBJECT // NOLINT
public:
    SGXIcon(QWidget* parent, void (SGUSignalEmitter::*resizeSignal)(), const QChar& s, float x1, float x0, float y1, float y0, float w1, float w0); // create icon
    // the value of each size and location variable is linear factor * width or height of rendering space + constant factor * size unit
    // ensure that x0 + w0 < 13.5 * (1 - x1 - w1) and y0 + w0 < 13.5 * (1 - y1 - w1) to avoid widgets going off screen
    // you are recommended to keep 0.5 * size unit of margin on the 4 sides of the screen
    float x1; // linear factor of x position
    float x0; // constant factor of x position
    float y1; // linear factor of y position
    float y0; // constant factor of y position
    float w1; // linear factor of width and height
    float w0; // constant factor of width and height
    QColor backgroundColour; // colour used to shade background
    QColor foregroundColour; // colour used to shade icon
    QChar s; // icon displayed, use corresponding char from your icons font
    QFont font; // font used for icon with size set
    void setIcon(const QChar& s); // function to change icon and update widget
    void setBackgroundColour(); // set background colour to default colour
    void setBackgroundColour(int themeColourIndex); // set background colour to theme colour
    void setBackgroundColour(SGXColourRGBA customColour); // set background colour to custom colour
    void setForegroundColour(); // set icon colour to default colour
    void setForegroundColour(int themeColourIndex); // set icon colour to theme colour
    void setForegroundColour(SGXColourRGBA customColour); // set icon colour to custom colour
    void paintEvent(QPaintEvent*) override; // NOLINT(readability-named-parameter)
public slots: // NOLINT
    void resizeObject(); // automatic resizing of icon
};

#endif // SGXICON_H
