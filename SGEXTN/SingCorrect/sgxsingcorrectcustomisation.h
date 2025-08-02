#ifndef SGXSINGCORRECTCUSTOMISATION_H
#define SGXSINGCORRECTCUSTOMISATION_H

#include <QObject>
#include <QHash>
#include <QString>
#include <QChar>
#include <qtmetamacros.h>

class SGXSingCorrectCustomisation : public QObject
{
    Q_OBJECT
public:
    SGXSingCorrectCustomisation() = delete;
    static void loadFileData();
    static void syncFileData();
    static QHash<QString, QChar>* database;
    static bool moduleEnabled;
};

#endif // SGXSINGCORRECTCUSTOMISATION_H
