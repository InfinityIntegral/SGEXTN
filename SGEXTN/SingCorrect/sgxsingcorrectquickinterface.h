#ifndef SGXSINGCORRECTQUICKINTERFACE_H
#define SGXSINGCORRECTQUICKINTERFACE_H

#include <QObject>
#include <qtmetamacros.h>

class SGXSingCorrectQuickInterface : public QObject // class allowing SingCorrect to be used in QML
{
    Q_OBJECT
public:
    SGXSingCorrectQuickInterface() = default;
    [[nodiscard]] Q_INVOKABLE QString correct(const QString& s) const; // wraps corresponding SGXSingCorrectCore static function for use in QML
};

#endif // SGXSINGCORRECTQUICKINTERFACE_H
