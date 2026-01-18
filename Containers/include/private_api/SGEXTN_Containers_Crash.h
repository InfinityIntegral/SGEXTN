#pragma once

namespace SGEXTN {
namespace Containers {
class BUILDLAH_DLL_SGEXTN_Containers Crash {
public:
    [[noreturn]] static void crash(const char* msg);
    static void (*logCrashMessage)(const char*);
};
}
}
