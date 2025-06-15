#ifndef SGXTIMESTAMP_H
#define SGXTIMESTAMP_H

#include <QString>
#include <QDateTime>
#include <QTimeZone>

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
    /*
methods list:
- get QDateTime
- get string representation
- get string with custom formatting
- equality check
- inequality check
- < comparator
- << function
- qHash
- get time difference
- add year, month, day etc
- subtract year, month, day etc
- get now
- cast to other time zone
- cast to universal time zone
- get day of week
- get if any special day (National Day, Total Defence, Racial Harmony etc)
- get if National Day period
     */
};

#endif // SGXTIMESTAMP_H
