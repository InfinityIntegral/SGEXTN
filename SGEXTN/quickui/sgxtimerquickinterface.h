#ifndef SGXTIMERQUICKINTERFACE_H
#define SGXTIMERQUICKINTERFACE_H

#include <QObject>

class SGXTimer;
class SGXTimerQuickInterface : public QObject
{
    Q_OBJECT
public:
    SGXTimerQuickInterface(SGXTimer* x);
    SGXTimer* x;
    void runFunction() const;
};

#endif // SGXTIMERQUICKINTERFACE_H
