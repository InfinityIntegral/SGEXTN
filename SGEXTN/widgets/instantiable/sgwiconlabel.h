#ifndef SGWICONLABEL_H
#define SGWICONLABEL_H

#include "../noninstantiable/sgwlabel.h"
#include "../../primitives/sgxchar.h"

class SGWWidget;
class SGWIconLabel : public SGWLabel
{
public:
    SGWIconLabel(SGWWidget* parent, SGXChar s, float x1, float x0, float y1, float y0, float w1, float w0);
    [[nodiscard]] SGXChar getChar() const;
    void setChar(SGXChar c);
protected:
    SGXChar textChar = {};
};

#endif // SGWICONLABEL_H
