#pragma once
#include <SGEXTN_ApplicationBase_OldString.h>
#define SG SGEXTN::ApplicationBase::Debug(__FILE__, __LINE__)

namespace SGEXTN {
namespace ApplicationBase {
class BUILDLAH_DLL_SGEXTN_ApplicationBase Debug {
public:
    Debug(const SGEXTN::ApplicationBase::OldString& fileName, int lineNumber);
    Debug(const Debug&) = delete;
    Debug& operator=(const Debug&) = delete;
    Debug(Debug&&) = delete;
    Debug& operator=(Debug&&) = delete;
    ~Debug();
    SGEXTN::ApplicationBase::OldString debugInfo;
    SGEXTN::ApplicationBase::OldString metaInfo;
    template <typename T> Debug& operator()(const T& x);
    Debug& operator()(bool x);
    Debug& operator()(unsigned char x);
    Debug& operator()(short x);
    Debug& operator()(unsigned short x);
    Debug& operator()(int x);
    Debug& operator()(unsigned int x);
    Debug& operator()(long long x);
    Debug& operator()(unsigned long long x);
    Debug& operator()(float x);
    Debug& operator()(double x);
    Debug& operator()(const SGEXTN::ApplicationBase::OldChar& x);
    Debug& operator()(const SGEXTN::ApplicationBase::OldString& x);
    Debug& operator()(const char* x);
    static SGEXTN::ApplicationBase::OldString logFile;
    static void logCrashMessage(const char* msg);
};
}
}

template <typename T> SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(const T& x){
    debugInfo += SGEXTN::ApplicationBase::OldString(" - ") + x.debugLog();
    return (*this);
}
