#ifndef SGXTIMESTAMP_H
#define SGXTIMESTAMP_H

#include <QString>
#include <QDateTime>
#include <QTimeZone>
#include <bit>
#include <QDebug>

class SGXTimeStamp // contains the number of seconds since 19650809 123000
{
public:
    long long t; // time in number of seconds since 19650809 123000
    static const QTimeZone timezone; // default time zone, corresponds to time zone of Singapore
    static const SGXTimeStamp zero; // 19650809 123000, the time in current time zone when Prime Minister Lee Kuan Yew announced the separation of our nation from Malaysia
    static const QDateTime zeroAsQDateTime; // time zero as a QDateTime
    SGXTimeStamp(long long t); // constructs timestamp object from the timestamp itself
    SGXTimeStamp(const QString& t); // constructs timestamp object from time in default calendar as a string in "yyyyMMdd HHmmss" format
    SGXTimeStamp(int year, int month, int day, int hour, int minute, int second); // construct timestamp object from components
    SGXTimeStamp(const QDateTime& dt); // converts QDateTime to SGXTimeStamp
    [[nodiscard]] QDateTime getQDateTime() const; // converts SGXTimeStamp to QDateTime
    [[nodiscard]] QString getString() const; // converts timestamp to string in "yyyyMMdd HHmmss" format
    [[nodiscard]] QString getStringNoOffset() const; // converts timestamp to string in "yyyyMMdd HHmmss" format without the default year offset of 1965
    [[nodiscard]] QString getStringCustomFormat(const QString& s) const; // converts timestamp to string in custom format
    [[nodiscard]] QString getStringNoOffsetCustomFormat(const QString& s) const; // converts timestamp to string in custom format without the default year offset of 1965
    [[nodiscard]] bool operator==(SGXTimeStamp x) const; // equality comparator by comparing time not struct instance memory location
    [[nodiscard]] bool operator!=(SGXTimeStamp x) const; // inequality comparator by comparing time not struct instance memory location
    [[nodiscard]] bool operator<(SGXTimeStamp x) const; // less than comparator using time
    [[nodiscard]] bool operator>(SGXTimeStamp x) const; // more than comparator using time
    [[nodiscard]] bool operator<=(SGXTimeStamp x) const; // less than or equal to comparator using time
    [[nodiscard]] bool operator>=(SGXTimeStamp x) const; // more than or equal to comparator using time
    void getTimeDifference(SGXTimeStamp x, int& year, int& month, int& day, int& hour, int& minute, int& second, bool& isBefore) const; // get time difference between this timestamp and x, isBefore true if this timestamp is before the other timestamp, the time difference outputs nonnegative integers for each field but uses decimals internally to keep accuracy, note that 1 month = 30 days, 1 year = 12.175 months, which are not exact but close enough to actual months and years
    [[nodiscard]] float getSecondsFrom(SGXTimeStamp x) const; // compute time difference in seconds required to be added to x to get this timestamp
    [[nodiscard]] float getMinutesFrom(SGXTimeStamp x) const; // compute time difference in minutes required to be added to x to get this timestamp
    [[nodiscard]] float getHoursFrom(SGXTimeStamp x) const; // compute time difference in hours required to be added to x to get this timestamp
    [[nodiscard]] float getDaysFrom(SGXTimeStamp x) const; // compute time difference in days required to be added to x to get this timestamp
    [[nodiscard]] float getMonthsFrom(SGXTimeStamp x) const; // compute time difference in months required to be added to x to get this timestamp
    [[nodiscard]] float getYearsFrom(SGXTimeStamp x) const; // compute time difference in years required to be added to x to get this timestamp
    void addSeconds(long long x); // add x seconds to this timestamp
    void addMinutes(float x); // add x minutes to this timestamp
    void addHours(float x); // add x hours to this timestamp
    void addDays(float x); // add x days to this timestamp
    void addMonths(float x); // add x months to this timestamp
    void addYears(float x); // add x years to this timestamp
    void subtractSeconds(long long x); // subtract x seconds from this timestamp
    void subtractMinutes(float x); // subtract x minutes from this timestamp
    void subtractHours(float x); // subtract x hours from this timestamp
    void subtractDays(float x); // subtract x days from this timestamp
    void subtractMonths(float x); // subtract x months from this timestamp
    void subtractYears(float x); // subtract x years from this timestamp
    [[nodiscard]] static SGXTimeStamp now(); // get timestamp representing the time now
    [[nodiscard]] int getDayOfWeek() const; // get day of week corresponding to day name in Chinese (1 = Monday, 2 = Tuesday, 3 = Wednesday, 4 = Thursday, 5 = Friday, 6 = Saturday, 7 = Sunday)
    [[nodiscard]] int getDayOfYear() const; // get day of year as a number between 1 and 365 (366 on leap years) inclusive
    [[nodiscard]] int getSecond() const; // extract second component
    [[nodiscard]] int getMinute() const; // extract minute component
    [[nodiscard]] int getHour() const; // extract hour component
    [[nodiscard]] int getDay() const; // get day of month as a number between 1 and 31 inclusive
    [[nodiscard]] int getMonth() const; // get month of year corresponding to month name in Chinese
    [[nodiscard]] int getYear() const; // get year component
    [[nodiscard]] int getYearNoOffset() const; // get year component without default offset of 1965
    /*
methods list:
- get if any special day (National Day, Total Defence, Racial Harmony etc)
- get if National Day period
     */
};

inline unsigned int qHash(SGXTimeStamp x, unsigned int seed = 0){
    return static_cast<unsigned int>(std::bit_cast<unsigned long long>(x.t >> 32ll) ^ std::bit_cast<unsigned long long>(x.t & 0xFFFFFFFFll) ^ static_cast<unsigned long long>(seed));
}

inline QDebug operator<<(QDebug s, SGXTimeStamp x){
    s << x.getString();
    return s;
}

#endif // SGXTIMESTAMP_H
