#ifndef SGWTOUCHRECEIVER_H
#define SGWTOUCHRECEIVER_H

#include <qtmetamacros.h>
#include "../noninstantiable/sgwwidget.h"
#include "../../primitives/sgxtouchevent.h"
#include <array>
#include <QString>

class SGWTouchReceiver : public SGWWidget
{
    Q_OBJECT
public:
    SGWTouchReceiver(SGWWidget* parent, void (*function)(SGWTouchReceiver*, const std::array<SGXTouchEvent, 5>&), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    void (*function)(SGWTouchReceiver*, const std::array<SGXTouchEvent, 5>&);
    [[nodiscard]] float getWidth() const;
    [[nodiscard]] float getHeight() const;
signals:
    void doNothing();
public slots:
    void eventReceived(const QString& s);
};

#endif // SGWTOUCHRECEIVER_H
