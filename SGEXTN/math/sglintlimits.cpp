#include "sglintlimits.h"
#include <limits>

int SGLIntLimits::maximum(){
    return std::numeric_limits<int>::max();
}

int SGLIntLimits::minimum(){
    return std::numeric_limits<int>::min();
}
