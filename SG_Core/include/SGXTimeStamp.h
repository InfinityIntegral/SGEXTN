#ifndef SGXTIMESTAMP_H
#define SGXTIMESTAMP_H

#include <SGXString.h>
#include <SGXChar.h>

#include <private_api_Core/SG_Build_Core.h>

class SG_CORE_DLL SGXTimeStamp
{
public:
    long long t;
    static const SGXTimeStamp zero;
    SGXTimeStamp() = default;
    SGXTimeStamp(long long t);
    SGXTimeStamp(int year, int month, int day, int hour, int minute, int second);
    [[nodiscard]] SGXString getString() const;
    [[nodiscard]] SGXString getStringNoOffset() const;
    [[nodiscard]] SGXString getStringCustomFormat(const SGXString& s) const;
    [[nodiscard]] SGXString getStringNoOffsetCustomFormat(const SGXString& s) const;
    [[nodiscard]] bool operator==(SGXTimeStamp x) const;
    [[nodiscard]] bool operator!=(SGXTimeStamp x) const;
    [[nodiscard]] bool operator<(SGXTimeStamp x) const;
    [[nodiscard]] bool operator>(SGXTimeStamp x) const;
    [[nodiscard]] bool operator<=(SGXTimeStamp x) const;
    [[nodiscard]] bool operator>=(SGXTimeStamp x) const;
    [[nodiscard]] int hash() const;
    [[nodiscard]] double getSecondsFrom(SGXTimeStamp x) const;
    [[nodiscard]] double getMinutesFrom(SGXTimeStamp x) const;
    [[nodiscard]] double getHoursFrom(SGXTimeStamp x) const;
    [[nodiscard]] double getDaysFrom(SGXTimeStamp x) const;
    [[nodiscard]] double getMonthsFrom(SGXTimeStamp x) const;
    [[nodiscard]] double getYearsFrom(SGXTimeStamp x) const;
    [[nodiscard]] int getTimeFromSecondPart(SGXTimeStamp x) const;
    [[nodiscard]] int getTimeFromMinutePart(SGXTimeStamp x) const;
    [[nodiscard]] int getTimeFromHourPart(SGXTimeStamp x) const;
    [[nodiscard]] int getTimeFromDayPart(SGXTimeStamp x) const;
    [[nodiscard]] int getTimeFromMonthPart(SGXTimeStamp x) const;
    [[nodiscard]] int getTimeFromYearPart(SGXTimeStamp x) const;
    [[nodiscard]] SGXString getFullSGCalendar() const;
    SGXTimeStamp& addSeconds(long long x);
    SGXTimeStamp& addMinutes(long long x);
    SGXTimeStamp& addHours(long long x);
    SGXTimeStamp& addDays(long long x);
    SGXTimeStamp& addMonths(long long x);
    SGXTimeStamp& addYears(long long x);
    SGXTimeStamp& subtractSeconds(long long x);
    SGXTimeStamp& subtractMinutes(long long x);
    SGXTimeStamp& subtractHours(long long x);
    SGXTimeStamp& subtractDays(long long x);
    SGXTimeStamp& subtractMonths(long long x);
    SGXTimeStamp& subtractYears(long long x);
    [[nodiscard]] static SGXTimeStamp now();
    [[nodiscard]] int getDayOfWeek() const;
    [[nodiscard]] int getDayOfYear() const;
    [[nodiscard]] int getSecond() const;
    [[nodiscard]] int getMinute() const;
    [[nodiscard]] int getHour() const;
    [[nodiscard]] int getDay() const;
    [[nodiscard]] int getMonth() const;
    [[nodiscard]] int getYear() const;
    [[nodiscard]] int getYearNoOffset() const;
    [[nodiscard]] bool isNationalDayPeriod() const;
    [[nodiscard]] bool isNationalDay() const;
    [[nodiscard]] bool isDayBeforeNationalDay() const;
    [[nodiscard]] bool isDayAfterNationalDay() const;
    [[nodiscard]] SGXString getFileName() const;
    [[nodiscard]] SGXString getFileNameNoOffset() const;
    [[nodiscard]] SGXString getFileNameCorrectToSecond() const;
    [[nodiscard]] SGXString getFileNameCorrectToSecondNoOffset() const;
    [[nodiscard]] SGXString getFileNameSeparated(SGXChar separator) const;
    [[nodiscard]] SGXString getFileNameNoOffsetSeparated(SGXChar separator) const;
    [[nodiscard]] SGXString getFileNameCorrectToSecondSeparated(SGXChar separator) const;
    [[nodiscard]] SGXString getFileNameCorrectToSecondNoOffsetSeparated(SGXChar separator) const;
};

#endif // SGXTIMESTAMP_H
