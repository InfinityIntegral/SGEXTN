#ifndef SGXRANDOMNUMBERGENERATOR_H
#define SGXRANDOMNUMBERGENERATOR_H

class SGXRandomNumberGenerator
{
public:
    SGXRandomNumberGenerator() = delete;
    static unsigned int rng();
    static double rngDouble();
    static unsigned long long rngLongLong();
};

#endif // SGXRANDOMNUMBERGENERATOR_H
