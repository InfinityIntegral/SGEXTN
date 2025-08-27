#ifndef SGXSINGCORRECTCORE_H
#define SGXSINGCORRECTCORE_H

#include <QString>
#include <QHash>
#include "../quickui/sgxsingcorrectquickinterface.h"

class SGXSingCorrectCore
{
public:
    SGXSingCorrectCore() = delete;
    static QString correct(const QString& s);
    static QString correctionPrefix;
    static QHash<QString, QChar>* database;
    static void initialise();
    static void terminate();
    static SGXSingCorrectQuickInterface* instance;
};

#endif // SGXSINGCORRECTCORE_H
