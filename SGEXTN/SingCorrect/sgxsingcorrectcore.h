#ifndef SGXSINGCORRECTCORE_H
#define SGXSINGCORRECTCORE_H

#include "../primitives/sgxstring.h"

class SGXChar;
template <typename K, typename V, typename EqualityCheck, typename HashFunction> class SGLUnorderedMap;
template <typename T> class SGLHash;
template <typename T> class SGLEqualsTo;
class SGXSingCorrectQuickInterface;
class SGXSingCorrectCore
{
public:
    SGXSingCorrectCore() = delete;
    static SGXString correct(const SGXString& s);
    static SGXString correctionPrefix;
    static SGLUnorderedMap<SGXString, SGXChar, SGLEqualsTo<SGXString>, SGLHash<SGXString>>* database;
    static void initialise();
    static void terminate();
    static SGXSingCorrectQuickInterface* instance;
};

#endif // SGXSINGCORRECTCORE_H
