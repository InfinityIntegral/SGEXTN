#ifndef SGXSCROLLVIEW_H
#define SGXSCROLLVIEW_H

#include <QWidget>
#include <QScrollArea>
#include "../userDefinedClasses/sgusignalemitter.h"

class SGXScrollView : public QScrollArea // scroll view with custom scroll bars
{
    Q_OBJECT // NOLINT
public:
    SGXScrollView(QWidget *parent, void (SGUSignalEmitter::*resizeSignal)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0, float s1, float s0); // create scroll view with custom scroll bars
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
public slots: // NOLINT
    void resizeObject(); // for automatic resizing
};

#endif // SGXSCROLLVIEW_H
