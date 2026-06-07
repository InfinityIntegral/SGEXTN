#pragma once

namespace SGEXTN {
namespace Containers {
template <typename T> class MoreThan {
public:
    [[nodiscard]] bool operator()(const T& a, const T& b) const;
};

template <typename T> class MoreThan<T*> {
public:
    [[nodiscard]] bool operator()(T* a, T* b) const;
};

template <typename ReturnType, typename... ArgTypes> class MoreThan<ReturnType(*)(ArgTypes...)> {
public:
    [[nodiscard]] bool operator()(ReturnType(*a)(ArgTypes...), ReturnType(*b)(ArgTypes...)) const;
};

template <typename ReturnType, typename ClassName, typename... ArgTypes> class MoreThan<ReturnType(ClassName::*)(ArgTypes...)> {
public:
    [[nodiscard]] bool operator()(ReturnType(ClassName::*a)(ArgTypes...), ReturnType(ClassName::*b)(ArgTypes...)) const;
};

template <typename ReturnType, typename ClassName, typename... ArgTypes> class MoreThan<ReturnType(ClassName::*)(ArgTypes...)const> {
public:
    [[nodiscard]] bool operator()(ReturnType(ClassName::*a)(ArgTypes...)const, ReturnType(ClassName::*b)(ArgTypes...)const) const;
};
}
}

#include <private_api/SGEXTN_Containers_MoreThan_impl.h>
