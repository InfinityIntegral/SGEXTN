#include <SGXTimeStamp.h>
#include <QDate>
#include <QTime>
#include <SGXString.h>
#include <SGLHash.h>
#include <QDateTime>
#include <QTimeZone>

namespace{
inline QTimeZone temp_timezone = QTimeZone("Asia/Singapore");
inline QDateTime temp_zeroAsQDateTime = QDateTime(QDate(1965, 8, 9), QTime(10, 30, 0), QTimeZone("Asia/Singapore"));

inline SGXTimeStamp temp_qDateTimeToSGXTimeStamp(const QDateTime& dt){
    if(dt.isValid() == false || dt.isNull() == true){return SGXTimeStamp::zero;}
    return SGXTimeStamp((temp_zeroAsQDateTime).secsTo(dt));
}

inline QDateTime temp_sgxTimeStampToQDateTime(const SGXTimeStamp& x){
    return temp_zeroAsQDateTime.addSecs(x.t);
}
}

const SGXTimeStamp SGXTimeStamp::zero = SGXTimeStamp(0ll);

SGXTimeStamp::SGXTimeStamp(long long t){
    (*this).t = t;
}

SGXTimeStamp::SGXTimeStamp(int year, int month, int day, int hour, int minute, int second){
    (*this).t = 0ll;
    (*this) = temp_qDateTimeToSGXTimeStamp(QDateTime(QDate(year + 1965, month, day), QTime(hour, minute, second), temp_timezone));
}

SGXString SGXTimeStamp::getString() const {
    return (SGXString("SG") + SGXString::intToString(getYear()).fillLeftToLength(2, '0') + " " + SGXString::intToString(getMonth()).fillLeftToLength(2, '0') + SGXString::intToString(getDay()).fillLeftToLength(2, '0') + " " + SGXString::intToString(getHour()).fillLeftToLength(2, '0') + SGXString::intToString(getMinute()).fillLeftToLength(2, '0') + SGXString::intToString(getSecond()).fillLeftToLength(2, '0'));
}

SGXString SGXTimeStamp::getStringNoOffset() const {
    return (SGXString::intToString(getYearNoOffset()).fillLeftToLength(4, '0') + " " + SGXString::intToString(getMonth()).fillLeftToLength(2, '0') + SGXString::intToString(getDay()).fillLeftToLength(2, '0') + " " + SGXString::intToString(getHour()).fillLeftToLength(2, '0') + SGXString::intToString(getMinute()).fillLeftToLength(2, '0') + SGXString::intToString(getSecond()).fillLeftToLength(2, '0'));
}

SGXString SGXTimeStamp::getStringCustomFormat(const SGXString &s) const {
    SGXString output = "";
    (*output.data) = ("SG" + temp_sgxTimeStampToQDateTime(*this).addYears(-1965ll).toString(*s.data));
    return output;
}

SGXString SGXTimeStamp::getStringNoOffsetCustomFormat(const SGXString &s) const {
    SGXString output = "";
    (*output.data) = temp_sgxTimeStampToQDateTime(*this).toString(*s.data);
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

int SGXTimeStamp::hash() const {
    return SGLHash<long long>()(t);
}

double SGXTimeStamp::getSecondsFrom(SGXTimeStamp x) const {
    return static_cast<double>(t - x.t);
}

double SGXTimeStamp::getMinutesFrom(SGXTimeStamp x) const {
    return (getSecondsFrom(x) / 60.0);
}

double SGXTimeStamp::getHoursFrom(SGXTimeStamp x) const {
    return (getSecondsFrom(x) / 60.0 / 60.0);
}

double SGXTimeStamp::getDaysFrom(SGXTimeStamp x) const {
    return (getSecondsFrom(x) / 60.0 / 60.0 / 24.0);
}

double SGXTimeStamp::getMonthsFrom(SGXTimeStamp x) const {
    const long long d = 12 * (getYear() - x.getYear()) + (getMonth() - x.getMonth());
    long long l = d - 1000ll;
    long long h = d + 1000ll;
    while(h - l > 1){
        const long long m = (l + h) / 2ll;
        const long long t0 = temp_qDateTimeToSGXTimeStamp(temp_sgxTimeStampToQDateTime(x).addMonths(static_cast<int>(m))).t;
        if(t0 < t){l = m;}
        else{h = m;}
    }
    const double lt = static_cast<double>(temp_qDateTimeToSGXTimeStamp(temp_sgxTimeStampToQDateTime(x).addMonths(static_cast<int>(l))).t);
    const double ht = static_cast<double>(temp_qDateTimeToSGXTimeStamp(temp_sgxTimeStampToQDateTime(x).addMonths(static_cast<int>(h))).t);
    return (static_cast<double>(l) + (static_cast<double>(t) - lt) / (ht - lt));
}

double SGXTimeStamp::getYearsFrom(SGXTimeStamp x) const {
    const long long d = getYear() - x.getYear();
    long long l = d - 1000ll;
    long long h = d + 1000ll;
    while(h - l > 1){
        const long long m = (l + h) / 2ll;
        const long long t0 = temp_qDateTimeToSGXTimeStamp(temp_sgxTimeStampToQDateTime(x).addYears(static_cast<int>(m))).t;
        if(t0 < t){l = m;}
        else{h = m;}
    }
    const double lt = static_cast<double>(temp_qDateTimeToSGXTimeStamp(temp_sgxTimeStampToQDateTime(x).addYears(static_cast<int>(l))).t);
    const double ht = static_cast<double>(temp_qDateTimeToSGXTimeStamp(temp_sgxTimeStampToQDateTime(x).addYears(static_cast<int>(h))).t);
    return (static_cast<double>(l) + (static_cast<double>(t) - lt) / (ht - lt));
}

int SGXTimeStamp::getTimeFromYearPart(SGXTimeStamp x) const {
    const int prelim = getYear() - x.getYear();
    if(getMonth() > x.getMonth()){return prelim;}
    if(getMonth() < x.getMonth()){return (prelim - 1);}
    if(getDay() > x.getDay()){return prelim;}
    if(getDay() < x.getDay()){return (prelim - 1);}
    if(getHour() > x.getHour()){return prelim;}
    if(getHour() < x.getHour()){return (prelim - 1);}
    if(getMinute() > x.getMinute()){return prelim;}
    if(getMinute() < x.getMinute()){return (prelim - 1);}
    if(getSecond() > x.getSecond()){return prelim;}
    if(getSecond() < x.getSecond()){return (prelim - 1);}
    return prelim;
}

int SGXTimeStamp::getTimeFromMonthPart(SGXTimeStamp x) const {
    int prelim = getMonth() - x.getMonth();
    if(getDay() < x.getDay() || (getDay() == x.getDay() && getHour() < x.getHour()) || (getDay() == x.getDay() && getHour() == x.getHour() && getMinute() < x.getMinute()) || (getDay() == x.getDay() && getHour() == x.getHour() && getMinute() == x.getMinute() && getSecond() < x.getSecond())){prelim--;}
    if(prelim < 0){prelim += 12;}
    return prelim;
}

int SGXTimeStamp::getTimeFromDayPart(SGXTimeStamp x) const {
    int prelim = getDay() - x.getDay();
    if(getHour() < x.getHour() || (getHour() == x.getHour() && getMinute() < x.getMinute()) || (getHour() == x.getHour() && getMinute() == x.getMinute() && getSecond() < x.getSecond())){prelim--;}
    if(prelim < 0){
        if(x.getMonth() == 1 || x.getMonth() == 3 || x.getMonth() == 5 || x.getMonth() == 7 || x.getMonth() == 8 || x.getMonth() == 10 || x.getMonth() == 12){prelim += 31;}
        else if(x.getMonth() == 2 && x.getYearNoOffset() % 4 == 0){prelim += 29;}
        else if(x.getMonth() == 2){prelim += 28;}
        else if(x.getMonth() == 4 || x.getMonth() == 6 || x.getMonth() == 9 || x.getMonth() == 11){prelim += 30;}
    }
    return prelim;
}

int SGXTimeStamp::getTimeFromHourPart(SGXTimeStamp x) const {
    int prelim = getHour() - x.getHour();
     if(getMinute() < x.getMinute() || (getMinute() == x.getMinute() && getSecond() < x.getSecond())){prelim--;}
    if(prelim < 0){prelim += 24;}
    return prelim;
}

int SGXTimeStamp::getTimeFromMinutePart(SGXTimeStamp x) const {
    int prelim = getMinute() - x.getMinute();
    if(getSecond() < x.getSecond()){prelim--;}
    if(prelim < 0){prelim += 60;}
    return prelim;
}

int SGXTimeStamp::getTimeFromSecondPart(SGXTimeStamp x) const {
    int prelim = getSecond() - x.getSecond();
    if(prelim < 0){prelim += 60;}
    return prelim;
}

SGXString SGXTimeStamp::getFullSGCalendar() const {
    return (SGXString("SG") + SGXString::intToString(getTimeFromYearPart(SGXTimeStamp::zero)).fillLeftToLength(2, '0') + " " + SGXString::intToString(getTimeFromMonthPart(SGXTimeStamp::zero)).fillLeftToLength(2, '0') + SGXString::intToString(getTimeFromDayPart(SGXTimeStamp::zero)).fillLeftToLength(2, '0') + " " + SGXString::intToString(getTimeFromHourPart(SGXTimeStamp::zero)).fillLeftToLength(2, '0') + SGXString::intToString(getTimeFromMinutePart(SGXTimeStamp::zero)).fillLeftToLength(2, '0') + SGXString::intToString(getTimeFromSecondPart(SGXTimeStamp::zero)).fillLeftToLength(2, '0'));
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
    (*this) = temp_qDateTimeToSGXTimeStamp(temp_sgxTimeStampToQDateTime(*this).addMonths(static_cast<int>(x)));
}

void SGXTimeStamp::addYears(long long x){
    (*this) = temp_qDateTimeToSGXTimeStamp(temp_sgxTimeStampToQDateTime(*this).addYears(static_cast<int>(x)));
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
    return temp_qDateTimeToSGXTimeStamp(QDateTime::currentDateTime(temp_timezone));
}

int SGXTimeStamp::getDayOfWeek() const {
    return temp_sgxTimeStampToQDateTime(*this).date().dayOfWeek();
}

int SGXTimeStamp::getDayOfYear() const {
    return temp_sgxTimeStampToQDateTime(*this).date().dayOfYear();
}

int SGXTimeStamp::getSecond() const {
    return temp_sgxTimeStampToQDateTime(*this).time().second();
}

int SGXTimeStamp::getMinute() const {
    return temp_sgxTimeStampToQDateTime(*this).time().minute();
}

int SGXTimeStamp::getHour() const {
    return temp_sgxTimeStampToQDateTime(*this).time().hour();
}

int SGXTimeStamp::getDay() const {
    return temp_sgxTimeStampToQDateTime(*this).date().day();
}

int SGXTimeStamp::getMonth() const {
    return temp_sgxTimeStampToQDateTime(*this).date().month();
}

int SGXTimeStamp::getYear() const {
    return (temp_sgxTimeStampToQDateTime(*this).date().year() - 1965);
}

int SGXTimeStamp::getYearNoOffset() const {
    return temp_sgxTimeStampToQDateTime(*this).date().year();
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
