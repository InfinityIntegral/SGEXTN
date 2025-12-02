#ifndef SGXTIMERQUICKINTERFACE_H
#define SGXTIMERQUICKINTERFACE_H

#include <QObject>

#include <private_api_Core/SG_Build_Core.h>

class SGXTimer;
class SG_CORE_DLL SGXTimerQuickInterface : public QObject
{
public:
    SGXTimerQuickInterface(SGXTimer* x);
    SGXTimer* x;
    void runFunction() const;
    void actuallyDeleteTimer() const;
};

#endif // SGXTIMERQUICKINTERFACE_H
