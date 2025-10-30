#ifndef SGXTOUCHEVENT_H
#define SGXTOUCHEVENT_H

#include <private_api_Widgets/SG_Build_Widgets.h>

template <typename T> class SGLArray;
class SG_WIDGETS_DLL SGXTouchEvent
{
public:
    enum TouchPhase{
        TouchStart = 1,
        TouchOngoing = 2,
        TouchEnd = 3
    };
    SGXTouchEvent() = default;
    SGXTouchEvent(int n);
    SGXTouchEvent(int n, const SGLArray<float>& data);
    float x;
    float y;
    SGXTouchEvent::TouchPhase phase;
    int id;
    float differenceX;
    float differenceY;
    float previousX;
    float previousY;
    float startX;
    float startY;
    float force;
    float velocityX;
    float velocityY;
    float radius;
    [[nodiscard]] bool operator==(SGXTouchEvent x) const;
    [[nodiscard]] bool operator!=(SGXTouchEvent x) const;
    [[nodiscard]] bool operator<(SGXTouchEvent x) const;
    [[nodiscard]] bool operator>(SGXTouchEvent x) const;
    [[nodiscard]] int hash() const;
};

#endif // SGXTOUCHEVENT_H
