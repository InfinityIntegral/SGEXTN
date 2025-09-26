#ifndef SGXSINGCORRECTCORE_H
#define SGXSINGCORRECTCORE_H

#include "../primitives/sgxstring.h"

class SGXChar;
template <typename T1, typename T2> class QHash;
class SGXSingCorrectQuickInterface;
class SGXSingCorrectCore
{
public:
    SGXSingCorrectCore() = delete;
    static SGXString correct(const SGXString& s);
    static SGXString correctionPrefix;
    static QHash<SGXString, SGXChar>* database;
    static void initialise();
    static void terminate();
    static SGXSingCorrectQuickInterface* instance;
};

#endif // SGXSINGCORRECTCORE_H
