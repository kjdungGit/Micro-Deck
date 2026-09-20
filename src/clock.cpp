#include "clock.h"

RTC_DS3231 RTC;

DateTime getNow(){
    return RTC.now();
}

uint32_t getUnixTime(){
    return RTC.now().unixtime();
}

std::array<int, 3> getTime(){
    DateTime now = getNow();
    return {now.hour(), now.minute(), now.second()};
}

std::array<int, 3> getDate(){
    DateTime now = getNow();
    return {now.day(), now.month(), now.year()};
}
