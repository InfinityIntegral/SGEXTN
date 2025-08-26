#ifndef SGXCENTRAL_H
#define SGXCENTRAL_H

#include <QObject>
#include <qtmetamacros.h>

class SGXCentral : public QObject
{
    Q_OBJECT
public:
    SGXCentral() = delete;
    static void initialise();
    static void terminate();
};

#endif // SGXCENTRAL_H
