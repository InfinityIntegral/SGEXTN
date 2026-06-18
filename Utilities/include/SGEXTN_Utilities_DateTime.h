#pragma once

namespace SGEXTN {
namespace CoreText {
class String;
}

namespace Utilities {
enum class BuildLah_SGEXTN_Utilities TimeUnit : unsigned char {Year, Month, Day, Hour, Minute, Second};

enum class BuildLah_SGEXTN_Utilities TimeFormat : unsigned char {Display, FileName, ShortestReadable};

enum class BuildLah_SGEXTN_Utilities SignificantDates : unsigned char {NationalDay, DayBeforeNationalDay, DayAfterNationalDay, TotalDefenceDay, RacialHarmonyDay};

class BuildLah_SGEXTN_Utilities DateTime {
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
    [[nodiscard]] SGEXTN::CoreText::String debugPrint() const;
    [[nodiscard]] double getTimeAfter(DateTime x, SGEXTN::Utilities::TimeUnit unit) const;
    [[nodiscard]] static DateTime beginningOfTime();
    [[nodiscard]] static DateTime now();
    [[nodiscard]] int getPart(SGEXTN::Utilities::TimeUnit unit) const;
    void setPart(SGEXTN::Utilities::TimeUnit unit, int x);
    [[nodiscard]] int getDayOfWeek() const;
    [[nodiscard]] int getDayOfYear() const;
    [[nodiscard]] int countDaysInMonth() const;
    [[nodiscard]] int countDaysInYear() const;
    [[nodiscard]] SGEXTN::Utilities::DateTime getStartOfDay() const;
    [[nodiscard]] SGEXTN::Utilities::DateTime getEndOfDay() const;
    [[nodiscard]] int getWeekOfYear() const;
    [[nodiscard]] int getTimeAfterDisplayPart(DateTime x, SGEXTN::Utilities::TimeUnit unit) const;
    void advanceTime(long long x, SGEXTN::Utilities::TimeUnit unit);
    [[nodiscard]] static int convertToGlobalYear(int standardYear);
    [[nodiscard]] bool isNationalDayPeriod() const;
    [[nodiscard]] bool isSignificantDate(SGEXTN::Utilities::SignificantDates date) const;
    [[nodiscard]] SGEXTN::CoreText::String getDisplayString(SGEXTN::Utilities::TimeFormat format, bool global, bool correctToSecond) const;
    [[nodiscard]] SGEXTN::CoreText::String getDisplayString(const SGEXTN::CoreText::String& customFormat) const;
};
}
}
