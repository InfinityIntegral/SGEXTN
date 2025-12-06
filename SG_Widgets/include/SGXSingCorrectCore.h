#ifndef SGXSINGCORRECTCORE_H
#define SGXSINGCORRECTCORE_H

#include <SGXString.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SGXChar;
template <typename K, typename V, typename EqualityCheck, typename HashFunction> class SGLUnorderedMap;
template <typename T> class SGLHash;
template <typename T> class SGLEqualsTo;
class SGXSingCorrectQuickInterface;
class SG_WIDGETS_DLL SGXSingCorrectCore
{
public:
    SGXSingCorrectCore() = delete;
    static SGXString correct(const SGXString& s);
    static SGXString correctionPrefix;
    static SGLUnorderedMap<SGXString, SGXChar, SGLEqualsTo<SGXString>, SGLHash<SGXString>>* database;
    static void initialise();
    static SGXSingCorrectQuickInterface* instance;
};

#endif // SGXSINGCORRECTCORE_H
