#ifndef SGXCENTRAL_H
#define SGXCENTRAL_H

#include <QObject>
#include <qtmetamacros.h>

class SGXCentral : public QObject // non instantiable class for essential application data that should not be modified by the user
{
    Q_OBJECT
public:
    SGXCentral() = delete;
    static void initialise(); // initialisation function run when app opens
    static void terminate(); // termination function run when app closes
};

#endif // SGXCENTRAL_H
