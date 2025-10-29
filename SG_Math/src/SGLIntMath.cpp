#include <SGLIntMath.h>
#include <numeric>

int SGLIntMath::absoluteValue(int x){
    if(x < 0){return (-1) * x;}
    return x;
}

int SGLIntMath::minimum(int a, int b){
    if(a < b){return a;}
    return b;
}

int SGLIntMath::maximum(int a, int b){
    if(a > b){return a;}
    return b;
}

int SGLIntMath::highestCommonFactor(int a, int b){
    return std::gcd(a, b);
}

int SGLIntMath::lowestCommonMultiple(int a, int b){
    return std::lcm(a, b);
}
