#include "sgllonglonglimits.h"
#include <limits>

long long SGLLongLongLimits::maximum(){
    return std::numeric_limits<long long>::max();
}

long long SGLLongLongLimits::minimum(){
    return std::numeric_limits<long long>::min();
}
