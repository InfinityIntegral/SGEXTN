#include <private_api/SGEXTN_Math_UnitTests.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <SGEXTN_Math_IntegerLimits.h>
#include <SGEXTN_Math_IntegerMath.h>
#include <SGEXTN_Math_FloatConstants.h>
#include <SGEXTN_Math_FloatLimits.h>
#include <SGEXTN_Math_FloatMath.h>

namespace {
bool isCloseEnough(float a, float b){
    if(b > 0.0f){return (a > 0.999f * b && a < 1.001f * b);}
    return (a < 0.999f * b && a > 1.001f * b);
}
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

// NOLINTBEGIN
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
// NOLINTEND

void SGEXTN::Math::UnitTests::testFloatLimits(){
    if(SGEXTN::Math::FloatLimits<float>::minimumPositive() >= 0.000001f || SGEXTN::Math::FloatLimits<float>::minimumPositive() <= 0.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatLimits - min positive fail");}
    if(SGEXTN::Math::FloatLimits<float>::maximumNegative() <= -0.000001f || SGEXTN::Math::FloatLimits<float>::maximumNegative() >= 0.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatLimits - max negative fail");}
    if(SGEXTN::Math::FloatLimits<float>::maximumFinite() <= 100000.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatLimits - max finite fail");}
    if(SGEXTN::Math::FloatLimits<float>::minimumFinite() >= -100000.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatLimits - min finite fail");}
    if(SGEXTN::Math::FloatLimits<float>::denormalisedMinimumPositive() >= 0.000001f || SGEXTN::Math::FloatLimits<float>::denormalisedMinimumPositive() <= 0.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatLimits - denorm min positive fail");}
    if(SGEXTN::Math::FloatLimits<float>::denormalisedMaximumNegative() <= -0.000001f || SGEXTN::Math::FloatLimits<float>::denormalisedMaximumNegative() >= 0.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatLimits - denorm max negative fail");}
    if(1.0f == 1.0f + SGEXTN::Math::FloatLimits<float>::relativeIncrementGap()){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatLimits - relative increment fail");}
    if(SGEXTN::Math::FloatLimits<float>::positiveInfinity() <= 100000.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatLimits - positive infinity fail");}
    if(SGEXTN::Math::FloatLimits<float>::negativeInfinity() >= -100000.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatLimits - negative infinity fail");}
    // NOLINTBEGIN
    if(SGEXTN::Math::FloatLimits<float>::notANumber() == SGEXTN::Math::FloatLimits<float>::notANumber()){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatLimits - NaN generation fail");}
    // NOLINTEND
    if(SGEXTN::Math::FloatLimits<float>::isInfinite(SGEXTN::Math::FloatLimits<float>::positiveInfinity()) == false || SGEXTN::Math::FloatLimits<float>::isInfinite(SGEXTN::Math::FloatLimits<float>::negativeInfinity()) == false || SGEXTN::Math::FloatLimits<float>::isInfinite(0.0f) == true){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatLimits - infinity detection fail");}
    if(SGEXTN::Math::FloatLimits<float>::isNotANumber(SGEXTN::Math::FloatLimits<float>::notANumber()) == false || SGEXTN::Math::FloatLimits<float>::isNotANumber(0.0f) == true){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatLimits - NaN detection fail");}
}

void SGEXTN::Math::UnitTests::testFloatMath(){
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::absoluteValue(-1.0f), 1.0f) == false || isCloseEnough(SGEXTN::Math::FloatMath<float>::absoluteValue(1.0f), 1.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - absolute value fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::modulo(5.0f, 2.0f), 1.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - modulo fail");}
    if(SGEXTN::Math::FloatMath<float>::maximum(0.0f, 1.0f) != 1.0f || SGEXTN::Math::FloatMath<float>::maximum(1.0f, 0.0f) != 1.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - maximum fail");}
    if(SGEXTN::Math::FloatMath<float>::minimum(0.0f, 1.0f) != 0.0f || SGEXTN::Math::FloatMath<float>::minimum(1.0f, 0.0f) != 0.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - minimum fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::powerOfE(1.0f), SGEXTN::Math::FloatConstants<float>::eulerNumber()) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - power of e fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::powerOf2(4.0f), 16.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - power of 2 fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::naturalLog(SGEXTN::Math::FloatConstants<float>::eulerNumber()), 1.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - natural log fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::logBase2(0.5f), -1.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - log base 2 fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::logBase10(0.01f), -2.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - log base 10 fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::powerOf(9.0f, 0.5f), 3.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - power fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::squareRoot(9.0f), 3.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - sqrt fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::cubeRoot(8.0f), 2.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - cbrt fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::sine(SGEXTN::Math::FloatConstants<float>::pi() / 2.0f), 1.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - sine fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::cosine(SGEXTN::Math::FloatConstants<float>::pi()), -1.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - cosine fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::tangent(SGEXTN::Math::FloatConstants<float>::pi() / 3.0f), SGEXTN::Math::FloatConstants<float>::squareRoot3()) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - tangent fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::arcsine(0.5f), SGEXTN::Math::FloatConstants<float>::pi() / 6.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - arcsine fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::arccosine(0.5f), SGEXTN::Math::FloatConstants<float>::pi() / 3.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - arccosine fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::arctangent(1.0f), SGEXTN::Math::FloatConstants<float>::pi() / 4.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - arctangent fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::arctangentQuadrantAware(5.0f, 5.0f), SGEXTN::Math::FloatConstants<float>::pi() / 4.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - quadrant aware arctangent fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::extendedFactorial(4.0f), 24.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - extended factorial fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::errorFunction(0.5f), 0.52050f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - normal distribution left side fail");}
    if(isCloseEnough(SGEXTN::Math::FloatMath<float>::complementaryErrorFunction(0.5f), 0.47950f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - normal distribution right side fail");}
    if(SGEXTN::Math::FloatMath<float>::ceiling(0.5f) != 1.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - ceiling function fail");}
    if(SGEXTN::Math::FloatMath<float>::ceilingToInt(0.5f) != 1){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - ceiling to int function fail");}
    if(SGEXTN::Math::FloatMath<float>::floor(0.5f) != 0.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - floor function fail");}
    if(SGEXTN::Math::FloatMath<float>::floorToInt(0.5f) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - floor to int function fail");}
    if(SGEXTN::Math::FloatMath<float>::round(0.4f) != 0.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - round function fail");}
    if(SGEXTN::Math::FloatMath<float>::roundToInt(0.4f) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::Math::FloatMath - round to int function fail");}
}

void SGEXTN::Math::UnitTests::testAll(){
    const bool x = SGEXTN::Math::UnitTests::checkDataSizes();
    if(x == true){
        SGEXTN::Math::UnitTests::testIntegerLimits();
        SGEXTN::Math::UnitTests::testIntegerMath();
    }
    SGEXTN::Math::UnitTests::testFloatConstants();
    SGEXTN::Math::UnitTests::testFloatLimits();
    SGEXTN::Math::UnitTests::testFloatMath();
}
