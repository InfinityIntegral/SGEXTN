#pragma once
#include <SGEXTN_Containers_Span.h>
#include <SGEXTN_Containers_HashAlgorithm.h>

template <typename T> int SGEXTN::Containers::Hash<T>::operator()(const T& x) const {
    return x.hash();
}

template <typename T> int SGEXTN::Containers::Hash<T*>::operator()(T* const& x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(T*)));
}

inline int SGEXTN::Containers::Hash<bool>::operator()(const bool& x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(bool)));
}

inline int SGEXTN::Containers::Hash<char>::operator()(const char& x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(char)));
}

inline int SGEXTN::Containers::Hash<signed char>::operator()(const signed char& x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(signed char)));
}

inline int SGEXTN::Containers::Hash<unsigned char>::operator()(const unsigned char& x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(unsigned char)));
}

inline int SGEXTN::Containers::Hash<short>::operator()(const short& x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(short)));
}

inline int SGEXTN::Containers::Hash<unsigned short>::operator()(const unsigned short& x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(unsigned short)));
}

inline int SGEXTN::Containers::Hash<int>::operator()(const int& x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(int)));
}

inline int SGEXTN::Containers::Hash<unsigned int>::operator()(const unsigned int& x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(unsigned int)));
}

inline int SGEXTN::Containers::Hash<long long>::operator()(const long long& x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(long long)));
}

inline int SGEXTN::Containers::Hash<unsigned long long>::operator()(const unsigned long long& x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(unsigned long long)));
}

inline int SGEXTN::Containers::Hash<float>::operator()(const float& x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(float)));
}

inline int SGEXTN::Containers::Hash<double>::operator()(const double& x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(double)));
}

inline int SGEXTN::Containers::Hash<long double>::operator()(const long double& x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(long double)));
}
