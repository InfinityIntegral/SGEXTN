#ifndef SGLCRASH_H
#define SGLCRASH_H

#include <private_api_Containers/SG_Build_Containers.h>

class SG_CONTAINERS_DLL SGLCrash
{
public:
    static void crash();
    static void crashOnInsert();
    static void crashOnRemove();
};

#endif // SGLCRASH_H
