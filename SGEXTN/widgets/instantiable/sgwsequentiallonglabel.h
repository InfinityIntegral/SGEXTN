#ifndef SGWSEQUENTIALLONGLABEL_H
#define SGWSEQUENTIALLONGLABEL_H

#include "../noninstantiable/sgwlabel.h"

class SGWWidget;
class SGXString;
class SGWSequentialLongLabel : public SGWLabel
{
public:
    SGWSequentialLongLabel(SGWWidget* parent, const SGXString& s, float x1, float x0, float y1, float y0, float w1, float w0, float h1, float h0);
};

#endif // SGWSEQUENTIALLONGLABEL_H
