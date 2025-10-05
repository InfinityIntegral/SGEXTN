#include "sgxrandomnumbergenerator.h"
#include <QRandomGenerator>

unsigned int SGXRandomNumberGenerator::rngInt32(){
    return (*QRandomGenerator::global()).generate();
}

double SGXRandomNumberGenerator::rng0To1(){
    return (*QRandomGenerator::global()).generateDouble();
}

unsigned long long SGXRandomNumberGenerator::rngInt64(){
    return (*QRandomGenerator::global()).generate64();
}
