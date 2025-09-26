#include "sgxtimestamp.h"
#include <QDate>
#include <QTime>
#include "../primitives/sgxstring.h"

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

SGXString SGXTimeStamp::getString() const {
    return (SGXString("SG") + SGXString::intToString(getYear()).fillLeftToLength(2, '0') + " " + SGXString::intToString(getMonth()).fillLeftToLength(2, '0') + SGXString::intToString(getDay()).fillLeftToLength(2, '0') + " " + SGXString::intToString(getHour()).fillLeftToLength(2, '0') + SGXString::intToString(getMinute()).fillLeftToLength(2, '0') + SGXString::intToString(getSecond()).fillLeftToLength(2, '0'));
}

SGXString SGXTimeStamp::getStringNoOffset() const {
    return (SGXString::intToString(getYearNoOffset()).fillLeftToLength(4, '0') + " " + SGXString::intToString(getMonth()).fillLeftToLength(2, '0') + SGXString::intToString(getDay()).fillLeftToLength(2, '0') + " " + SGXString::intToString(getHour()).fillLeftToLength(2, '0') + SGXString::intToString(getMinute()).fillLeftToLength(2, '0') + SGXString::intToString(getSecond()).fillLeftToLength(2, '0'));
}

SGXString SGXTimeStamp::getStringCustomFormat(const SGXString &s) const {
    SGXString output = "";
    (*output.data) = ("SG" + getQDateTime().addYears(-1965ll).toString(*s.data));
    return output;
}

SGXString SGXTimeStamp::getStringNoOffsetCustomFormat(const SGXString &s) const {
    SGXString output = "";
    (*output.data) = getQDateTime().toString(*s.data);
    return output;
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

SGXString SGXTimeStamp::getFileName() const {
    return (SGXString::intToString(getYear()).fillLeftToLength(2, '0') + SGXString::intToString(getMonth()).fillLeftToLength(2, '0') + SGXString::intToString(getDay()).fillLeftToLength(2, '0'));
}

SGXString SGXTimeStamp::getFileNameNoOffset() const {
    return (SGXString::intToString(getYearNoOffset()).fillLeftToLength(4, '0') + SGXString::intToString(getMonth()).fillLeftToLength(2, '0') + SGXString::intToString(getDay()).fillLeftToLength(2, '0'));
}

SGXString SGXTimeStamp::getFileNameCorrectToSecond() const {
    return (SGXString::intToString(getYear()).fillLeftToLength(2, '0') + SGXString::intToString(getMonth()).fillLeftToLength(2, '0') + SGXString::intToString(getDay()).fillLeftToLength(2, '0') + SGXString::intToString(getHour()).fillLeftToLength(2, '0') + SGXString::intToString(getMinute()).fillLeftToLength(2, '0') + SGXString::intToString(getSecond()).fillLeftToLength(2, '0'));
}

SGXString SGXTimeStamp::getFileNameCorrectToSecondNoOffset() const {
    return (SGXString::intToString(getYearNoOffset()).fillLeftToLength(4, '0') + SGXString::intToString(getMonth()).fillLeftToLength(2, '0') + SGXString::intToString(getDay()).fillLeftToLength(2, '0') + SGXString::intToString(getHour()).fillLeftToLength(2, '0') + SGXString::intToString(getMinute()).fillLeftToLength(2, '0') + SGXString::intToString(getSecond()).fillLeftToLength(2, '0'));
}

SGXString SGXTimeStamp::getFileNameSeparated(SGXChar separator) const {
    return (SGXString::intToString(getYear()).fillLeftToLength(2, '0') + separator + SGXString::intToString(getMonth()).fillLeftToLength(2, '0') + separator + SGXString::intToString(getDay()).fillLeftToLength(2, '0'));
}

SGXString SGXTimeStamp::getFileNameNoOffsetSeparated(SGXChar separator) const {
    return (SGXString::intToString(getYearNoOffset()).fillLeftToLength(4, '0') + separator + SGXString::intToString(getMonth()).fillLeftToLength(2, '0') + separator + SGXString::intToString(getDay()).fillLeftToLength(2, '0'));
}

SGXString SGXTimeStamp::getFileNameCorrectToSecondSeparated(SGXChar separator) const {
    return (SGXString::intToString(getYear()).fillLeftToLength(2, '0') + separator + SGXString::intToString(getMonth()).fillLeftToLength(2, '0') + separator + SGXString::intToString(getDay()).fillLeftToLength(2, '0') + separator + SGXString::intToString(getHour()).fillLeftToLength(2, '0') + separator + SGXString::intToString(getMinute()).fillLeftToLength(2, '0') + separator + SGXString::intToString(getSecond()).fillLeftToLength(2, '0'));
}

SGXString SGXTimeStamp::getFileNameCorrectToSecondNoOffsetSeparated(SGXChar separator) const {
    return (SGXString::intToString(getYearNoOffset()).fillLeftToLength(4, '0') + separator + SGXString::intToString(getMonth()).fillLeftToLength(2, '0') + separator + SGXString::intToString(getDay()).fillLeftToLength(2, '0') + separator + SGXString::intToString(getHour()).fillLeftToLength(2, '0') + separator + SGXString::intToString(getMinute()).fillLeftToLength(2, '0') + separator + SGXString::intToString(getSecond()).fillLeftToLength(2, '0'));
}
