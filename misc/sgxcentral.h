#ifndef SGXCENTRAL_H
#define SGXCENTRAL_H

#include <QObject>

class SGXCentral : public QObject // non instantiable class for essential application data that should not be modified by the user
{
    Q_OBJECT // NOLINT
public:
    SGXCentral() = delete;
    SGXCentral(const SGXCentral&) = delete;
    SGXCentral(SGXCentral&&) = delete;
    SGXCentral& operator=(const SGXCentral&) = delete;
    SGXCentral& operator=(SGXCentral&&) = delete;
    ~SGXCentral() override = default;
    static void initialise(); // initialisation function run when app opens
    static void terminate(); // termination function run when app closes
};

#endif // SGXCENTRAL_H
