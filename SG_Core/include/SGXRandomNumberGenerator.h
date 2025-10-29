#ifndef SGXRANDOMNUMBERGENERATOR_H
#define SGXRANDOMNUMBERGENERATOR_H

#include <private_api_Core/SG_Build_Core.h>

class SG_CORE_DLL SGXRandomNumberGenerator
{
public:
    SGXRandomNumberGenerator() = delete;
    static double rng0To1();
    static unsigned int rngInt32();
    static unsigned long long rngInt64();
};

#endif // SGXRANDOMNUMBERGENERATOR_H
