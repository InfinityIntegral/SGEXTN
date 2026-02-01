#include <SGEXTN_ApplicationBase_Random.h>
#include <QRandomGenerator>

float SGEXTN::ApplicationBase::Random::normalisedFloat(){
    return static_cast<float>((*QRandomGenerator::global()).generateDouble());
}

double SGEXTN::ApplicationBase::Random::normalisedDouble(){
    return (*QRandomGenerator::global()).generateDouble();
}

int SGEXTN::ApplicationBase::Random::signedInt32(){
    return static_cast<int>((*QRandomGenerator::global()).generate());
}

unsigned int SGEXTN::ApplicationBase::Random::unsignedInt32(){
    return (*QRandomGenerator::global()).generate();
}

long long SGEXTN::ApplicationBase::Random::signedInt64(){
    return static_cast<long long>((*QRandomGenerator::global()).generate64());
}

unsigned long long SGEXTN::ApplicationBase::Random::unsignedInt64(){
    return (*QRandomGenerator::global()).generate64();
}
