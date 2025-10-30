#ifndef SGWVERTICALALIGNMENT_H
#define SGWVERTICALALIGNMENT_H

#include <private_api_Widgets/SG_Build_Widgets.h>

class SG_WIDGETS_DLL SGWVerticalAlignment
{
public:
    SGWVerticalAlignment() = delete;
    enum Flag{
        Top,
        Center,
        Bottom
    };
};

#endif // SGWVERTICALALIGNMENT_H
