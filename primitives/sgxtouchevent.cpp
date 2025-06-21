#include "sgxtouchevent.h"
#include <QTouchEvent>
#include <QEventPoint>

SGXTouchEvent::SGXTouchEvent(int id, SGXTouchEvent::TouchPhase phase, int x, int y, SGXTouchEvent lt){
    (*this).id = id;
    (*this).phase = phase;
    (*this).x = x;
    (*this).y = y;
    if(phase == SGXTouchEvent::TouchOngoing){
        (*this).dx = x - lt.x;
        (*this).dy = y - lt.y;
    }
    else{
        (*this).dx = 0;
        (*this).dy = 0;
    }
}

SGXTouchEvent::SGXTouchEvent(int id, SGXTouchEvent::TouchPhase phase, int x, int y){
    (*this).id = id;
    (*this).phase = phase;
    (*this).x = x;
    (*this).y = y;
    (*this).dx = 0;
    (*this).dy = 0;
}

SGXTouchEvent::SGXTouchEvent(const QTouchEvent::TouchPoint& tp, SGXTouchEvent lt){
    id = tp.id();
    x = static_cast<int>(tp.position().x());
    y = static_cast<int>(tp.position().y());
    if(tp.state() == QEventPoint::Pressed){phase = SGXTouchEvent::TouchStart;}
    else if(tp.state() == QEventPoint::Stationary || tp.state() == QEventPoint::Updated){phase = SGXTouchEvent::TouchOngoing;}
    else{phase = SGXTouchEvent::TouchEnd;}
    if(phase == SGXTouchEvent::TouchOngoing){
        (*this).dx = x - lt.x;
        (*this).dy = y - lt.y;
    }
    else{
        (*this).dx = 0;
        (*this).dy = 0;
    }
}

SGXTouchEvent::SGXTouchEvent(const QTouchEvent::TouchPoint& tp){
    id = tp.id();
    x = static_cast<int>(tp.position().x());
    y = static_cast<int>(tp.position().y());
    if(tp.state() == QEventPoint::Pressed){phase = SGXTouchEvent::TouchStart;}
    else if(tp.state() == QEventPoint::Stationary || tp.state() == QEventPoint::Updated){phase = SGXTouchEvent::TouchOngoing;}
    else{phase = SGXTouchEvent::TouchEnd;}
    (*this).dx = 0;
    (*this).dy = 0;
}

bool SGXTouchEvent::operator==(SGXTouchEvent x) const {
    return (id == x.id);
}

bool SGXTouchEvent::operator !=(SGXTouchEvent x) const {
    return (id != x.id);
}

bool SGXTouchEvent::operator<(SGXTouchEvent x) const {
    return (id < x.id);
}
