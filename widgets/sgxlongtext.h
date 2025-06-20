#ifndef SGXLONGTEXT_H
#define SGXLONGTEXT_H

#include <QScrollArea>
#include "../userDefinedClasses/sgusignalemitter.h"
#include <QWidget>
#include <QString>
#include <QColor>
#include <QFont>
#include "../primitives/sgxcolourrgba.h"
#include <QList>

class SGXLongTextInternal;
class SGXLongText : public QScrollArea // scrollable display of multiline text
{
    Q_OBJECT // NOLINT
public:
    SGXLongText(QWidget* parent, void (SGUSignalEmitter::*resizeSignal)(), const QString& s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float s1, float s0, float f1, float f0); // create long text
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
    float s1; // linear factor of scroll bar width
    float s0; // constant factor of scroll bar height
    float f1; // linear factor of font size
    float f0; // constant factor of font size
    QColor backgroundColour; // colour used to shade background
    QColor foregroundColour; // colour used to shade text
    QString s; // text displayed in label
    QFont font; // font used for label with size set
    void setText(const QString& s); // function to change text and update widget
    void setBackgroundColour(); // set background colour to default colour
    void setBackgroundColour(int themeColourIndex); // set background colour to theme colour
    void setBackgroundColour(SGXColourRGBA customColour); // set background colour to custom colour
    void setForegroundColour(); // set text colour to default colour
    void setForegroundColour(int themeColourIndex); // set text colour to theme colour
    void setForegroundColour(SGXColourRGBA customColour); // set text colour to custom colour
    SGXLongTextInternal* displayInternal; // child widget that actually displays text
    QList<int> lineGaps; // list of ints, each pair indicating a line
    void splitLine(); // split string into lines for rendering
public slots: // NOLINT
    void resizeObject(); // automatic resizing of text label
};

#endif // SGXLONGTEXT_H
