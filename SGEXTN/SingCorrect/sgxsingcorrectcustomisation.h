#ifndef SGXSINGCORRECTCUSTOMISATION_H
#define SGXSINGCORRECTCUSTOMISATION_H

class SGXChar;
class SGXString;
template <typename T1, typename T2> class QHash;
class SGXSingCorrectCustomisation
{
public:
    SGXSingCorrectCustomisation() = delete;
    static void loadFileData();
    static void syncFileData();
    static QHash<SGXString, SGXChar>* database;
    static bool moduleEnabled;
};

#endif // SGXSINGCORRECTCUSTOMISATION_H
