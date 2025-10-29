#ifndef SGXIDENTIFIER_H
#define SGXIDENTIFIER_H

#include <SGXString.h>

#include <private_api_Core/SG_Build_Core.h>

template <typename T, typename EqualityCheck, typename HashFunction> class SGLUnorderedSet;
template <typename T> class SGLEqualsTo;
template <typename T> class SGLHash;
class SG_CORE_DLL SGXIdentifier
{
public:
    static SGLUnorderedSet<SGXIdentifier, SGLEqualsTo<SGXIdentifier>, SGLHash<SGXIdentifier>>* identifiersList;
    static void terminate();
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
    static const SGXIdentifier nullIdentifier;
    SGXIdentifier() = default;
    SGXIdentifier(bool ifValid);
    SGXIdentifier(int);
    SGXIdentifier(unsigned int a, unsigned int b, unsigned int c, unsigned int d, bool ifValid, int* errCode);
    SGXIdentifier(const SGXString& s, bool ifValid, int* errCode);
    [[nodiscard]] int registerIdentifier() const;
    [[nodiscard]] int unregisterIdentifier() const;
    [[nodiscard]] bool exists() const;
    [[nodiscard]] bool operator==(SGXIdentifier x) const;
    [[nodiscard]] bool operator!=(SGXIdentifier x) const;
    [[nodiscard]] bool operator<(SGXIdentifier x) const;
    [[nodiscard]] bool operator>(SGXIdentifier x) const;
    [[nodiscard]] int hash() const;
    [[nodiscard]] SGXString getStringForPrinting() const;
};

#endif // SGXIDENTIFIER_H
