#ifndef SGXTIMER_H
#define SGXTIMER_H

#include <QTimer>

class SGXTimerQuickInterface;
class SGXTimer
{
public:
    SGXTimer(float t, void (*attachedFunction)());
    SGXTimer(bool x, float t, void (*attachedFunction)());
    SGXTimer(const SGXTimer&) = delete;
    SGXTimer& operator=(const SGXTimer&) = delete;
    SGXTimer(SGXTimer&&) = delete;
    SGXTimer& operator=(SGXTimer&&) = delete;
    ~SGXTimer();
    void stop() const;
    void start() const;
    void (*attachedFunction)();
    QTimer* timer;
    static void singleCall(float t, void (*attachedFunction)());
    void runFunction();
protected:
    float interval;
    bool onceOnly;
    SGXTimerQuickInterface* quickInterface;
};

#endif // SGXTIMER_H
