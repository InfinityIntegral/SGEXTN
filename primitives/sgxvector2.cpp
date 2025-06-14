#include "sgxvector2.h"

SGXVector2::SGXVector2(float x, float y){
    (*this).x = x;
    (*this).y = y;
}

bool SGXVector2::operator==(SGXVector2 x) const {
    return (((*this).x == x.x) && ((*this).y == x.y));
}

bool SGXVector2::operator!=(SGXVector2 x) const {
    return (((*this).x != x.x) || ((*this).y != x.y));
}

bool SGXVector2::operator<(SGXVector2 x) const {
    if((*this).x != x.x){return ((*this).x < x.x);}
    return ((*this).y < x.y);
}

QString SGXVector2::getStringForPrinting() const {
    return ("(" + QString::number(x) + ", " + QString::number(y) + ")");
}
