#ifndef SGWVERTICALALIGNMENT_H
#define SGWVERTICALALIGNMENT_H

#include <qnamespace.h>

class SGWVerticalAlignment
{
public:
    SGWVerticalAlignment() = delete;
    enum Flag{
        Top,
        Center,
        Bottom
    };
    static Qt::AlignmentFlag getQtFlag(SGWVerticalAlignment::Flag x);
};

#endif // SGWVERTICALALIGNMENT_H
