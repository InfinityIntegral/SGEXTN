#ifndef SGXTOUCHEVENT_H
#define SGXTOUCHEVENT_H

#include <QDebug>
#include <bit>
#include <QString>
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
};

inline unsigned int qHash(SGXTouchEvent x, unsigned int seed = 0){
    return seed ^ std::bit_cast<unsigned int>(x.id);
}

inline QDebug operator<<(QDebug s, SGXTouchEvent x){
    if(x.phase == SGXTouchEvent::TouchStart){
        s << ("touch event with id = " + QString::number(x.id) + ", phase = starting, position = (" + QString::number(x.x) + ", " + QString::number(x.y) + ")");
        return s;
    }
    if(x.phase == SGXTouchEvent::TouchEnd){
        s << ("touch event with id = " + QString::number(x.id) + ", phase = ending");
        return s;
    }
    if(x.phase == SGXTouchEvent::TouchOngoing){
        s << ("touch event with id = " + QString::number(x.id) + ", phase = ongoing, position = (" + QString::number(x.x) + ", " + QString::number(x.y) + ")");
        return s;
    }
    s << "touch event with invalid phase";
    return s;
}

#endif // SGXTOUCHEVENT_H
