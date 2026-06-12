#pragma once

namespace SGEXTN {
namespace Containers {
class BUILDLAH_DLL_SGEXTN_Containers ForceCrash {
public:
    [[noreturn]] static void immediateCrash(const char* msg);
    static void basicWarn(const char* msg);
    static void logMessage(const char* prefix, const char* msg);
};
}
}

#define SGEXTN_IMMEDIATE_CRASH(msg) SGEXTN::Containers::ForceCrash::immediateCrash(msg)
#define SGEXTN_BASIC_WARN(msg) SGEXTN::Containers::ForceCrash::basicWarn(msg)