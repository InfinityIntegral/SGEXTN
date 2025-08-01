#ifndef SGXSINGCORRECTCORE_H
#define SGXSINGCORRECTCORE_H

#include <QObject>
#include <QString>
#include <QHash>
#include "qtmetamacros.h"
#include "sgxsingcorrectquickinterface.h"

class SGXSingCorrectCore : public QObject // class containing SingCorrect resources
{
    Q_OBJECT
public:
    SGXSingCorrectCore() = delete;
    static QString correct(const QString& s); // correction function that actually does the replacing text
    static QString correctionPrefix; // prefix used to detect commands, default is SG-\ and user will be able to customise this in the corresponding settings page
    static QHash<QString, QChar>* database; // command database with information about SingCorrect commands
    static void initialise(); // creates command database
    static void terminate(); // frees resources
    static SGXSingCorrectQuickInterface* instance; // singleton instance for use by QML
};

#endif // SGXSINGCORRECTCORE_H
