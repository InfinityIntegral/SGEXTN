#ifndef SGXTOUCHRECEIVER_H
#define SGXTOUCHRECEIVER_H

#include <QWidget>
#include "../userDefinedClasses/sgusignalemitter.h"
#include "../primitives/sgxtouchevent.h"
#include <QEvent>
#include <QList>

class SGXTouchReceiver : public QWidget // transparent widget to handle touch events
{
    Q_OBJECT // NOLINT
public:
    SGXTouchReceiver(QWidget* parent, void (SGUSignalEmitter::*resizeSignal)(), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0); // create touch receiver
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
    void paintEvent(QPaintEvent*) override; // NOLINT(readability-named-parameter)
    bool event(QEvent* event) override; // custom handling of touch events
    QList<SGXTouchEvent> activeTouches; // list of existing touch events
    virtual void process() = 0; // user defined function for actual touch event processing, must be scheduled
    bool scheduled; // indicates if call to processTouches has been scheduled
public slots: // NOLINT
    void resizeObject(); // automatic resizing of touch receiver
    void processTouches(); // function to run user defined processing function upon receiving touch input
};

#endif // SGXTOUCHRECEIVER_H
