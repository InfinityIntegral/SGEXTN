#pragma once
#include <SGEXTN_ApplicationBase_String.h>

namespace SGEXTN {
namespace Structs {
enum class BUILDLAH_DLL_SGEXTN_Structs TimeUnit {Year, Month, Day, Hour, Minute, Second};

enum class BUILDLAH_DLL_SGEXTN_Structs TimeFormat {Display, FileName, FileNameSpaceSeparated, FileNameUnderscoreSeparated, FileNameHyphenSeparated};

class BUILDLAH_DLL_SGEXTN_Structs DateTime {
public:
    long long private_data;
    DateTime();
    DateTime(long long t);
    DateTime(int year, int month, int day, int hour, int minute, int second);
    [[nodiscard]] bool operator==(DateTime x) const;
    [[nodiscard]] bool operator!=(DateTime x) const;
    [[nodiscard]] bool operator<(DateTime x) const;
    [[nodiscard]] bool operator>(DateTime x) const;
    [[nodiscard]] bool operator<=(DateTime x) const;
    [[nodiscard]] bool operator>=(DateTime x) const;
    [[nodiscard]] int hash() const;
    [[nodiscard]] SGEXTN::ApplicationBase::String debugLog() const;
    [[nodiscard]] double getTimeAfter(DateTime x, SGEXTN::Structs::TimeUnit unit) const;
    [[nodiscard]] int getTimeAfterFlooredPart(DateTime x, SGEXTN::Structs::TimeUnit unit) const;
    void advanceTime(long long x, SGEXTN::Structs::TimeUnit unit);
    [[nodiscard]] static DateTime beginningOfTime();
    [[nodiscard]] static DateTime now();
    [[nodiscard]] int getDayOfWeek() const;
    [[nodiscard]] int getDayOfYear() const;
    [[nodiscard]] int getPart(SGEXTN::Structs::TimeUnit unit) const;
    [[nodiscard]] static int convertToGlobalYear(int standardYear);
    [[nodiscard]] bool isNationalDayPeriod() const;
    [[nodiscard]] bool isNationalDay() const;
    [[nodiscard]] bool isDayBeforeNationalDay() const;
    [[nodiscard]] bool isDayAfterNationalDay() const;
    [[nodiscard]] bool isTotalDefenceDay() const;
    [[nodiscard]] bool isRacialHarmonyDay() const;
    [[nodiscard]] SGEXTN::ApplicationBase::String getDisplayString(SGEXTN::Structs::TimeFormat format, bool global, bool correctToSecond) const;
    [[nodiscard]] SGEXTN::ApplicationBase::String getDisplayString(const SGEXTN::ApplicationBase::String& customFormat) const;
};
}
}