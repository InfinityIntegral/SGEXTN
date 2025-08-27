#ifndef SGWTOUCHRECEIVER_H
#define SGWTOUCHRECEIVER_H

#include "../noninstantiable/sgwwidget.h"
#include "../../primitives/sgxtouchevent.h"
#include <array>
#include <QString>

class SGWWidgetQuickInterface;
class SGWTouchReceiver : public SGWWidget
{
public:
    SGWTouchReceiver(SGWWidget* parent, void (*function)(SGWTouchReceiver*, const std::array<SGXTouchEvent, 5>&), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    ~SGWTouchReceiver() override;
    void (*function)(SGWTouchReceiver*, const std::array<SGXTouchEvent, 5>&);
    [[nodiscard]] float getWidth() const;
    [[nodiscard]] float getHeight() const;
    void eventReceived(const QString& s);
protected:
    SGWWidgetQuickInterface* quickInterface;
};

#endif // SGWTOUCHRECEIVER_H
