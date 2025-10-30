#ifndef SGWSINGLETOUCHRECEIVER_H
#define SGWSINGLETOUCHRECEIVER_H

#include <SGWWidget.h>
#include <SGXString.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SGWWidgetQuickInterface;
class SGXTouchEvent;
class SG_WIDGETS_DLL SGWSingleTouchReceiver : public SGWWidget
{
public:
    SGWSingleTouchReceiver(SGWWidget* parent, void (*function)(const SGXTouchEvent&), float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
    SGWSingleTouchReceiver() = delete;
    SGWSingleTouchReceiver(const SGWSingleTouchReceiver&) = delete;
    SGWSingleTouchReceiver& operator=(const SGWSingleTouchReceiver&) = delete;
    SGWSingleTouchReceiver(SGWSingleTouchReceiver&&) = delete;
    SGWSingleTouchReceiver& operator=(SGWSingleTouchReceiver&&) = delete;
    ~SGWSingleTouchReceiver() override;
    int attachedInt;
    SGXString attachedString;
    void (*callbackFunction)(const SGXTouchEvent&);
    void (*callbackFunctionWithInt)(int, const SGXTouchEvent&);
    void (*callbackFunctionWithString)(SGXString, const SGXTouchEvent&);
    void (*callbackFunctionWithPointer)(SGWSingleTouchReceiver*, const SGXTouchEvent&);
    [[nodiscard]] float getWidth() const;
    [[nodiscard]] float getHeight() const;
    void eventReceived(const SGXString& s);
protected:
    SGWWidgetQuickInterface* quickInterface;
};

#endif // SGWSINGLETOUCHRECEIVER_H
