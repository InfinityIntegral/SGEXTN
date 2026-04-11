#pragma once

namespace SGEXTN {
namespace ApplicationBase {
class OldString;
}

namespace Structs {
enum class BUILDLAH_DLL_SGEXTN_Structs TimeUnit : unsigned char {Year, Month, Day, Hour, Minute, Second};

enum class BUILDLAH_DLL_SGEXTN_Structs TimeFormat : unsigned char {Display, FileName, ShortestReadable};

enum class BUILDLAH_DLL_SGEXTN_Structs SignificantDates : unsigned char {NationalDay, DayBeforeNationalDay, DayAfterNationalDay, TotalDefenceDay, RacialHarmonyDay};

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
    [[nodiscard]] SGEXTN::ApplicationBase::OldString debugLog() const;
    [[nodiscard]] double getTimeAfter(DateTime x, SGEXTN::Structs::TimeUnit unit) const;
    [[nodiscard]] static DateTime beginningOfTime();
    [[nodiscard]] static DateTime now();
    [[nodiscard]] int getPart(SGEXTN::Structs::TimeUnit unit) const;
    void setPart(SGEXTN::Structs::TimeUnit unit, int x);
    [[nodiscard]] int getDayOfWeek() const;
    [[nodiscard]] int getDayOfYear() const;
    [[nodiscard]] int countDaysInMonth() const;
    [[nodiscard]] int countDaysInYear() const;
    [[nodiscard]] SGEXTN::Structs::DateTime getStartOfDay() const;
    [[nodiscard]] SGEXTN::Structs::DateTime getEndOfDay() const;
    [[nodiscard]] int getWeekOfYear() const;
    [[nodiscard]] int getTimeAfterDisplayPart(DateTime x, SGEXTN::Structs::TimeUnit unit) const;
    void advanceTime(long long x, SGEXTN::Structs::TimeUnit unit);
    [[nodiscard]] static int convertToGlobalYear(int standardYear);
    [[nodiscard]] bool isNationalDayPeriod() const;
    [[nodiscard]] bool isSignificantDate(SGEXTN::Structs::SignificantDates date) const;
    [[nodiscard]] SGEXTN::ApplicationBase::OldString getDisplayString(SGEXTN::Structs::TimeFormat format, bool global, bool correctToSecond) const;
    [[nodiscard]] SGEXTN::ApplicationBase::OldString getDisplayString(const SGEXTN::ApplicationBase::OldString& customFormat) const;
};
}
}