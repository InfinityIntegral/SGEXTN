#include "sgxtimestamp.h"
#include <QDate>
#include <QTime>

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
    return ("SG" + getQDateTime().addYears(-1965).toString("yy MMdd hhmmss"));
}

QString SGXTimeStamp::getStringNoOffset() const {
    return getQDateTime().toString("yyyyMMdd hhmmss");
}

QString SGXTimeStamp::getStringCustomFormat(const QString &s) const {
    return ("SG" + getQDateTime().addYears(-1965).toString(s));
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

float SGXTimeStamp::getSecondsFrom(SGXTimeStamp x) const {
    return static_cast<float>(t - x.t);
}

float SGXTimeStamp::getMinutesFrom(SGXTimeStamp x) const {
    double d = static_cast<double>(t - x.t);
    d /= 60.0;
    return static_cast<float>(d);
}

float SGXTimeStamp::getHoursFrom(SGXTimeStamp x) const {
    double d = static_cast<double>(t - x.t);
    d /= 60.0;
    d /= 60.0;
    return static_cast<float>(d);
}

float SGXTimeStamp::getDaysFrom(SGXTimeStamp x) const {
    double d = static_cast<double>(t - x.t);
    d /= 60.0;
    d /= 60.0;
    d /= 24.0;
    return static_cast<float>(d);
}

float SGXTimeStamp::getMonthsFrom(SGXTimeStamp x) const {
    double d = static_cast<double>(t - x.t);
    d /= 60.0;
    d /= 60.0;
    d /= 24.0;
    d /= 30.0;
    return static_cast<float>(d);
}

float SGXTimeStamp::getYearsFrom(SGXTimeStamp x) const {
    double d = static_cast<double>(t - x.t);
    d /= 60.0;
    d /= 60.0;
    d /= 24.0;
    d /= 30.0;
    d /= 12.175;
    return static_cast<float>(d);
}

void SGXTimeStamp::addSeconds(long long x){
    t += x;
}

void SGXTimeStamp::addMinutes(float x){
    double d = static_cast<double>(x);
    d *= 60.0;
    t += static_cast<long long>(d);
}

void SGXTimeStamp::addHours(float x){
    double d = static_cast<double>(x);
    d *= 60.0;
    d *= 60.0;
    t += static_cast<long long>(d);
}

void SGXTimeStamp::addDays(float x){
    double d = static_cast<double>(x);
    d *= 60.0;
    d *= 60.0;
    d *= 24.0;
    t += static_cast<long long>(d);
}

void SGXTimeStamp::addMonths(float x){
    double d = static_cast<double>(x);
    d *= 60.0;
    d *= 60.0;
    d *= 24.0;
    d *= 30.0;
    t += static_cast<long long>(d);
}

void SGXTimeStamp::addYears(float x){
    double d = static_cast<double>(x);
    d *= 60.0;
    d *= 60.0;
    d *= 24.0;
    d *= 30.0;
    d *= 12.175;
    t += static_cast<long long>(d);
}

void SGXTimeStamp::subtractSeconds(long long x){
    t -= x;
}

void SGXTimeStamp::subtractMinutes(float x){
    double d = static_cast<double>(x);
    d *= 60.0;
    t -= static_cast<long long>(d);
}

void SGXTimeStamp::subtractHours(float x){
    double d = static_cast<double>(x);
    d *= 60.0;
    d *= 60.0;
    t -= static_cast<long long>(d);
}

void SGXTimeStamp::subtractDays(float x){
    double d = static_cast<double>(x);
    d *= 60.0;
    d *= 60.0;
    d *= 24.0;
    t -= static_cast<long long>(d);
}

void SGXTimeStamp::subtractMonths(float x){
    double d = static_cast<double>(x);
    d *= 60.0;
    d *= 60.0;
    d *= 24.0;
    d *= 30.0;
    t -= static_cast<long long>(d);
}

void SGXTimeStamp::subtractYears(float x){
    double d = static_cast<double>(x);
    d *= 60.0;
    d *= 60.0;
    d *= 24.0;
    d *= 30.0;
    d *= 12.175;
    t -= static_cast<long long>(d);
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
    const int m = getMonth();
    const int d = getDay();
    if(m == 8 && d == 9){return true;}
    return false;
}

bool SGXTimeStamp::isDayBeforeNationalDay() const {
    const int m = getMonth();
    const int d = getDay();
    if(m == 8 && d == 8){return true;}
    return false;
}

bool SGXTimeStamp::isDayAfterNationalDay() const {
    const int m = getMonth();
    const int d = getDay();
    if(m == 8 && d == 10){return true;}
    return false;
}

bool SGXTimeStamp::isNationalDayPeriod() const {
    const int m = getMonth();
    if(m >= 7 && m <= 9){return true;}
    return false;
}

QString SGXTimeStamp::getSpecialDay() const {
    const int m = getMonth();
    const int d = getDay();
    if(m == 8 && d == 9){return "National Day";}
    if(m == 8 && d == 8){return "day before National Day";}
    if(m == 8 && d == 10){return "day before National Day";}
    if(m == 2 && d == 15){return "Total Defence Day";}
    if(m == 7 && d == 21){return "Racial Harmony Day";}
    if(m == 10 && d == 5){return "International Teachers' Day";} // International version used because our own one changes every year according to MOE calendar
    if(m == 10 && d <= 7 && getDayOfWeek() == 5){return "Children's Day";}
    if(m == 7 && d <= 7 && getDayOfWeek() == 7){return "Youth Day";}
    if(m == 3 && d == 8){return "International Women's Day";}
    if(m == 5 && d == 1){return "Labour Day";}
    if(m == 3 && d == 14){return "International Mathematics Day";}
    if(m == 7 && d == 1){return "Singapore Armed Forces Day";}
    if(m == 9 && d == 21){return "International Day of Peace";}
    if(m == 4 && d == 22){return "Earth Day";}
    if(m == 6 && d == 5){return "World Environment Day";}
    if(m == 7 && d == 26){return "Day 7.26";}
    if(m == 5 && d == 12){return "International Women in Mathematics Day";}
    if(m == 12 && d == 9){return "International Computer Science Day";}
    if(m == 1 && d == 14){return "World Logic Day";}
    if(m == 4 && d == 14){return "World Quantum Day";}
    if(m == 12 && d == 11){return "International Day of Chemistry";}
    if(getDayOfYear() == 256){return "Programmer's Day";}
    if(m == 9 && d == 16){return "Lee Kuan Yew's birthday";}
    return "";
}
