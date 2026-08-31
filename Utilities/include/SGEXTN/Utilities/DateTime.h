/*
   Copyright 2026 05524F.sg

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
// BuildLah license check: SGEXTN 7.0.0

#pragma once

namespace SGEXTN::Containers {
template <typename T> class Span;
}

namespace SGEXTN::CoreText {
class String;
}

namespace SGEXTN::Utilities {
enum class TimeUnit : unsigned char {
    Year = 1,
    Month = 2,
    Day = 3,
    Hour = 4,
    Minute = 5,
    Second = 6
};

enum class TimeFormat : unsigned char {
    Display = 1,
    FileName = 2,
    ShortestReadable = 3
};

enum class SignificantDates : unsigned char {
    NationalDay = 0x01,
    DayBeforeNationalDay = 0x02,
    DayAfterNationalDay = 0x03,
    TotalDefenceDay = 0x11,
    RacialHarmonyDay = 0x21
};

class BuildLah_SGEXTN_Utilities DateTime {
private:
    long long data_;
public:
    explicit DateTime();
    explicit DateTime(long long t);
    explicit DateTime(int year, int month, int day, int hour, int minute, int second);
    [[nodiscard]] bool operator==(DateTime x) const;
    [[nodiscard]] bool operator!=(DateTime x) const;
    [[nodiscard]] bool operator<(DateTime x) const;
    [[nodiscard]] bool operator>(DateTime x) const;
    [[nodiscard]] bool operator<=(DateTime x) const;
    [[nodiscard]] bool operator>=(DateTime x) const;
    [[nodiscard]] SGEXTN::CoreText::String debugPrint() const;
    [[nodiscard]] static bool sendOut(DateTime x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static bool sendIn(DateTime& x, SGEXTN::Containers::Span<unsigned char> data);
    [[nodiscard]] static int size();
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
