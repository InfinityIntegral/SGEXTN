#ifndef SGWHORIZONTALALIGNMENT_H
#define SGWHORIZONTALALIGNMENT_H

#include <qnamespace.h>

class SGWHorizontalAlignment
{
public:
    SGWHorizontalAlignment() = delete;
    enum Flag{
        Left,
        Center,
        Right
    };
    static Qt::AlignmentFlag getQtFlag(SGWHorizontalAlignment::Flag x);
};

#endif // SGWHORIZONTALALIGNMENT_H
