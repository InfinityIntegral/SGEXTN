#ifndef SGXSINGCORRECTCORE_H
#define SGXSINGCORRECTCORE_H

#include <QObject>
#include <QString>
#include <QHash>
#include "qtmetamacros.h"
#include "sgxsingcorrectquickinterface.h"

class SGXSingCorrectCore : public QObject
{
    Q_OBJECT
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
