#include <SGLLongLongMath.h>
#include <numeric>

long long SGLLongLongMath::absoluteValue(long long x){
    if(x < 0){return (-1ll) * x;}
    return x;
}

long long SGLLongLongMath::minimum(long long a, long long b){
    if(a < b){return a;}
    return b;
}

long long SGLLongLongMath::maximum(long long a, long long b){
    if(a > b){return a;}
    return b;
}

long long SGLLongLongMath::highestCommonFactor(long long a, long long b){
    return std::gcd(a, b);
}

long long SGLLongLongMath::lowestCommonMultiple(long long a, long long b){
    return std::lcm(a, b);
}
