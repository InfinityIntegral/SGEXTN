#pragma once

namespace SGEXTN {
namespace Containers {
template <typename T> class Hash {
public:
    [[nodiscard]] int operator()(const T& x) const;
};

template <typename T> class Hash<T*> {
public:
    [[nodiscard]] int operator()(T* const& x) const;
};

template <> class Hash<bool> {
public:
    [[nodiscard]] int operator()(const bool& x) const;
};

template <> class Hash<char> {
public:
    [[nodiscard]] int operator()(const char& x) const;
};

template <> class Hash<signed char> {
public:
    [[nodiscard]] int operator()(const signed char& x) const;
};

template <> class Hash<unsigned char> {
public:
    [[nodiscard]] int operator()(const unsigned char& x) const;
};

template <> class Hash<short> {
public:
    [[nodiscard]] int operator()(const short& x) const;
};

template <> class Hash<unsigned short> {
public:
    [[nodiscard]] int operator()(const unsigned short& x) const;
};

template <> class Hash<int> {
public:
    [[nodiscard]] int operator()(const int& x) const;
};

template <> class Hash<unsigned int> {
public:
    [[nodiscard]] int operator()(const unsigned int& x) const;
};

template <> class Hash<long long> {
public:
    [[nodiscard]] int operator()(const long long& x) const;
};

template <> class Hash<unsigned long long> {
public:
    [[nodiscard]] int operator()(const unsigned long long& x) const;
};

template <> class Hash<float> {
public:
    [[nodiscard]] int operator()(const float& x) const;
};

template <> class Hash<double> {
public:
    [[nodiscard]] int operator()(const double& x) const;
};

template <> class Hash<long double> {
public:
    [[nodiscard]] int operator()(const long double& x) const;
};
}
}

#include <private_api/SGEXTN_Containers_Hash_impl.h>
