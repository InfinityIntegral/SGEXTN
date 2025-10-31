#ifndef SGXSINGCORRECTQUICKINTERFACE_H
#define SGXSINGCORRECTQUICKINTERFACE_H

#include <QObject>
#include <qtmetamacros.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SG_WIDGETS_DLL SGXSingCorrectQuickInterface : public QObject
{
    Q_OBJECT
public:
    SGXSingCorrectQuickInterface() = default;
    [[nodiscard]] Q_INVOKABLE QString correct(const QString& s) const;
};

#endif // SGXSINGCORRECTQUICKINTERFACE_H
