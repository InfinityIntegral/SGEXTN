#ifndef SGWTOUCHRECEIVER_H
#define SGWTOUCHRECEIVER_H

#include "../noninstantiable/sgwwidget.h"
#include <array>

class SGWWidgetQuickInterface;
class SGXString;
class SGXTouchEvent;
class SGWTouchReceiver : public SGWWidget
{
public:
    SGWTouchReceiver(SGWWidget* parent, void (*function)(SGWTouchReceiver*, const std::array<SGXTouchEvent, 5>&), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    SGWTouchReceiver() = delete;
    SGWTouchReceiver(const SGWTouchReceiver&) = delete;
    SGWTouchReceiver& operator=(const SGWTouchReceiver&) = delete;
    SGWTouchReceiver(SGWTouchReceiver&&) = delete;
    SGWTouchReceiver& operator=(SGWTouchReceiver&&) = delete;
    ~SGWTouchReceiver() override;
    void (*function)(SGWTouchReceiver*, const std::array<SGXTouchEvent, 5>&);
    [[nodiscard]] float getWidth() const;
    [[nodiscard]] float getHeight() const;
    void eventReceived(const SGXString& s);
protected:
    SGWWidgetQuickInterface* quickInterface;
};

#endif // SGWTOUCHRECEIVER_H
