#ifndef SGXTIMERQUICKINTERFACE_H
#define SGXTIMERQUICKINTERFACE_H

#include <QObject>

#include <private_api_Core/SG_Build_Core.h>

class SG_CORE_DLL SGXTimer;
class SGXTimerQuickInterface : public QObject
{
public:
    SGXTimerQuickInterface(SGXTimer* x);
    SGXTimer* x;
    void runFunction() const;
};

#endif // SGXTIMERQUICKINTERFACE_H
