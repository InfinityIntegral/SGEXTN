#include "sgxtouchevent.h"
#include <algorithm>
#include <array>

SGXTouchEvent::SGXTouchEvent(int n, const std::array<float, 11> &data){
    // [x, y, px, py, sx, sy, vx, vy, rx, ry, f]
    id = n;
    x = data[0];
    y = data[1];
    if(data[0] == data[4] && data[1] == data[5]){phase = SGXTouchEvent::TouchStart;}
    else{phase = SGXTouchEvent::TouchOngoing;}
    differenceX = data[0] - data[2];
    differenceY = data[1] - data[3];
    previousX = data[2];
    previousY = data[3];
    startX = data[4];
    startY = data[5];
    force = data[10];
    velocityX = data[6];
    velocityY = data[7];
    radius = std::max(data[8], data[9]) / 2.0f;
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
