#include <SGEXTN_Containers_Span.h>
#include <private_api/SGEXTN_Containers_HashAlgorithm.h>
#include <SGEXTN_Containers_Hash.h>

int SGEXTN::Containers::Hash<bool>::operator()(bool x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(bool)));
}

int SGEXTN::Containers::Hash<unsigned char>::operator()(unsigned char x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(unsigned char)));
}

int SGEXTN::Containers::Hash<short>::operator()(short x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(short)));
}

int SGEXTN::Containers::Hash<unsigned short>::operator()(unsigned short x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(unsigned short)));
}

int SGEXTN::Containers::Hash<int>::operator()(int x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(int)));
}

int SGEXTN::Containers::Hash<unsigned int>::operator()(unsigned int x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(unsigned int)));
}

int SGEXTN::Containers::Hash<long long>::operator()(long long x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(long long)));
}

int SGEXTN::Containers::Hash<unsigned long long>::operator()(unsigned long long x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(unsigned long long)));
}

int SGEXTN::Containers::Hash<float>::operator()(float x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(float)));
}

int SGEXTN::Containers::Hash<double>::operator()(double x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(double)));
}