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
