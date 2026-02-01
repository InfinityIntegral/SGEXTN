#pragma once

class QTimer;
namespace SGEXTN {
namespace ApplicationBase {
class QObjTimerInterface;
class BUILDLAH_DLL_SGEXTN_ApplicationBase Timer {
public:
    Timer(float t, void (*attachedFunction)());
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
    Timer(Timer&&) = delete;
    Timer& operator=(Timer&&) = delete;
    ~Timer();
    void stop() const;
    void start() const;
    void (*attachedFunction)();
    static void singleCall(float t, void (*attachedFunction)());
    void deleteTimer();
    void private_runFunction();
    QTimer* private_timer;
    float private_interval;
    bool private_once;
    bool private_deleted;
    SGEXTN::ApplicationBase::QObjTimerInterface* private_q;
};
}
}
