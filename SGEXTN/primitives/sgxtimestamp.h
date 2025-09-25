#ifndef SGXTIMESTAMP_H
#define SGXTIMESTAMP_H

#include <QString>
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
    [[nodiscard]] QString getString() const;
    [[nodiscard]] QString getStringNoOffset() const;
    [[nodiscard]] QString getStringCustomFormat(const QString& s) const;
    [[nodiscard]] QString getStringNoOffsetCustomFormat(const QString& s) const;
    [[nodiscard]] bool operator==(SGXTimeStamp x) const;
    [[nodiscard]] bool operator!=(SGXTimeStamp x) const;
    [[nodiscard]] bool operator<(SGXTimeStamp x) const;
    [[nodiscard]] bool operator>(SGXTimeStamp x) const;
    [[nodiscard]] bool operator<=(SGXTimeStamp x) const;
    [[nodiscard]] bool operator>=(SGXTimeStamp x) const;
    [[nodiscard]] float getSecondsFrom(SGXTimeStamp x) const;
    [[nodiscard]] float getMinutesFrom(SGXTimeStamp x) const;
    [[nodiscard]] float getHoursFrom(SGXTimeStamp x) const;
    [[nodiscard]] float getDaysFrom(SGXTimeStamp x) const;
    [[nodiscard]] float getMonthsFrom(SGXTimeStamp x) const;
    [[nodiscard]] float getYearsFrom(SGXTimeStamp x) const;
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
    [[nodiscard]] QString getFileName() const;
    [[nodiscard]] QString getFileNameNoOffset() const;
    [[nodiscard]] QString getFileNameCorrectToSecond() const;
    [[nodiscard]] QString getFileNameCorrectToSecondNoOffset() const;
    [[nodiscard]] QString getFileNameSeparated(QChar separator) const;
    [[nodiscard]] QString getFileNameNoOffsetSeparated(QChar separator) const;
    [[nodiscard]] QString getFileNameCorrectToSecondSeparated(QChar separator) const;
    [[nodiscard]] QString getFileNameCorrectToSecondNoOffsetSeparated(QChar separator) const;
};

inline unsigned int qHash(SGXTimeStamp x, unsigned int seed = 0){
    return static_cast<unsigned int>(static_cast<unsigned long long>(x.t >> 32ll) ^ static_cast<unsigned long long>(x.t & 0xFFFFFFFFll) ^ static_cast<unsigned long long>(seed));
}

#endif // SGXTIMESTAMP_H
