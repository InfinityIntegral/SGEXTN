#include "sgxtouchevent.h"
#include <QTouchEvent>
#include <QEventPoint>

bool SGXTouchEvent::operator==(SGXTouchEvent x) const {
    return (id == x.id);
}

bool SGXTouchEvent::operator !=(SGXTouchEvent x) const {
    return (id != x.id);
}

bool SGXTouchEvent::operator<(SGXTouchEvent x) const {
    return (id < x.id);
}
