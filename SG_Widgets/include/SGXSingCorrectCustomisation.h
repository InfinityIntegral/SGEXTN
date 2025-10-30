#ifndef SGXSINGCORRECTCUSTOMISATION_H
#define SGXSINGCORRECTCUSTOMISATION_H

#include <private_api_Widgets/SG_Build_Widgets.h>

class SGXChar;
class SGXString;
template <typename K, typename V, typename EqualityCheck, typename HashFunction> class SGLUnorderedMap;
template <typename T> class SGLEqualsTo;
template <typename T> class SGLHash;
class SG_WIDGETS_DLL SGXSingCorrectCustomisation
{
public:
    SGXSingCorrectCustomisation() = delete;
    static void loadFileData();
    static void syncFileData();
    static SGLUnorderedMap<SGXString, SGXChar, SGLEqualsTo<SGXString>, SGLHash<SGXString>>* database;
    static bool moduleEnabled;
};

#endif // SGXSINGCORRECTCUSTOMISATION_H
