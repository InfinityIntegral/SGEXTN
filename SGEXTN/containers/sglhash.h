#ifndef SGLHASH_H
#define SGLHASH_H

#include "sglspan.h"
#include "sglhashalgorithm.h"

template <typename T> class SGLHash {
public:
    [[nodiscard]] int operator()(T x) const;
};

template <typename T> int SGLHash<T>::operator()(T x) const {
    return x.hash();
}

template <> class SGLHash<bool> {
public:
    [[nodiscard]] int operator()(bool x) const;
};

inline int SGLHash<bool>::operator()(bool x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(bool)));
}

template <> class SGLHash<char> {
public:
    [[nodiscard]] int operator()(char x) const;
};

inline int SGLHash<char>::operator()(char x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(char)));
}

template <> class SGLHash<signed char> {
public:
    [[nodiscard]] int operator()(signed char x) const;
};

inline int SGLHash<signed char>::operator()(signed char x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(signed char)));
}

template <> class SGLHash<unsigned char> {
public:
    [[nodiscard]] int operator()(unsigned char x) const;
};

inline int SGLHash<unsigned char>::operator()(unsigned char x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(unsigned char)));
}

template <> class SGLHash<short> {
public:
    [[nodiscard]] int operator()(short x) const;
};

inline int SGLHash<short>::operator()(short x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(short)));
}

template <> class SGLHash<unsigned short> {
public:
    [[nodiscard]] int operator()(unsigned short x) const;
};

inline int SGLHash<unsigned short>::operator()(unsigned short x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(unsigned short)));
}

template <> class SGLHash<int> {
public:
    [[nodiscard]] int operator()(int x) const;
};

inline int SGLHash<int>::operator()(int x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(int)));
}

template <> class SGLHash<unsigned int> {
public:
    [[nodiscard]] int operator()(unsigned int x) const;
};

inline int SGLHash<unsigned int>::operator()(unsigned int x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(unsigned int)));
}

template <> class SGLHash<long> {
public:
    [[nodiscard]] int operator()(long x) const;
};

inline int SGLHash<long>::operator()(long x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(long)));
}

template <> class SGLHash<unsigned long> {
public:
    [[nodiscard]] int operator()(unsigned long x) const;
};

inline int SGLHash<unsigned long>::operator()(unsigned long x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(unsigned long)));
}

template <> class SGLHash<long long> {
public:
    [[nodiscard]] int operator()(long long x) const;
};

inline int SGLHash<long long>::operator()(long long x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(long long)));
}

template <> class SGLHash<unsigned long long> {
public:
    [[nodiscard]] int operator()(unsigned long long x) const;
};

inline int SGLHash<unsigned long long>::operator()(unsigned long long x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(unsigned long long)));
}

template <> class SGLHash<float> {
public:
    [[nodiscard]] int operator()(float x) const;
};

inline int SGLHash<float>::operator()(float x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(float)));
}

template <> class SGLHash<double> {
public:
    [[nodiscard]] int operator()(double x) const;
};

inline int SGLHash<double>::operator()(double x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(double)));
}

template <> class SGLHash<long double> {
public:
    [[nodiscard]] int operator()(long double x) const;
};

inline int SGLHash<long double>::operator()(long double x) const {
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(long double)));
}

#endif // SGLHASH_H
