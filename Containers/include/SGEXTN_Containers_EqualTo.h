#pragma once

namespace SGEXTN {
namespace Containers {
template <typename T> class EqualTo {
public:
    [[nodiscard]] bool operator()(const T& a, const T& b) const;
};

template <typename T> class EqualTo<T*> {
public:
    [[nodiscard]] bool operator()(const T* a, const T* b) const;
};

template <typename ReturnType, typename... ArgTypes> class EqualTo<ReturnType (*)(ArgTypes...)> {
public:
    [[nodiscard]] bool operator()(ReturnType (*a)(ArgTypes...), ReturnType (*b)(ArgTypes...)) const;
};

template <typename ReturnType, typename ClassName, typename... ArgTypes> class EqualTo<ReturnType (ClassName::*)(ArgTypes...)> {
public:
    [[nodiscard]] bool operator()(ReturnType (ClassName::*a)(ArgTypes...), ReturnType (ClassName::*b)(ArgTypes...)) const;
};

template <typename ReturnType, typename ClassName, typename... ArgTypes> class EqualTo<ReturnType (ClassName::*)(ArgTypes...) const> {
public:
    [[nodiscard]] bool operator()(ReturnType (ClassName::*a)(ArgTypes...) const, ReturnType (ClassName::*b)(ArgTypes...) const) const;
};
}
}

#include <private_api/SGEXTN_Containers_EqualTo_impl.h>
