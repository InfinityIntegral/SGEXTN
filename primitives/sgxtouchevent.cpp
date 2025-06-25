#include "sgxtouchevent.h"

SGXTouchEvent::SGXTouchEvent(int n, float *data){
    qDebug() << n << data[0] << data[1] << data[2] << data[3] << data[4] << data[5] << data[6] << data[7] << data[8] << data[9] << data[10];
}

SGXTouchEvent::SGXTouchEvent(int n){
    qDebug() << n;
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
