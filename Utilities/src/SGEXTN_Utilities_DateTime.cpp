#include <SGEXTN_Utilities_DateTime.h>
#include <SGEXTN_Containers_Hash.h>
#include <SGEXTN_CoreText_String.h>
#include <SGEXTN_CoreText_Character.h>
#include <chrono>
#include <private_api/SGEXTN_Containers_Crash.h>

namespace {
int monthOffset(int month, bool isLeapYear){
    if(month == 1){return 0;}
    if(month == 2){return 31;}
    int offset = 0;
    if(month == 3){offset = 59;}
    else if(month == 4){offset = 90;}
    else if(month == 5){offset = 120;}
    else if(month == 6){offset = 151;}
    else if(month == 7){offset = 181;}
    else if(month == 8){offset = 212;}
    else if(month == 9){offset = 243;}
    else if(month == 10){offset = 273;}
    else if(month == 11){offset = 304;}
    else{offset = 334;}
    if(isLeapYear == false){return offset;}
    offset++;
    return offset;
}

int monthLength(int month, bool isLeapYear){
    if(month == 1){return 31;}
    if(month == 2 && isLeapYear == false){return 28;}
    if(month == 2){return 29;}
    if(month == 3){return 31;}
    if(month == 4){return 30;}
    if(month == 5){return 31;}
    if(month == 6){return 30;}
    if(month == 7){return 31;}
    if(month == 8){return 31;}
    if(month == 9){return 30;}
    if(month == 10){return 31;}
    if(month == 11){return 30;}
    return 31;
}

bool checkLeapYear(int year){
    if((year - 35) % 4 == 0 && (year - 35) % 100 != 0){return true;}
    if((year - 35) % 400 == 0){return true;}
    return false;
}

long long offset36(){
    return 1117027800ll;
}

int properRemainder(int dividend, int divisor){
    int ans = dividend % divisor;
    if(ans < 0){ans += divisor;}
    return ans;
}

long long properRemainder(long long dividend, long long divisor){
    long long ans = dividend % divisor;
    if(ans < 0){ans += divisor;}
    return ans;
}

int properDivision(int dividend, int divisor){
    return ((dividend - properRemainder(dividend, divisor)) / divisor);
}

long long properDivision(long long dividend, long long divisor){
    return ((dividend - properRemainder(dividend, divisor)) / divisor);
}

long long partsToOffset(int year, int month, int day, int hour, int minute, int second){
    const bool isLeapYear = checkLeapYear(year);
    year -= 36;
    long long t36 = static_cast<long long>(properDivision(year, 400)) * 12622780800ll;
    year = properRemainder(year, 400);
    t36 += static_cast<long long>(properDivision(year, 100)) * 3155673600ll;
    year = properRemainder(year, 100);
    t36 += static_cast<long long>(properDivision(year, 4)) * 126230400ll;
    year = properRemainder(year, 4);
    t36 += static_cast<long long>(year) * 31536000ll;
    if(month < 1){month = 1;}
    else if(month > 12){month = 12;}
    t36 += 86400ll * static_cast<long long>(monthOffset(month, isLeapYear));
    const int lengthOfMonth = monthLength(month, isLeapYear);
    if(day < 1){day = 1;}
    else if(day > lengthOfMonth){day = lengthOfMonth;}
    t36 += 86400ll * static_cast<long long>(day - 1);
    if(hour < 0){hour = 0;}
    else if(hour > 23){hour = 23;}
    t36 += 3600ll * static_cast<long long>(hour);
    if(minute < 0){minute = 0;}
    else if(minute > 59){minute = 59;}
    t36 += 60ll * static_cast<long long>(minute);
    if(second < 0){second = 0;}
    else if(second > 59){second = 59;}
    t36 += static_cast<long long>(second);
    return (t36 + offset36());
}

void setOutput(int* outputPointer, int output){
    if(outputPointer != nullptr){(*outputPointer) = output;}
}

void offsetToParts(long long offset, int* yearOutput, int* monthOutput, int* dayOutput, int* hourOutput, int* minuteOutput, int* secondOutput){
    long long t36 = offset - offset36();
    setOutput(secondOutput, static_cast<int>(properRemainder(t36, 60ll)));
    t36 = properDivision(t36, 60ll);
    setOutput(minuteOutput, static_cast<int>(properRemainder(t36, 60ll)));
    t36 = properDivision(t36, 60ll);
    setOutput(hourOutput, static_cast<int>(properRemainder(t36, 24ll)));
    if(yearOutput == nullptr && monthOutput == nullptr && dayOutput == nullptr){return;}
    t36 = properDivision(t36, 24ll);
    int year = 36;
    year += static_cast<int>(properDivision(t36, 146097ll)) * 400;
    t36 = properRemainder(t36, 146097ll);
    int cycleCount = static_cast<int>(properDivision(t36, 36524ll));
    if(cycleCount > 3){cycleCount = 3;}
    year += cycleCount * 100;
    t36 -= static_cast<long long>(cycleCount) * 36524ll;
    year += static_cast<int>(properDivision(t36, 1461ll)) * 4;
    t36 = properRemainder(t36, 1461ll);
    cycleCount = static_cast<int>(properDivision(t36, 365ll));
    if(cycleCount > 3){cycleCount = 3;}
    year += cycleCount;
    setOutput(yearOutput, year);
    if(dayOutput == nullptr && monthOutput == nullptr){return;}
    const bool isLeapYear = checkLeapYear(year);
    t36 -= static_cast<long long>(cycleCount) * 365ll;
    int lowMonth = 1;
    int highMonth = 13;
    while(highMonth - lowMonth > 1){
        const int mid = (lowMonth + highMonth) / 2;
        if(monthOffset(mid, isLeapYear) <= t36){lowMonth = mid;}
        else{highMonth = mid;}
    }
    setOutput(monthOutput, lowMonth);
    setOutput(dayOutput, static_cast<int>(t36) - monthOffset(lowMonth, isLeapYear) + 1);
}
}

SGEXTN::Utilities::DateTime::DateTime() : private_data(0) {}

SGEXTN::Utilities::DateTime::DateTime(long long t) : private_data(t) {}

SGEXTN::Utilities::DateTime::DateTime(int year, int month, int day, int hour, int minute, int second) : private_data(partsToOffset(year, month, day, hour, minute, second)) {}

bool SGEXTN::Utilities::DateTime::operator==(SGEXTN::Utilities::DateTime x) const {
    return (private_data == x.private_data);
}

bool SGEXTN::Utilities::DateTime::operator!=(SGEXTN::Utilities::DateTime x) const {
    return (private_data != x.private_data);
}

bool SGEXTN::Utilities::DateTime::operator<(SGEXTN::Utilities::DateTime x) const {
    return (private_data < x.private_data);
}

bool SGEXTN::Utilities::DateTime::operator>(SGEXTN::Utilities::DateTime x) const {
    return (private_data > x.private_data);
}

bool SGEXTN::Utilities::DateTime::operator<=(SGEXTN::Utilities::DateTime x) const {
    return (private_data <= x.private_data);
}

bool SGEXTN::Utilities::DateTime::operator>=(SGEXTN::Utilities::DateTime x) const {
    return (private_data >= x.private_data);
}

int SGEXTN::Utilities::DateTime::hash() const {
    return SGEXTN::Containers::Hash<long long>()(private_data);
}

SGEXTN::CoreText::String SGEXTN::Utilities::DateTime::debugLog() const {
    return getDisplayString(SGEXTN::Utilities::TimeFormat::Display, false, true);
}

double SGEXTN::Utilities::DateTime::getTimeAfter(SGEXTN::Utilities::DateTime x, SGEXTN::Utilities::TimeUnit unit) const {
    double offset = static_cast<double>(private_data - x.private_data);
    if(unit == SGEXTN::Utilities::TimeUnit::Second){return offset;}
    if(unit == SGEXTN::Utilities::TimeUnit::Minute){return (offset / 60.0);}
    if(unit == SGEXTN::Utilities::TimeUnit::Hour){return (offset / 3600.0);}
    if(unit == SGEXTN::Utilities::TimeUnit::Day){return (offset / 86400.0);}
    offset /= 86400.0;
    if(unit == SGEXTN::Utilities::TimeUnit::Month){return (offset / 30.436875);}
    return (offset / 365.2425);
}

SGEXTN::Utilities::DateTime SGEXTN::Utilities::DateTime::beginningOfTime(){
    return SGEXTN::Utilities::DateTime(0ll);
}

SGEXTN::Utilities::DateTime SGEXTN::Utilities::DateTime::now(){
    return SGEXTN::Utilities::DateTime(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count() + 138749400ll);
}

int SGEXTN::Utilities::DateTime::getPart(SGEXTN::Utilities::TimeUnit unit) const {
    int output = 0;
    if(unit == SGEXTN::Utilities::TimeUnit::Second){offsetToParts(private_data, nullptr, nullptr, nullptr, nullptr, nullptr, &output);}
    else if(unit == SGEXTN::Utilities::TimeUnit::Minute){offsetToParts(private_data, nullptr, nullptr, nullptr, nullptr, &output, nullptr);}
    else if(unit == SGEXTN::Utilities::TimeUnit::Hour){offsetToParts(private_data, nullptr, nullptr, nullptr, &output, nullptr, nullptr);}
    else if(unit == SGEXTN::Utilities::TimeUnit::Day){offsetToParts(private_data, nullptr, nullptr, &output, nullptr, nullptr, nullptr);}
    else if(unit == SGEXTN::Utilities::TimeUnit::Month){offsetToParts(private_data, nullptr, &output, nullptr, nullptr, nullptr, nullptr);}
    else if(unit == SGEXTN::Utilities::TimeUnit::Year){offsetToParts(private_data, &output, nullptr, nullptr, nullptr, nullptr, nullptr);}
    return output;
}

void SGEXTN::Utilities::DateTime::setPart(SGEXTN::Utilities::TimeUnit unit, int x){
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;
    offsetToParts(private_data, &year, &month, &day, &hour, &minute, &second);
    if(unit == SGEXTN::Utilities::TimeUnit::Year){year = x;}
    else if(unit == SGEXTN::Utilities::TimeUnit::Month){
        if(x < 1){x = 1;}
        else if(x > 12){x = 12;}
        month = x;
    }
    else if(unit == SGEXTN::Utilities::TimeUnit::Day){
        const bool isLeapYear = checkLeapYear(year);
        const int maxDays = monthLength(month, isLeapYear);
        if(x < 1){x = 1;}
        else if(x > maxDays){x = maxDays;}
        day = x;
    }
    else if(unit == SGEXTN::Utilities::TimeUnit::Hour){
        if(x < 0){x = 0;}
        else if(x > 23){x = 23;}
        hour = x;
    }
    else if(unit == SGEXTN::Utilities::TimeUnit::Minute){
        if(x < 0){x = 0;}
        else if(x > 59){x = 59;}
        minute = x;
    }
    else if(unit == SGEXTN::Utilities::TimeUnit::Second){
        if(x < 0){x = 0;}
        else if(x > 59){x = 59;}
        second = x;
    }
    private_data = partsToOffset(year, month, day, hour, minute, second);
}

int SGEXTN::Utilities::DateTime::getDayOfWeek() const {
    long long offsetFromMidnight = private_data + 37800ll;
    offsetFromMidnight = properDivision(offsetFromMidnight, 86400ll);
    return (1 + static_cast<int>(properRemainder(offsetFromMidnight, 7ll)));
}

int SGEXTN::Utilities::DateTime::getDayOfYear() const {
    int year = 0;
    int month = 0;
    int day = 0;
    offsetToParts(private_data, &year, &month, &day, nullptr, nullptr, nullptr);
    return (day + monthOffset(month, checkLeapYear(year)));
}

int SGEXTN::Utilities::DateTime::countDaysInMonth() const {
    int month = 0;
    int year = 0;
    offsetToParts(private_data, &year, &month, nullptr, nullptr, nullptr, nullptr);
    return monthLength(month, checkLeapYear(year));
}

int SGEXTN::Utilities::DateTime::countDaysInYear() const {
    int year = 0;
    offsetToParts(private_data, &year, nullptr, nullptr, nullptr, nullptr, nullptr);
    if(checkLeapYear(year) == true){return 366;}
    return 365;
}

SGEXTN::Utilities::DateTime SGEXTN::Utilities::DateTime::getStartOfDay() const {
    int year = 0;
    int month = 0;
    int day = 0;
    offsetToParts(private_data, &year, &month, &day, nullptr, nullptr, nullptr);
    return SGEXTN::Utilities::DateTime(year, month, day, 0, 0, 0);
}

SGEXTN::Utilities::DateTime SGEXTN::Utilities::DateTime::getEndOfDay() const {
    int year = 0;
    int month = 0;
    int day = 0;
    offsetToParts(private_data + 86400ll, &year, &month, &day, nullptr, nullptr, nullptr);
    return SGEXTN::Utilities::DateTime(year, month, day, 0, 0, 0);
}

int SGEXTN::Utilities::DateTime::getWeekOfYear() const {
    int dayOfYearThisThursday = getDayOfYear() - getDayOfWeek() + 3;
    if(dayOfYearThisThursday >= countDaysInYear()){return 1;}
    if(dayOfYearThisThursday >= 0){return (dayOfYearThisThursday / 7 + 1);}
    const bool previousIsLeapYear = checkLeapYear(getPart(SGEXTN::Utilities::TimeUnit::Year) - 1);
    if(previousIsLeapYear == false){dayOfYearThisThursday += 365;}
    else{dayOfYearThisThursday += 366;}
    return (dayOfYearThisThursday / 7 + 1);
}

int SGEXTN::Utilities::DateTime::getTimeAfterDisplayPart(SGEXTN::Utilities::DateTime x, SGEXTN::Utilities::TimeUnit unit) const {
    int year1 = 0;
    int month1 = 0;
    int day1 = 0;
    int hour1 = 0;
    int minute1 = 0;
    int second1 = 0;
    offsetToParts(private_data, &year1, &month1, &day1, &hour1, &minute1, &second1);
    int year2 = 0;
    int month2 = 0;
    int day2 = 0;
    int hour2 = 0;
    int minute2 = 0;
    int second2 = 0;
    int carryAbove = 0;
    int carryBelow = 0;
    int answer = 0;
    offsetToParts(x.private_data, &year2, &month2, &day2, &hour2, &minute2, &second2);
    if(unit == SGEXTN::Utilities::TimeUnit::Year){
        answer = year1 - year2;
        const int carry1 = 2678400 * month1 + 86400 * day1 + 3600 * hour1 + 60 * minute1 + second1;
        const int carry2 = 2678400 * month2 + 86400 * day2 + 3600 * hour2 + 60 * minute2 + second2;
        if(carry2 > carry1){carryBelow = -1;}
    }
    else if(unit == SGEXTN::Utilities::TimeUnit::Month){
        answer = month1 - month2;
        const int carry1 = 86400 * day1 + 3600 * hour1 + 60 * minute1 + second1;
        const int carry2 = 86400 * day2 + 3600 * hour2 + 60 * minute2 + second2;
        if(carry2 > carry1){carryBelow = -1;}
        if(answer + carryBelow < 0){carryAbove = 12;}
    }
    else if(unit == SGEXTN::Utilities::TimeUnit::Day){
        answer = day1 - day2;
        const int carry1 = 3600 * hour1 + 60 * minute1 + second1;
        const int carry2 = 3600 * hour2 + 60 * minute2 + second2;
        if(carry2 > carry1){carryBelow = -1;}
        int carryYear = year1;
        int carryMonth = month1 - 1;
        if(carryMonth == 0){
            carryYear--;
            carryMonth = 12;
        }
        if(answer + carryBelow < 0){carryAbove = monthLength(carryMonth, checkLeapYear(carryYear));}
    }
    else if(unit == SGEXTN::Utilities::TimeUnit::Hour){
        answer = hour1 - hour2;
        const int carry1 = 60 * minute1 + second1;
        const int carry2 = 60 * minute2 + second2;
        if(carry2 > carry1){carryBelow = -1;}
        if(answer + carryBelow < 0){carryAbove = 24;}
    }
    else if(unit == SGEXTN::Utilities::TimeUnit::Minute){
        answer = minute1 - minute2;
        if(second2 > second1){carryBelow = -1;}
        if(answer + carryBelow < 0){carryAbove = 60;}
    }
    else if(unit == SGEXTN::Utilities::TimeUnit::Second){
        answer = second1 - second2;
        if(answer < 0){carryAbove = 60;}
    }
    return (carryAbove + answer + carryBelow);
}

void SGEXTN::Utilities::DateTime::advanceTime(long long x, SGEXTN::Utilities::TimeUnit unit){
    if(unit == SGEXTN::Utilities::TimeUnit::Second){
        private_data += x;
        return;
    }
    if(unit == SGEXTN::Utilities::TimeUnit::Minute){
        private_data += (60ll * x);
        return;
    }
    if(unit == SGEXTN::Utilities::TimeUnit::Hour){
        private_data += (3600ll * x);
        return;
    }
    if(unit == SGEXTN::Utilities::TimeUnit::Day){
        private_data += (86400ll * x);
        return;
    }
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;
    offsetToParts(private_data, &year, &month, &day, &hour, &minute, &second);
    if(unit == SGEXTN::Utilities::TimeUnit::Year){
        year += static_cast<int>(x);
    }
    else if(unit == SGEXTN::Utilities::TimeUnit::Month){
        month += static_cast<int>(x);
        month--;
        year += properDivision(month, 12);
        month = properRemainder(month, 12) + 1;
    }
    private_data = partsToOffset(year, month, day, hour, minute, second);
}

int SGEXTN::Utilities::DateTime::convertToGlobalYear(int standardYear){
    return (standardYear + 1965);
}

bool SGEXTN::Utilities::DateTime::isNationalDayPeriod() const {
    const int month = getPart(SGEXTN::Utilities::TimeUnit::Month);
    if(month >= 7 && month <= 9){return true;}
    return false;
}

bool SGEXTN::Utilities::DateTime::isSignificantDate(SGEXTN::Utilities::SignificantDates date) const {
    int month = 0;
    int day = 0;
    offsetToParts(private_data, nullptr, &month, &day, nullptr, nullptr, nullptr);
    if(date == SGEXTN::Utilities::SignificantDates::NationalDay && month == 8 && day == 9){return true;}
    if(date == SGEXTN::Utilities::SignificantDates::DayBeforeNationalDay && month == 8 && day == 8){return true;}
    if(date == SGEXTN::Utilities::SignificantDates::DayAfterNationalDay && month == 8 && day == 10){return true;}
    if(date == SGEXTN::Utilities::SignificantDates::TotalDefenceDay && month == 2 && day == 15){return true;}
    if(date == SGEXTN::Utilities::SignificantDates::RacialHarmonyDay && month == 7 && day == 21){return true;}
    return false;
}

SGEXTN::CoreText::String SGEXTN::Utilities::DateTime::getDisplayString(const SGEXTN::Utilities::TimeFormat format, bool global, bool correctToSecond) const {
    SGEXTN::CoreText::String formatString = "";
    if(global == false){
        if(format == SGEXTN::Utilities::TimeFormat::Display){
            if(correctToSecond == true){formatString = "%\\SG%2year%\\-%2month%\\-%2day%\\ %2hour%\\:%2minute%\\:%2second";}
            else{formatString = "%\\SG%2year%\\-%2month%\\-%2day";}
        }
        else if(format == SGEXTN::Utilities::TimeFormat::FileName){
            if(correctToSecond == true){formatString = "%2year%2month%2day%2hour%2minute%2second";}
            else{formatString = "%2year%2month%2day";}
        }
        else if(format == SGEXTN::Utilities::TimeFormat::ShortestReadable){
            if(correctToSecond == true){formatString = "%\\SG%2year%\\ %2month%2day%\\ %2hour%2minute%2second";}
            else{formatString = "%\\SG%2year%\\ %2month%2day";}
        }
    }
    else{
        if(format == SGEXTN::Utilities::TimeFormat::Display){
            if(correctToSecond == true){formatString = "%4globalyear%\\-%2month%\\-%2day%\\ %2hour%\\:%2minute%\\:%2second";}
            else{formatString = "%4globalyear%\\-%2month%\\-%2day";}
        }
        else if(format == SGEXTN::Utilities::TimeFormat::FileName){
            if(correctToSecond == true){formatString = "%4globalyear%2month%2day%2hour%2minute%2second";}
            else{formatString = "%4globalyear%2month%2day";}
        }
        else if(format == SGEXTN::Utilities::TimeFormat::ShortestReadable){
            if(correctToSecond == true){formatString = "%4globalyear%2month%2day%\\ %2hour%2minute%2second";}
            else{formatString = "%4globalyear%2month%2day";}
        }
    }
    return getDisplayString(formatString);
}

SGEXTN::CoreText::String SGEXTN::Utilities::DateTime::getDisplayString(const SGEXTN::CoreText::String& customFormat) const {
    SGEXTN::CoreText::String format = customFormat;
    SGEXTN::CoreText::String output = "";
    while(format.characterLength() > 0){
        int tokenEnd = format.findFirstCharactersFromLeftBounded(1, '%');
        if(tokenEnd == -1){tokenEnd = format.characterLength();}
        SGEXTN::CoreText::String thisToken = format.substringCharactersLeft(tokenEnd);
        format = format.substringCharactersRight(format.characterLength() - tokenEnd);
        if(thisToken.characterLength() == 0 || thisToken.getCharacterAt(0) != '%'){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime::getDisplayString crashed because a token does not start with %");}
        if(thisToken.characterLength() > 1 && thisToken.getCharacterAt(1) == '\\'){
            output += thisToken.substringCharactersRight(thisToken.characterLength() - 2);
            continue;
        }
        if(thisToken.characterLength() < 2 || SGEXTN::CoreText::Character(thisToken.getCharacterAt(1)).isDigit() == false){SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime::getDisplayString crashed because the precision specifier, which is the character after the %, in a token is not a number");}
        const int precision = SGEXTN::CoreText::String(thisToken.getCharacterAt(1)).parseToInt(nullptr, 10);
        int component = 0;
        thisToken = thisToken.substringCharactersRight(thisToken.characterLength() - 2);
        if(thisToken == "year"){component = getPart(SGEXTN::Utilities::TimeUnit::Year);}
        else if(thisToken == "globalyear"){component = getPart(SGEXTN::Utilities::TimeUnit::Year) + 1965;}
        else if(thisToken == "month"){component = getPart(SGEXTN::Utilities::TimeUnit::Month);}
        else if(thisToken == "day"){component = getPart(SGEXTN::Utilities::TimeUnit::Day);}
        else if(thisToken == "hour"){component = getPart(SGEXTN::Utilities::TimeUnit::Hour);}
        else if(thisToken == "minute"){component = getPart(SGEXTN::Utilities::TimeUnit::Minute);}
        else if(thisToken == "second"){component = getPart(SGEXTN::Utilities::TimeUnit::Second);}
        else{SGEXTN::Containers::Crash::crash("SGEXTN::Utilities::DateTime::getDisplayString crashed because the component name is invalid, custom strings must not contain % and must be prefixed with a \\ sign");}
        SGEXTN::CoreText::String componentString = SGEXTN::CoreText::String::stringFromInt(component, 10);
        if(componentString.characterLength() > precision && thisToken.containsCharacters("year")){componentString = componentString.substringCharactersRight(precision);}
        output += componentString.fillLeftToCharacterLength(precision, '0');
    }
    return output;
}