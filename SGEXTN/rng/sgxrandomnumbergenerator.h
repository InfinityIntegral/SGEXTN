#ifndef SGXRANDOMNUMBERGENERATOR_H
#define SGXRANDOMNUMBERGENERATOR_H

class SGXRandomNumberGenerator
{
public:
    SGXRandomNumberGenerator() = delete;
    static double rng0To1();
    static unsigned int rngInt32();
    static unsigned long long rngInt64();
};

#endif // SGXRANDOMNUMBERGENERATOR_H
