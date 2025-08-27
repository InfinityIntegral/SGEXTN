#ifndef SGXSINGCORRECTCUSTOMISATION_H
#define SGXSINGCORRECTCUSTOMISATION_H

#include <QHash>
#include <QString>
#include <QChar>

class SGXSingCorrectCustomisation
{
public:
    SGXSingCorrectCustomisation() = delete;
    static void loadFileData();
    static void syncFileData();
    static QHash<QString, QChar>* database;
    static bool moduleEnabled;
};

#endif // SGXSINGCORRECTCUSTOMISATION_H
