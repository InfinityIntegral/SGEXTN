#include "sgxtimestamp.h"
#include <QDate>
#include <QTime>

const QTimeZone SGXTimeStamp::timezone = QTimeZone("Asia/Singapore");
const SGXTimeStamp SGXTimeStamp::zero = SGXTimeStamp(0ll);
const QDateTime SGXTimeStamp::zeroAsQDateTime = QDateTime(QDate(1965, 8, 9), QTime(12, 30, 0), SGXTimeStamp::timezone);

SGXTimeStamp::SGXTimeStamp(long long t){
    (*this).t = t;
}

SGXTimeStamp::SGXTimeStamp(const QString& t){
    (*this).t = 0ll;
    (*this) = SGXTimeStamp(QDateTime::fromString(t + " +0800", "yyyyMMdd HHmmss t"));
}

SGXTimeStamp::SGXTimeStamp(int year, int month, int day, int hour, int minute, int second){
    (*this).t = 0ll;
    (*this) = SGXTimeStamp(QDateTime(QDate(year, month, day), QTime(hour, minute, second), SGXTimeStamp::timezone));
}

SGXTimeStamp::SGXTimeStamp(const QDateTime& dt){
    (*this).t = (SGXTimeStamp::zeroAsQDateTime).secsTo(dt);
}

QDateTime SGXTimeStamp::getQDateTime() const {
    return SGXTimeStamp::zeroAsQDateTime.addSecs(t);
}

QString SGXTimeStamp::getString() const {
    return getQDateTime().addYears(-1965).toString("yyyyMMdd hhmmss");
}

QString SGXTimeStamp::getStringNoOffset() const {
    return getQDateTime().toString("yyyyMMdd hhmmss");
}

QString SGXTimeStamp::getStringCustomFormat(const QString &s) const {
    return getQDateTime().addYears(-1965).toString(s);
}

QString SGXTimeStamp::getStringNoOffsetCustomFormat(const QString &s) const {
    return getQDateTime().toString(s);
}

bool SGXTimeStamp::operator==(SGXTimeStamp x) const {
    return (t == x.t);
}

bool SGXTimeStamp::operator!=(SGXTimeStamp x) const {
    return (t != x.t);
}

bool SGXTimeStamp::operator<(SGXTimeStamp x) const {
    return (t < x.t);
}

bool SGXTimeStamp::operator>(SGXTimeStamp x) const {
    return (t > x.t);
}

bool SGXTimeStamp::operator<=(SGXTimeStamp x) const {
    return (t <= x.t);
}

bool SGXTimeStamp::operator>=(SGXTimeStamp x) const {
    return (t >= x.t);
}
