#pragma once
#include <QObject>

namespace SGEXTN {
namespace ApplicationBase {
class Timer;
class BUILDLAH_DLL_SGEXTN_ApplicationBase QObjTimerInterface : public QObject {
public:
    QObjTimerInterface(SGEXTN::ApplicationBase::Timer* x);
    SGEXTN::ApplicationBase::Timer* x;
    void runFunction() const;
    void actuallyDeleteTimer() const;
};
}
}
