#ifndef SGXSINGCORRECTCORE_H
#define SGXSINGCORRECTCORE_H

#include <QString>

class SGXChar;
template <typename T1, typename T2> class QHash;
class SGXSingCorrectQuickInterface;
class SGXSingCorrectCore
{
public:
    SGXSingCorrectCore() = delete;
    static QString correct(const QString& s);
    static QString correctionPrefix;
    static QHash<QString, SGXChar>* database;
    static void initialise();
    static void terminate();
    static SGXSingCorrectQuickInterface* instance;
};

#endif // SGXSINGCORRECTCORE_H
