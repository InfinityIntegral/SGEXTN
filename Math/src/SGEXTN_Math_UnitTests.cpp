#include <private_api/SGEXTN_Math_UnitTests.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <SGEXTN_Math_IntegerLimits.h>
#include <SGEXTN_Math_IntegerMath.h>
#include <SGEXTN_Math_FloatConstants.h>

bool isCloseEnough(float a, float b){
    return (a > 0.999f * b && a < 1.001f * b);
}

bool SGEXTN::Math::UnitTests::checkDataSizes(){
    if(sizeof(char) != 1){SGEXTN::Containers::Crash::warn("unexpected char size");}
    if(sizeof(short) != 2){SGEXTN::Containers::Crash::warn("unpected short size");}
    if(sizeof(int) != 4){SGEXTN::Containers::Crash::warn("unexpected int size");}
    if(sizeof(long long) != 8){SGEXTN::Containers::Crash::warn("unexpected long long size");}
    if(sizeof(float) != 4){SGEXTN::Containers::Crash::warn("unexpected float size");}
    if(sizeof(double) != 8){SGEXTN::Containers::Crash::warn("unexpected double size");}
    if(sizeof(char) == 1 && sizeof(short) == 2 && sizeof(int) == 4 && sizeof(long long) == 8 && sizeof(float) == 4 && sizeof(double) == 8){return true;}
    SGEXTN::Containers::Crash::warn("avoid using types with unexpected sizes listed above on this platform");
    return false;
}

void SGEXTN::Math::UnitTests::testIntegerLimits(){
    if(static_cast<long long>(SGEXTN::Math::IntegerLimits<int>::minimum()) != -2147483648){SGEXTN::Containers::Crash::crash("SGEXTN::Math::IntegerLimits - signed minimum fail");}
    if(static_cast<long long>(SGEXTN::Math::IntegerLimits<int>::maximum()) != 2147483647){SGEXTN::Containers::Crash::crash("SGEXTN::Math::IntegerLimits - signed maximum fail");}
    if(static_cast<long long>(SGEXTN::Math::IntegerLimits<unsigned int>::minimum()) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::Math::IntegerLimits - signed minimum fail");}
    if(static_cast<long long>(SGEXTN::Math::IntegerLimits<unsigned int>::maximum()) != 4294967295){SGEXTN::Containers::Crash::crash("SGEXTN::Math::IntegerLimits - signed maximum fail");}
}

void SGEXTN::Math::UnitTests::testIntegerMath(){
    if(SGEXTN::Math::IntegerMath<int>::absoluteValue(5) != 5){SGEXTN::Containers::Crash::crash("SGEXTN::Math::IntegerMath - abs of positive fail");}
    if(SGEXTN::Math::IntegerMath<int>::absoluteValue(0) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::Math::IntegerMath - abs of zero fail");}
    if(SGEXTN::Math::IntegerMath<int>::absoluteValue(-5) != 5){SGEXTN::Containers::Crash::crash("SGEXTN::Math::IntegerMath - abs of negative fail");}
    if(SGEXTN::Math::IntegerMath<int>::maximum(0, 1) != 1 || SGEXTN::Math::IntegerMath<int>::maximum(1, 0) != 1){SGEXTN::Containers::Crash::crash("SGEXTN::Math::IntegerMath - maximum fail");}
    if(SGEXTN::Math::IntegerMath<int>::minimum(0, 1) != 0 || SGEXTN::Math::IntegerMath<int>::minimum(1, 0) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::Math::IntegerMath - minimum fail");}
    if(SGEXTN::Math::IntegerMath<int>::highestCommonFactor(10, 24) != 2){SGEXTN::Containers::Crash::crash("SGEXTN::Math::IntegerMath - HCF fail");}
    if(SGEXTN::Math::IntegerMath<int>::lowestCommonMultiple(10, 24) != 120){SGEXTN::Containers::Crash::crash("SGEXTN::Math::IntegerMath - LCM fail");}
}

void SGEXTN::Math::UnitTests::testFloatConstants(){
    if(isCloseEnough(SGEXTN::Math::FloatConstants<float>::eulerNumber(), 2.718281828f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatConstants - retrieve e fail");}
    if(isCloseEnough(SGEXTN::Math::FloatConstants<float>::eulerNumberLog2(), 1.442695041f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatConstants - retrieve log 2 of e fail");}
    if(isCloseEnough(SGEXTN::Math::FloatConstants<float>::eulerNumberLog10(), 0.4342944819f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatConstants - retrieve log 10 of e fail");}
    if(isCloseEnough(SGEXTN::Math::FloatConstants<float>::goldenRatio(), 1.618033989f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatConstants - retrieve golden ratio fail");}
    if(isCloseEnough(SGEXTN::Math::FloatConstants<float>::naturalLog2(), 0.6931471806f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatConstants - retrieve ln 2 fail");}
    if(isCloseEnough(SGEXTN::Math::FloatConstants<float>::naturalLog10(), 2.302585093f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatConstants - retrieve ln 10 fail");}
    if(isCloseEnough(SGEXTN::Math::FloatConstants<float>::pi(), 3.14159265358f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatConstants - retrieve pi fail");}
    if(isCloseEnough(SGEXTN::Math::FloatConstants<float>::squareRoot2(), 1.414213562f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatConstants - retrieve sqrt 2 fail");}
    if(isCloseEnough(SGEXTN::Math::FloatConstants<float>::squareRoot3(), 1.732050808f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatConstants - retrieve sqrt 3 fail");}
}

void SGEXTN::Math::UnitTests::testAll(){
    bool x = SGEXTN::Math::UnitTests::checkDataSizes();
    if(x == true){
        SGEXTN::Math::UnitTests::testIntegerLimits();
        SGEXTN::Math::UnitTests::testIntegerMath();
    }
    SGEXTN::Math::UnitTests::testFloatConstants();
}
