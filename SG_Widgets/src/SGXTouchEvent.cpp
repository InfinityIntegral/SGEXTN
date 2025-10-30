#include <SGXTouchEvent.h>
#include <SGLArray.h>
#include <SGLHash.h>

SGXTouchEvent::SGXTouchEvent(int n, const SGLArray<float> &data){
    // x, y, px, py, sx, sy, vx, vy, rx, ry, f
    id = n;
    x = data.at(0);
    y = data.at(1);
    if(data.at(0) == data.at(4) && data.at(1) == data.at(5)){phase = SGXTouchEvent::TouchStart;}
    else{phase = SGXTouchEvent::TouchOngoing;}
    differenceX = data.at(0) - data.at(2);
    differenceY = data.at(1) - data.at(3);
    previousX = data.at(2);
    previousY = data.at(3);
    startX = data.at(4);
    startY = data.at(5);
    force = data.at(10);
    velocityX = data.at(6);
    velocityY = data.at(7);
    if(data.at(8) >= data.at(9)){radius = data.at(8) / 2.0f;}
    else{radius = data.at(9) / 2.0f;}
}

SGXTouchEvent::SGXTouchEvent(int n){
    id = n;
    x = 0.0f;
    y = 0.0f;
    phase = SGXTouchEvent::TouchEnd;
    differenceX = 0.0f;
    differenceY = 0.0f;
    previousX = 0.0f;
    previousY = 0.0f;
    startX = 0.0f;
    startY = 0.0f;
    force = 0.0f;
    velocityX = 0.0f;
    velocityY = 0.0f;
    radius = 0.0f;
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

bool SGXTouchEvent::operator>(SGXTouchEvent x) const {
    return (id > x.id);
}

int SGXTouchEvent::hash() const {
    return SGLHash<int>()(id);
}
