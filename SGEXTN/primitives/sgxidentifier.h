#ifndef SGXIDENTIFIER_H
#define SGXIDENTIFIER_H

#include <QSet>
#include <QDebug>

class SGXIdentifier
{
public:
    static QSet<SGXIdentifier> identifiersList;
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
    static const SGXIdentifier nullIdentifier;
    SGXIdentifier() = default;
    SGXIdentifier(bool ifValid);
    SGXIdentifier(int);
    SGXIdentifier(unsigned int a, unsigned int b, unsigned int c, unsigned int d, bool ifValid, int* errCode);
    SGXIdentifier(const QString& s, bool ifValid, int* errCode);
    [[nodiscard]] int registerIdentifier() const;
    [[nodiscard]] int unregisterIdentifier() const;
    [[nodiscard]] bool exists() const;
    [[nodiscard]] bool operator==(SGXIdentifier x) const;
    [[nodiscard]] bool operator!=(SGXIdentifier x) const;
    [[nodiscard]] bool operator<(SGXIdentifier x) const;
    [[nodiscard]] QString getStringForPrinting() const;
};

inline unsigned int qHash(SGXIdentifier x, unsigned int seed = 0){
    return (x.a ^ x.b ^ x.c ^ x.d ^ seed);
}

inline QDebug operator<<(QDebug s, SGXIdentifier x){
    s << x.getStringForPrinting();
    return s;
}

#endif // SGXIDENTIFIER_H
