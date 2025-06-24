#ifndef SGXTOUCHEVENT_H
#define SGXTOUCHEVENT_H

#include <QDebug>
#include <bit>
#include <QString>

class SGXTouchEvent // struct to represent touch input
{
public:
    enum TouchPhase {TouchStart, TouchOngoing, TouchEnd}; // enum representing touch phase (inspired by Unity C#)
    SGXTouchEvent() = default;
    // built constructors later
    // SGTouchEvent no longer supports QTouchEvent, precise touch interaction must be done through a SGEXTN-QtQuick touchReceiver, an instance of this can be provided using SGXQuickUIInterface::createTouchReceiver
    // for QTouchEvent support, refer to this file in the SGEXTN v1 release, but that version has less features
    float x; // x coordinate of touch event
    float y; // y coordinate of touch event
    SGXTouchEvent::TouchPhase phase; // touch phase
    float id; // ID of touch event
    float dx; // difference between x coordinates of this touch event and the same touch event on the previous frame, zero if previous touch does not exist
    float dy; // difference between y coordinates of this touch event and the same touch event on the previous frame, zero if previous touch does not exist
    float prevX; // x coordinate of touch event on previous frame
    float prevY; // y coordinate of touch event on previous frame
    float startX; // x coordinate of starting point of this touch event
    float startY; // y coordinate of starting point of this touch event
    float f; // force of this touch event, number between 0 to 1
    // touch event speed should not be relied upon for cross platform applications unless the property has been tested to work on compatible devices, for most purposes, using dx, dy, prevX, prevY should be more than sufficient
    float vx; // speed of this touch event in x direction in pixels per second, zero if unsupported
    float vy; // speed of this touch event in y direction in pixels per second, zero if unsupported
    float r; // radius of touch event
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
        s << ("touch event with id = " + QString::number(x.id) + ", phase = ongoing, position = (" + QString::number(x.x) + ", " + QString::number(x.y) + ")");
        return s;
    }
    s << "touch event with invalid phase";
    return s;
}

#endif // SGXTOUCHEVENT_H
