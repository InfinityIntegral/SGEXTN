#include "sgxtimestamp.h"
#include <QDate>
#include <QTime>
#include <QString>

const QTimeZone SGXTimeStamp::timezone = QTimeZone("Asia/Singapore");
const SGXTimeStamp SGXTimeStamp::zero = SGXTimeStamp(0ll);
const QDateTime SGXTimeStamp::zeroAsQDateTime = QDateTime(QDate(1965, 8, 9), QTime(12, 30, 0), SGXTimeStamp::timezone);

SGXTimeStamp::SGXTimeStamp(long long t){
    (*this).t = t;
}

SGXTimeStamp::SGXTimeStamp(int year, int month, int day, int hour, int minute, int second){
    (*this).t = 0ll;
    (*this) = SGXTimeStamp(QDateTime(QDate(year + 1965, month, day), QTime(hour, minute, second), SGXTimeStamp::timezone));
}

SGXTimeStamp::SGXTimeStamp(const QDateTime& dt){
    if(dt.isValid() == false || dt.isNull() == true){(*this).t = 0ll;}
    else{(*this).t = (SGXTimeStamp::zeroAsQDateTime).secsTo(dt);}
}

QDateTime SGXTimeStamp::getQDateTime() const {
    return SGXTimeStamp::zeroAsQDateTime.addSecs(t);
}

QString SGXTimeStamp::getString() const {
    return ("SG" + QString::number(getYear()).rightJustified(2, '0') + " " + QString::number(getMonth()).rightJustified(2, '0') + QString::number(getDay()).rightJustified(2, '0') + " " + QString::number(getHour()).rightJustified(2, '0') + QString::number(getMinute()).rightJustified(2, '0') + QString::number(getSecond()).rightJustified(2, '0'));
}

QString SGXTimeStamp::getStringNoOffset() const {
    return (QString::number(getYearNoOffset()).rightJustified(4, '0') + " " + QString::number(getMonth()).rightJustified(2, '0') + QString::number(getDay()).rightJustified(2, '0') + " " + QString::number(getHour()).rightJustified(2, '0') + QString::number(getMinute()).rightJustified(2, '0') + QString::number(getSecond()).rightJustified(2, '0'));
}

QString SGXTimeStamp::getStringCustomFormat(const QString &s) const {
    return ("SG" + getQDateTime().addYears(-1965ll).toString(s));
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

double SGXTimeStamp::getSecondsFrom(SGXTimeStamp x) const {
    return static_cast<double>(t - x.t);
}

double SGXTimeStamp::getMinutesFrom(SGXTimeStamp x) const {
    return (getSecondsFrom(x) / 60.0L);
}

double SGXTimeStamp::getHoursFrom(SGXTimeStamp x) const {
    return (getSecondsFrom(x) / 60.0L / 60.0L);
}

double SGXTimeStamp::getDaysFrom(SGXTimeStamp x) const {
    return (getSecondsFrom(x) / 60.0L / 60.0L / 24.0L);
}

double SGXTimeStamp::getMonthsFrom(SGXTimeStamp x) const {
    long long d = static_cast<long long>(getSecondsFrom(x) / 60.0L / 60.0L / 24.0L / 30.0L);
    long long l = d - 1000ll;
    long long h = d + 1000ll;
    while(h - l > 1){
        long long m = (l + h) / 2ll;
        long long t0 = SGXTimeStamp(x.getQDateTime().addMonths(m)).t;
        if(t0 < t){l = m;}
        else{h = m;}
    }
    double lt = static_cast<double>(SGXTimeStamp(x.getQDateTime().addMonths(l)).t);
    double ht = static_cast<double>(SGXTimeStamp(x.getQDateTime().addMonths(h)).t);
    return (static_cast<double>(l) + (t - lt) / (ht - lt));
}

double SGXTimeStamp::getYearsFrom(SGXTimeStamp x) const {
    long long d = static_cast<long long>(getSecondsFrom(x) / 60.0L / 60.0L / 24.0L / 30.0L / 12.175L);
    long long l = d - 1000ll;
    long long h = d + 1000ll;
    while(h - l > 1){
        long long m = (l + h) / 2ll;
        long long t0 = SGXTimeStamp(x.getQDateTime().addYears(m)).t;
        if(t0 < t){l = m;}
        else{h = m;}
    }
    double lt = static_cast<double>(SGXTimeStamp(x.getQDateTime().addYears(l)).t);
    double ht = static_cast<double>(SGXTimeStamp(x.getQDateTime().addYears(h)).t);
    return (static_cast<double>(l) + (t - lt) / (ht - lt));
}

void SGXTimeStamp::addSeconds(long long x){
    t += x;
}

void SGXTimeStamp::addMinutes(long long x){
    t += (60ll * x);
}

void SGXTimeStamp::addHours(long long x){
    t += (60ll * 60ll * x);
}

void SGXTimeStamp::addDays(long long x){
    t += (60ll * 60ll * 24ll * x);
}

void SGXTimeStamp::addMonths(long long x){
    (*this) = SGXTimeStamp(getQDateTime().addMonths(x));
}

void SGXTimeStamp::addYears(long long x){
    (*this) = SGXTimeStamp(getQDateTime().addYears(x));
}

void SGXTimeStamp::subtractSeconds(long long x){
    addSeconds((-1ll) * x);
}

void SGXTimeStamp::subtractMinutes(long long x){
    addMinutes((-1ll) * x);
}

void SGXTimeStamp::subtractHours(long long x){
    addHours((-1ll) * x);
}

void SGXTimeStamp::subtractDays(long long x){
    addDays((-1ll) * x);
}

void SGXTimeStamp::subtractMonths(long long x){
    addMonths((-1ll) * x);
}

void SGXTimeStamp::subtractYears(long long x){
    addYears((-1ll) * x);
}

SGXTimeStamp SGXTimeStamp::now(){
    return SGXTimeStamp(QDateTime::currentDateTime(SGXTimeStamp::timezone));
}

int SGXTimeStamp::getDayOfWeek() const {
    return getQDateTime().date().dayOfWeek();
}

int SGXTimeStamp::getDayOfYear() const {
    return getQDateTime().date().dayOfYear();
}

int SGXTimeStamp::getSecond() const {
    return getQDateTime().time().second();
}

int SGXTimeStamp::getMinute() const {
    return getQDateTime().time().minute();
}

int SGXTimeStamp::getHour() const {
    return getQDateTime().time().hour();
}

int SGXTimeStamp::getDay() const {
    return getQDateTime().date().day();
}

int SGXTimeStamp::getMonth() const {
    return getQDateTime().date().month();
}

int SGXTimeStamp::getYear() const {
    return (getQDateTime().date().year() - 1965);
}

int SGXTimeStamp::getYearNoOffset() const {
    return getQDateTime().date().year();
}

bool SGXTimeStamp::isNationalDay() const {
    if(getMonth() == 8 && getDay() == 9){return true;}
    return false;
}

bool SGXTimeStamp::isDayBeforeNationalDay() const {
    if(getMonth() == 8 && getDay() == 8){return true;}
    return false;
}

bool SGXTimeStamp::isDayAfterNationalDay() const {
    if(getMonth() == 8 && getDay() == 10){return true;}
    return false;
}

bool SGXTimeStamp::isNationalDayPeriod() const {
    const int m = getMonth();
    if(m >= 7 && m <= 9){return true;}
    return false;
}

QString SGXTimeStamp::getFileName() const {
    return (QString::number(getYear()).rightJustified(2, '0') + QString::number(getMonth()).rightJustified(2, '0') + QString::number(getDay()).rightJustified(2, '0'));
}

QString SGXTimeStamp::getFileNameNoOffset() const {
    return (QString::number(getYearNoOffset()).rightJustified(4, '0') + QString::number(getMonth()).rightJustified(2, '0') + QString::number(getDay()).rightJustified(2, '0'));
}

QString SGXTimeStamp::getFileNameCorrectToSecond() const {
    return (QString::number(getYear()).rightJustified(2, '0') + QString::number(getMonth()).rightJustified(2, '0') + QString::number(getDay()).rightJustified(2, '0') + QString::number(getHour()).rightJustified(2, '0') + QString::number(getMinute()).rightJustified(2, '0') + QString::number(getSecond()).rightJustified(2, '0'));
}

QString SGXTimeStamp::getFileNameCorrectToSecondNoOffset() const {
    return (QString::number(getYearNoOffset()).rightJustified(4, '0') + QString::number(getMonth()).rightJustified(2, '0') + QString::number(getDay()).rightJustified(2, '0') + QString::number(getHour()).rightJustified(2, '0') + QString::number(getMinute()).rightJustified(2, '0') + QString::number(getSecond()).rightJustified(2, '0'));
}

QString SGXTimeStamp::getFileNameSeparated(QChar separator) const {
    return (QString::number(getYear()).rightJustified(2, '0') + separator + QString::number(getMonth()).rightJustified(2, '0') + separator + QString::number(getDay()).rightJustified(2, '0'));
}

QString SGXTimeStamp::getFileNameNoOffsetSeparated(QChar separator) const {
    return (QString::number(getYearNoOffset()).rightJustified(4, '0') + separator + QString::number(getMonth()).rightJustified(2, '0') + separator + QString::number(getDay()).rightJustified(2, '0'));
}

QString SGXTimeStamp::getFileNameCorrectToSecondSeparated(QChar separator) const {
    return (QString::number(getYear()).rightJustified(2, '0') + separator + QString::number(getMonth()).rightJustified(2, '0') + separator + QString::number(getDay()).rightJustified(2, '0') + separator + QString::number(getHour()).rightJustified(2, '0') + separator + QString::number(getMinute()).rightJustified(2, '0') + separator + QString::number(getSecond()).rightJustified(2, '0'));
}

QString SGXTimeStamp::getFileNameCorrectToSecondNoOffsetSeparated(QChar separator) const {
    return (QString::number(getYearNoOffset()).rightJustified(4, '0') + separator + QString::number(getMonth()).rightJustified(2, '0') + separator + QString::number(getDay()).rightJustified(2, '0') + separator + QString::number(getHour()).rightJustified(2, '0') + separator + QString::number(getMinute()).rightJustified(2, '0') + separator + QString::number(getSecond()).rightJustified(2, '0'));
}
