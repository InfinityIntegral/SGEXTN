#ifndef SGLINTMATH_H
#define SGLINTMATH_H

class SGLIntMath
{
public:
    SGLIntMath() = delete;
    static int absoluteValue(int x);
    static int minimum(int a, int b);
    static int maximum(int a, int b);
    static int lowestCommonMultiple(int a, int b);
    static int highestCommonFactor(int a, int b);
};

#endif // SGLINTMATH_H
