#ifndef SGXSINGCORRECTQUICKINTERFACE_H
#define SGXSINGCORRECTQUICKINTERFACE_H

#include <QObject>
#include <qtmetamacros.h>

class SGXSingCorrectQuickInterface : public QObject
{
    Q_OBJECT
public:
    SGXSingCorrectQuickInterface() = default;
    [[nodiscard]] Q_INVOKABLE QString correct(const QString& s) const;
};

#endif // SGXSINGCORRECTQUICKINTERFACE_H
