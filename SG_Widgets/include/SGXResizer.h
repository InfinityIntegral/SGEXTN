#ifndef SGXRESIZER_H
#define SGXRESIZER_H

#include <private_api_Widgets/SG_Build_Widgets.h>

class SG_WIDGETS_DLL SGXResizer
{
public:
    SGXResizer() = delete;
    static float getRenderSpaceWidth();
    static float getRenderSpaceHeight();
    static float getSizeUnit();
};

#endif // SGXRESIZER_H
