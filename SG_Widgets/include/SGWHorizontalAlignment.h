#ifndef SGWHORIZONTALALIGNMENT_H
#define SGWHORIZONTALALIGNMENT_H

#include <private_api_Widgets/SG_Build_Widgets.h>

class SG_WIDGETS_DLL SGWHorizontalAlignment
{
public:
    SGWHorizontalAlignment() = delete;
    enum Flag{
        Left,
        Center,
        Right
    };
};

#endif // SGWHORIZONTALALIGNMENT_H
