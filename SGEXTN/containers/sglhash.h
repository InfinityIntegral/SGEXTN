#ifndef SGLHASH_H
#define SGLHASH_H

#include "sglspan.h"
#include "sglhashalgorithm.h"

template <typename T> class SGLHash {
public:
    [[nodiscard]] int operator()(const T& x) const;
};

template <typename T> int SGLHash<T>::operator()(const T& x) const {
    return x.hash();
}

template <typename T> class SGLHash<T*> {
public:
    [[nodiscard]] int operator()(T* const & x) const;
};

template <typename T> int SGLHash<T*>::operator()(T* const & x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(T*)));
}

template <> class SGLHash<bool> {
public:
    [[nodiscard]] int operator()(const bool& x) const;
};

inline int SGLHash<bool>::operator()(const bool& x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(bool)));
}

template <> class SGLHash<char> {
public:
    [[nodiscard]] int operator()(const char& x) const;
};

inline int SGLHash<char>::operator()(const char& x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(char)));
}

template <> class SGLHash<signed char> {
public:
    [[nodiscard]] int operator()(const signed char& x) const;
};

inline int SGLHash<signed char>::operator()(const signed char& x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(signed char)));
}

template <> class SGLHash<unsigned char> {
public:
    [[nodiscard]] int operator()(const unsigned char& x) const;
};

inline int SGLHash<unsigned char>::operator()(const unsigned char& x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(&x, sizeof(unsigned char)));
}

template <> class SGLHash<short> {
public:
    [[nodiscard]] int operator()(const short& x) const;
};

inline int SGLHash<short>::operator()(const short& x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(short)));
}

template <> class SGLHash<unsigned short> {
public:
    [[nodiscard]] int operator()(const unsigned short& x) const;
};

inline int SGLHash<unsigned short>::operator()(const unsigned short& x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(unsigned short)));
}

template <> class SGLHash<int> {
public:
    [[nodiscard]] int operator()(const int& x) const;
};

inline int SGLHash<int>::operator()(const int& x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(int)));
}

template <> class SGLHash<unsigned int> {
public:
    [[nodiscard]] int operator()(const unsigned int& x) const;
};

inline int SGLHash<unsigned int>::operator()(const unsigned int& x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(unsigned int)));
}

template <> class SGLHash<long> {
public:
    [[nodiscard]] int operator()(const long& x) const;
};

inline int SGLHash<long>::operator()(const long& x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(long)));
}

template <> class SGLHash<unsigned long> {
public:
    [[nodiscard]] int operator()(const unsigned long& x) const;
};

inline int SGLHash<unsigned long>::operator()(const unsigned long& x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(unsigned long)));
}

template <> class SGLHash<long long> {
public:
    [[nodiscard]] int operator()(const long long& x) const;
};

inline int SGLHash<long long>::operator()(const long long& x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(long long)));
}

template <> class SGLHash<unsigned long long> {
public:
    [[nodiscard]] int operator()(const unsigned long long& x) const;
};

inline int SGLHash<unsigned long long>::operator()(const unsigned long long& x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(unsigned long long)));
}

template <> class SGLHash<float> {
public:
    [[nodiscard]] int operator()(const float& x) const;
};

inline int SGLHash<float>::operator()(const float& x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(float)));
}

template <> class SGLHash<double> {
public:
    [[nodiscard]] int operator()(const double& x) const;
};

inline int SGLHash<double>::operator()(const double& x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(double)));
}

template <> class SGLHash<long double> {
public:
    [[nodiscard]] int operator()(const long double& x) const;
};

inline int SGLHash<long double>::operator()(const long double& x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(long double)));
}

#endif // SGLHASH_H
