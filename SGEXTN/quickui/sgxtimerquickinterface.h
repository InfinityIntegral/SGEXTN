#ifndef SGXTIMERQUICKINTERFACE_H
#define SGXTIMERQUICKINTERFACE_H

#include <QObject>
#include "../timer/sgxtimer.h"
#include <qtmetamacros.h>

class SGXTimerQuickInterface : public QObject
{
    Q_OBJECT
public:
    SGXTimerQuickInterface(SGXTimer* x);
    SGXTimer* x;
signals:
    void doNothing();
public slots:
    void runFunction() const;
};

#endif // SGXTIMERQUICKINTERFACE_H
