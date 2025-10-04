#ifndef SGXTIMESTAMP_H
#define SGXTIMESTAMP_H

#include "sgxstring.h"
#include "sgxchar.h"
#include <QDateTime>
#include <QTimeZone>

class SGXTimeStamp
{
public:
    long long t;
    static const QTimeZone timezone;
    static const SGXTimeStamp zero;
    static const QDateTime zeroAsQDateTime;
    SGXTimeStamp() = default;
    SGXTimeStamp(long long t);
    SGXTimeStamp(int year, int month, int day, int hour, int minute, int second);
    SGXTimeStamp(const QDateTime& dt);
    [[nodiscard]] QDateTime getQDateTime() const;
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
    void addSeconds(long long x);
    void addMinutes(long long x);
    void addHours(long long x);
    void addDays(long long x);
    void addMonths(long long x);
    void addYears(long long x);
    void subtractSeconds(long long x);
    void subtractMinutes(long long x);
    void subtractHours(long long x);
    void subtractDays(long long x);
    void subtractMonths(long long x);
    void subtractYears(long long x);
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

inline unsigned int qHash(SGXTimeStamp x, unsigned int seed = 0){
    return static_cast<unsigned int>(static_cast<unsigned long long>(x.t >> 32ll) ^ static_cast<unsigned long long>(x.t & 0xFFFFFFFFll) ^ static_cast<unsigned long long>(seed));
}

#endif // SGXTIMESTAMP_H
