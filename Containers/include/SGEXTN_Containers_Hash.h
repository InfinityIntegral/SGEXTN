#pragma once

namespace SGEXTN {
namespace Containers {
template <typename... Ts> class Hash {
public:
    [[nodiscard]] int operator()(Ts... args) const;
};

template <typename T> class Hash<T> {
public:
    [[nodiscard]] int operator()(const T& x) const;
};

template <typename T> class Hash<T*> {
public:
    [[nodiscard]] int operator()(T* x) const;
};

template <typename ReturnType, typename... ArgTypes> class Hash<ReturnType(*)(ArgTypes...)> {
public:
    [[nodiscard]] int operator()(ReturnType(*x)(ArgTypes...)) const;
};

template <typename ReturnType, typename ClassName, typename... ArgTypes> class Hash<ReturnType(ClassName::*)(ArgTypes...)> {
public:
    [[nodiscard]] int operator()(ReturnType(ClassName::*x)(ArgTypes...)) const;
};

template <typename ReturnType, typename ClassName, typename... ArgTypes> class Hash<ReturnType(ClassName::*)(ArgTypes...)const> {
public:
    [[nodiscard]] int operator()(ReturnType(ClassName::*x)(ArgTypes...)const) const;
};

template <> class BUILDLAH_DLL_SGEXTN_Containers Hash<bool> {
public:
    [[nodiscard]] int operator()(bool x) const;
};

template <> class BUILDLAH_DLL_SGEXTN_Containers Hash<unsigned char> {
public:
    [[nodiscard]] int operator()(unsigned char x) const;
};

template <> class BUILDLAH_DLL_SGEXTN_Containers Hash<short> {
public:
    [[nodiscard]] int operator()(short x) const;
};

template <> class BUILDLAH_DLL_SGEXTN_Containers Hash<unsigned short> {
public:
    [[nodiscard]] int operator()(unsigned short x) const;
};

template <> class BUILDLAH_DLL_SGEXTN_Containers Hash<int> {
public:
    [[nodiscard]] int operator()(int x) const;
};

template <> class BUILDLAH_DLL_SGEXTN_Containers Hash<unsigned int> {
public:
    [[nodiscard]] int operator()(unsigned int x) const;
};

template <> class BUILDLAH_DLL_SGEXTN_Containers Hash<long long> {
public:
    [[nodiscard]] int operator()(long long x) const;
};

template <> class BUILDLAH_DLL_SGEXTN_Containers Hash<unsigned long long> {
public:
    [[nodiscard]] int operator()(unsigned long long x) const;
};

template <> class BUILDLAH_DLL_SGEXTN_Containers Hash<float> {
public:
    [[nodiscard]] int operator()(float x) const;
};

template <> class BUILDLAH_DLL_SGEXTN_Containers Hash<double> {
public:
    [[nodiscard]] int operator()(double x) const;
};
}
}

#include <private_api/SGEXTN_Containers_Hash_impl.h>
