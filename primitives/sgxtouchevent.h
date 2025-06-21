#ifndef SGXTOUCHEVENT_H
#define SGXTOUCHEVENT_H

#include <QTouchEvent>
#include <bit>
#include <QString>

class SGXTouchEvent // struct to represent touch input
{
public:
    enum TouchPhase {TouchStart, TouchOngoing, TouchEnd}; // enum representing touch phase (inspired by Unity C#)
    SGXTouchEvent(int id, SGXTouchEvent::TouchPhase phase, int x, int y, SGXTouchEvent lt); // creation from components with previous touch
    SGXTouchEvent(int id, SGXTouchEvent::TouchPhase phase, int x, int y); // creation from components without previous touch
    SGXTouchEvent(const QTouchEvent::TouchPoint& tp, SGXTouchEvent lt); // creation from QTouchEvent with previous touch
    SGXTouchEvent(const QTouchEvent::TouchPoint& tp); // creation from QTouchEvent without previous touch
    int x; // x coordinate of touch event
    int y; // y coordinate of touch event
    SGXTouchEvent::TouchPhase phase; // touch phase
    int id; // ID of touch event
    int dx; // difference between x coordinates of this touch event and the same touch event on the previous frame, zero if previous touch does not exist
    int dy; // difference between y coordinates of this touch event and the same touch event on the previous frame, zero if previous touch does not exist
    [[nodiscard]] bool operator==(SGXTouchEvent x) const; // equality comparator by comparing id not struct instance memory location, ignores frame number because you should never mix touch events from different frames anyways
    [[nodiscard]] bool operator!=(SGXTouchEvent x) const; // inequality comparator by comparing id not struct instance memory location, ignores frame number because you should never mix touch events from different frames anyways
    [[nodiscard]] bool operator<(SGXTouchEvent x) const; // < comparator for use in sorted data structure
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
        s << ("touch event with id = " + QString::number(x.id) + ", phase = ongoing, position = (" + QString::number(x.x) + ", " + QString::number(x.y) + "), distance since last position = (" + QString::number(x.dx) + ", " + QString::number(x.dy) + ")");
        return s;
    }
    s << "touch event with invalid phase";
    return s;
}

#endif // SGXTOUCHEVENT_H
