#ifndef SGWMULTITOUCHRECEIVER_H
#define SGWMULTITOUCHRECEIVER_H

#include "../noninstantiable/sgwwidget.h"
#include "../../primitives/sgxstring.h"

class SGWWidgetQuickInterface;
class SGXTouchEvent;
template <typename T> class SGLArray;
class SGWMultiTouchReceiver : public SGWWidget
{
public:
    SGWMultiTouchReceiver(SGWWidget* parent, void (*function)(const SGLArray<SGXTouchEvent>&), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    SGWMultiTouchReceiver() = delete;
    SGWMultiTouchReceiver(const SGWMultiTouchReceiver&) = delete;
    SGWMultiTouchReceiver& operator=(const SGWMultiTouchReceiver&) = delete;
    SGWMultiTouchReceiver(SGWMultiTouchReceiver&&) = delete;
    SGWMultiTouchReceiver& operator=(SGWMultiTouchReceiver&&) = delete;
    ~SGWMultiTouchReceiver() override;
    int attachedInt;
    SGXString attachedString;
    void (*callbackFunction)(const SGLArray<SGXTouchEvent>&);
    void (*callbackFunctionWithInt)(int, const SGLArray<SGXTouchEvent>&);
    void (*callbackFunctionWithString)(SGXString, const SGLArray<SGXTouchEvent>&);
    void (*callbackFunctionWithPointer)(SGWMultiTouchReceiver*, const SGLArray<SGXTouchEvent>&);
    [[nodiscard]] float getWidth() const;
    [[nodiscard]] float getHeight() const;
    void eventReceived(const SGXString& s);
protected:
    SGWWidgetQuickInterface* quickInterface;
};

#endif // SGWMULTITOUCHRECEIVER_H
