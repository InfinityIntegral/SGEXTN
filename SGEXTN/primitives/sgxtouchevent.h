#ifndef SGXTOUCHEVENT_H
#define SGXTOUCHEVENT_H

#include <array>

class SGXTouchEvent
{
public:
    enum TouchPhase{
        TouchStart = 1,
        TouchOngoing = 2,
        TouchEnd = 3
    };
    SGXTouchEvent() = default;
    SGXTouchEvent(int n);
    SGXTouchEvent(int n, const std::array<float, 11>& data);
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

inline unsigned int qHash(SGXTouchEvent x, unsigned int seed = 0){
    return seed ^ static_cast<unsigned int>(x.id);
}

#endif // SGXTOUCHEVENT_H
