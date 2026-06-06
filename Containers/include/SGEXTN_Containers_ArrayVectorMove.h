#pragma once

namespace SGEXTN {
namespace Containers {
template <typename T> class ArrayVectorMove {
public:
    static Vector<T> convertToVectorAndDestroyArray(SGEXTN::Containers::Array<T>& arr);
    static SGEXTN::Containers::Array<T> convertToArrayAndDestroyVector(Vector<T>& vec);
};
}
}

#include <private_api/SGEXTN_Containers_ArrayVectorMove_impl.h>