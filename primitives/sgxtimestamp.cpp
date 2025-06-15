#include "sgxtimestamp.h"
#include <QDate>
#include <QTime>

const QTimeZone SGXTimeStamp::timezone = QTimeZone("Asia/Singapore");
const SGXTimeStamp SGXTimeStamp::zero = SGXTimeStamp(0l);
const QDateTime SGXTimeStamp::zeroAsQDateTime = QDateTime(QDate(1965, 8, 9), QTime(12, 30, 0), SGXTimeStamp::timezone);

SGXTimeStamp::SGXTimeStamp(long long t){
    (*this).t = t;
}

SGXTimeStamp::SGXTimeStamp(const QString& t){
    (*this).t = 0l;
    (*this) = SGXTimeStamp(QDateTime::fromString(t + " +0800", "yyyyMMdd HHmmss t"));
}

SGXTimeStamp::SGXTimeStamp(int year, int month, int day, int hour, int minute, int second){
    (*this).t = 0l;
    (*this) = SGXTimeStamp(QDateTime(QDate(year, month, day), QTime(hour, minute, second), SGXTimeStamp::timezone));
}

SGXTimeStamp::SGXTimeStamp(const QDateTime& dt){
    (*this).t = (SGXTimeStamp::zeroAsQDateTime).secsTo(dt);
}
