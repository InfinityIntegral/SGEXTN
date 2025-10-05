#include "sgxrandomnumbergenerator.h"
#include <QRandomGenerator>

unsigned int SGXRandomNumberGenerator::rng(){
    return (*QRandomGenerator::global()).generate();
}

double SGXRandomNumberGenerator::rngDouble(){
    return (*QRandomGenerator::global()).generateDouble();
}

unsigned long long SGXRandomNumberGenerator::rngLongLong(){
    return (*QRandomGenerator::global()).generate64();
}
