#ifndef SGXRESIZER_H
#define SGXRESIZER_H

class SGXResizer
{
public:
    SGXResizer() = delete;
    static float getRenderSpaceWidth();
    static float getRenderSpaceHeight();
    static float getSizeUnit();
};

#endif // SGXRESIZER_H
