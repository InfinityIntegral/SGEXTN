#include "sgxcolourrgba.h"

namespace{
inline void temp_boundInt(int& x){
    if(x < 0){x = 0;}
    else if(x > 255){x = 255;}
}

inline void temp_boundFloat(float& x){
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
}

inline unsigned int temp_floatToUnsignedInt(float x){
    x = 255.0f * x + 0.5f;
    return static_cast<unsigned int>(x);
}
}

SGXColourRGBA::SGXColourRGBA(unsigned int x0){
    (*this).x = x0;
}

SGXColourRGBA::SGXColourRGBA(int r, int g, int b, int a){
    temp_boundInt(r);
    temp_boundInt(g);
    temp_boundInt(b);
    temp_boundInt(a);
    (*this).x = (static_cast<unsigned int>(r) << 24U) | (static_cast<unsigned int>(g) << 16U) | (static_cast<unsigned int>(b) << 8U) | (static_cast<unsigned int>(a));
}

SGXColourRGBA::SGXColourRGBA(int r, int g, int b){
    temp_boundInt(r);
    temp_boundInt(g);
    temp_boundInt(b);
    (*this).x = (static_cast<unsigned int>(r) << 24u) | (static_cast<unsigned int>(g) << 16u) | (static_cast<unsigned int>(b) << 8u) | (0xFFu);
}

SGXColourRGBA::SGXColourRGBA(float r, float g, float b, float a){
    temp_boundFloat(r);
    temp_boundFloat(g);
    temp_boundFloat(b);
    temp_boundFloat(a);
    (*this).x = (temp_floatToUnsignedInt(r) << 24U) | (temp_floatToUnsignedInt(g) << 16U) | (temp_floatToUnsignedInt(b) << 8U) | (temp_floatToUnsignedInt(a));
}

SGXColourRGBA::SGXColourRGBA(float r, float g, float b){
    temp_boundFloat(r);
    temp_boundFloat(g);
    temp_boundFloat(b);
    (*this).x = (temp_floatToUnsignedInt(r) << 24U) | (temp_floatToUnsignedInt(g) << 16U) | (temp_floatToUnsignedInt(b) << 8U) | (0xFFu);
}
