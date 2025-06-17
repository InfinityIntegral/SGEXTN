#ifndef SGXIDENTIFIER_H
#define SGXIDENTIFIER_H

#include <QSet>
#include <QDebug>

class SGXIdentifier // GUID with registration system to avoid duplicates
{
public:
    static QSet<SGXIdentifier> identifiersList; // list of registered identifiers
    unsigned int a; // first section of identifier
    unsigned int b; // second section of identifier
    unsigned int c; // third section of identifier
    unsigned int d; // fourth section of identifier
    static const SGXIdentifier nullIdentifier; // null identifier
    SGXIdentifier() = default; // default constructor for initialisation purposes
    SGXIdentifier(bool ifValid); // generate new random non-null identifier with ifValid determining if it cannot be the same as an already registered identifier
    SGXIdentifier(int); // do not use this constructor, its only purpose is to produce the null value at the start of the programme
    SGXIdentifier(unsigned int a, unsigned int b, unsigned int c, unsigned int d, bool ifValid, int& errCode); // generates identifier from data with ifValid determining if it cannot be the same as an already registered identifier, if ifValid is true and the identifier already exists, it is created anyways but errCode is set to 1 instead of 0, errCode is set to 2 instead of 0 if the data produces a null identifier
    [[nodiscard]] int registerIdentifier() const; // registers identifier, this is not done in the constructor and must be done separately, it normally returns 0 but returns 1 if the identifier is already registered
    [[nodiscard]] int unregisterIdentifier() const; // unregisters identifier, this is not done in the destructor and must be done separately, it normally returns 0 but returns 1 if the identifier is not registered
    [[nodiscard]] bool exists() const; // check if the identifier has already been registered
    [[nodiscard]] bool operator==(SGXIdentifier x) const; // equality comparator by comparing data not struct instance memory location
    [[nodiscard]] bool operator!=(SGXIdentifier x) const; // inequality comparator by comparing data not struct instance memory location
    [[nodiscard]] bool operator<(SGXIdentifier x) const; // < comparator for use in sorted data structures
    [[nodiscard]] QString getStringForPrinting() const; // generate string to print identifier
};

inline unsigned int qHash(SGXIdentifier x, unsigned int seed = 0){
    return (x.a ^ x.b ^ x.c ^ x.d ^ seed);
}

inline QDebug operator<<(QDebug s, SGXIdentifier x){
    s << x.getStringForPrinting();
    return s;
}

#endif // SGXIDENTIFIER_H
