#ifndef SGRGRAPHICSLANGUAGETYPE_H
#define SGRGRAPHICSLANGUAGETYPE_H

#include <private_api_RI/SG_Build_RI.h>

class SG_RI_DLL SGRGraphicsLanguageType
{
public:
    SGRGraphicsLanguageType() = delete;
    enum Type{
        Float,
        UnsignedInt,
        Int
    };
};

#endif // SGRGRAPHICSLANGUAGETYPE_H
