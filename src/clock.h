#pragma once
#include <array>
#include <RTClib.h>

extern RTC_DS3231 RTC;

DateTime getNow();

std::array<int, 3> getTime();
std::array<int, 3> getDate();