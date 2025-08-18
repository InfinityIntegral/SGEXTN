#ifndef SGXTIMER_H
#define SGXTIMER_H

#include <QObject>
#include <QTimer>
#include <qtmetamacros.h>

class SGXTimer : public QObject
{
    Q_OBJECT
public:
    SGXTimer(float t, void (*attachedFunction)());
    SGXTimer(bool x, float t, void (*attachedFunction)());
    SGXTimer(const SGXTimer&) = delete;
    SGXTimer& operator=(const SGXTimer&) = delete;
    SGXTimer(SGXTimer&&) = delete;
    SGXTimer& operator=(SGXTimer&&) = delete;
    ~SGXTimer() override;
    void stop() const;
    void start() const;
    void (*attachedFunction)();
    QTimer* timer;
    [[nodiscard]] float getInterval() const;
    void setInterval(float t);
    static void singleCall(float t, void (*attachedFunction)());
protected:
    float interval;
private:
    bool onceOnly;
public slots:
    void runFunction();
};

#endif // SGXTIMER_H
